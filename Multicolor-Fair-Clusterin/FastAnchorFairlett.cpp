#include "FastAnchorFairlett.h"

#ifdef PROCESS_BAR
    #define printProcess(process) std::cout << process << endl;
#else
    #define printProcess(process)
#endif

// * * * =========== Calculating the Fairlets =========== * * * //
double fastAnchorFairlett::markFairletts(vector<ColoredPoint>* points){
    // Farben richtig Sortieren
    makeCritFeatureSmalestFirst(points);
    printProcess("--smallFeature-- ");

    // Anker berechnen
    AnchorMatrix anchorMatrix;
    calculateAnchors(points, anchorMatrix);

    // Optimalen Radius Finden
    double optRad = findBinaryPotentionalRadius(points, anchorMatrix);
    printProcess("--found potRad-- ");

    // Graph mit Optimalem Radius Aufbauen
    // Variablen erzeugen
	Graph g;
	FGraphData gData;
	CapacityMap capacity(g);

    // Ankermatrix hinzufügen
    gData.anchorDistance = anchorMatrix;

    // Graph Initialisieren
    fastAnchorFlow::buildupGraphFromAnchorDist(g, gData, capacity, optRad, points);
    printProcess("--build Graph-- ");

    // Fluss berechnen
    Flow* preflow = fastAnchorFlow::calculateFlow(g, capacity, gData);
    printProcess("--made Flow-- ");

    // Main-Kanten durchgehen und Partner markieren
    // Punkte Filtern
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();


    // Main Fairletts bilden
    int fairlettCounter = markMainNodes(g, *preflow, gData.mainArcs, nRed, points, anchorMatrix);
    printProcess("--marked Fairlets-- ");    

    // Ausreißer markieren
    int numOfOutlier = markOutliers(g, *preflow, gData.targetArcs, nRed, points);
    printProcess("--marked outlier-- ");
    printProcess("----number of fairletts: " << fairlettCounter << ";\tnumber of outlier: " << numOfOutlier <<" --");

    // Aufräumen 
    delete redPoints;
    delete preflow;

    return optRad;
}


int fastAnchorFairlett::markMainNodes(const Graph& g, const Flow& preflow, 
                                    vector<Arc> mainArcs, int nRed, 
                                    vector<ColoredPoint>* points, AnchorMatrix& anchorMatrix){

    int fairlettCounter = 0;

    // Alle main-Kanten durchgehen
    for (int i = 0; i < (int) mainArcs.size(); i++){
        // Hat die Kante überhaupt Fluss?
        if (fastAnchorFlow::getFlowOfArc(preflow, mainArcs.at(i)) < 1){
            continue;
        }
        
        // Nodes herausfinden
        Node redNode = g.source(mainArcs.at(i));
        Node blueNode = g.target(mainArcs.at(i));

        // FarbIndex herausfinden
        int redIndex = mapIDtoIndexByColor(g.id(redNode), RED, nRed);
        int blueIndex = mapIDtoIndexByColor(g.id(blueNode), BLUE, nRed);

        // Ankerknoten bestimmen
        int anchorID = anchorMatrix[redIndex][blueIndex].trueAnchorID;

        // Echte Punkte mit fairlettID markieren
        markFairlettWithAnchor(fairlettCounter, anchorID, g.id(redNode), RED, nRed, points);
        markFairlettWithAnchor(fairlettCounter, anchorID, g.id(blueNode), BLUE, nRed, points);


        // IDs hochzählen
        fairlettCounter++;
    }
    
    // Anzahl an Fairletts zurückgeben
    return fairlettCounter;
}


int fastAnchorFairlett::markOutliers(const Graph& g, const Flow& preflow, 
                                    vector<Arc> targetArcs, int nRed, 
                                    vector<ColoredPoint>* points){
    int outlier = 0;

    // Alle main-Kanten durchgehen
    for (int i = 0; i < (int) targetArcs.size(); i++){
        // Hat die Kante überhaupt Fluss?
        if (fastAnchorFlow::getFlowOfArc(preflow, targetArcs.at(i)) > 0){
            continue;
        }
        
        // Nodes herausfinden
        Node blueNode = g.source(targetArcs.at(i));

        // Echte Punkte mit fairlettID markieren
        markFairlettWithAnchor(-2, -2, g.id(blueNode), BLUE, nRed, points);

        // Anzahl hochzählen
        outlier++;
    }

    return outlier;
}


void fastAnchorFairlett::makeCritFeatureSmalestFirst(vector<ColoredPoint> *points){
    // Punkte durchzählen
    int nRed = 0;
    int nBlue = 0;
    int nOther = 0;

    for (int i = 0; i < (int) points->size(); i++){
        switch (points->at(i).getColor()){
        case RED:
            nRed++;
            break;

        case BLUE:
            nBlue++;
            break;
        
        default:
            nOther++;
            break;
        }
    }

    // Sanity-Check
    if (nOther > 0){
        printf("Es wurden %d Punkte gezählt die weder rot noch blau sind\n", nOther);        
    }

    // Muss denn getauscht werden?
    if (nBlue > nRed){
        return;
    }

    // Zahlen Tauschen
    for (int i = 0; i < (int) points->size(); i++){
        switch (points->at(i).getColor()){
        case RED:
            points->at(i).setColor(BLUE);
            break;

        case BLUE:
            points->at(i).setColor(RED);
            break;
        
        default:
            nOther++;
            break;
        }
    }
    
    return;
}





double fastAnchorFairlett::findBinaryPotentionalRadius(vector<ColoredPoint>* points, AnchorMatrix& anchorMatrix){
    // Alle möglichen Radien berechnen
    vector<double>* potRadii = calculateAllRadii(points); // Kommen sortiert zurück
    printProcess("\nChecking " << (int) potRadii->size() <<" potentional Radii with Binary-Search\n");
    #ifdef PROCESS_BAR
        int checkedNumbers = 0;
    #endif  
    


    // Startgrenzen für die Binäre-Suche
    int left = 0;
    int right = (int) potRadii->size() - 1;
    bool workingRadius = false;
    

    // Binäre-Suche machen
    while (left <= right) {
        // Sind wir schon am richtigen Index?
        // Radius bei left zu klein, Radius bei rechts gibt validen Fluss und 
        // die zwei sind nur noch um Eins verschieden
        // --> der kleinst mögliche Radius liegt bei right
        if (left >= right){  
            // Funktionierenden Radius abspeichern
            double trueRadius = potRadii->at(right);
            printProcess("\n----radius found after " << checkedNumbers << " Checks");
            printProcess("----using radius at index " << right);

            // Off by one Error überprüfen
            // Fall Links wurde verschoben aber noch nicht überprüft
            if (!workingRadius){
                printProcess("------off by one error correction; " << right << " to " << left);
                printProcess("------change radius from " << trueRadius << " to " << potRadii->at(left));
                trueRadius = potRadii->at(left);
            }

            // Aufräumen
            delete(potRadii);

            // Zurückgeben
            return trueRadius;
        }
        
        // Mitte ausrechnen
        int mid = left + (right - left) / 2;

        // checken des Radius an der Stelle mid
        workingRadius = checkRadius(points, anchorMatrix, potRadii->at(mid));

        // Wenn der Radius funktioniert funktionieren auch alle darüber
        // --> verschiebe Rechts auf mid
        if (workingRadius){
            right = mid;
        }

        // Wenn der Radius nicht funktioniert sind auch alle darunter zu klein
        // --> verschiebe Links auf mid
        if (!workingRadius){
            left = mid+1;
        }
        #ifdef PROCESS_BAR
            // Progressbar
        if (checkedNumbers % 10 == 0){
            printf("\nCheck: %d ", checkedNumbers);
            fflush(stdout);
        }else{
            printf(" * ");
            fflush(stdout);
        }
        checkedNumbers++; 
        #endif   
    }


    // Fehlerfall
    printf("ERROR: Es können keine Fairlets gebildet werden. Größter Radius %f ist nicht groß genung\n", potRadii->back());
    delete potRadii;
    return -1.0;
}




vector<double>* fastAnchorFairlett::calculateAllRadii(vector<ColoredPoint>* points){
    // Erstmal nach Blau und Rot filtern
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = ColoredPoint::getPointsOfColor(points, BLUE);

    // Liste für alle Radien Anlegen
    vector<double>* potentalRadii = new vector<double>;

    // Alle möglichen Radien berechnen
    // Alle roten Punkte durchgehen
    for (int redIndex = 0; redIndex < (int) redPoints->size(); redIndex++){
        //printf("Test Potentional Radii with Index %d\n", redIndex);
        // Alle blauen Punkte durchgehen
        for (int blueIndex = 0; blueIndex < (int) bluePoints->size(); blueIndex++){
            // Radius hinzufügen
            potentalRadii->push_back(redPoints->at(redIndex).distTo(bluePoints->at(blueIndex)));
        } 
    }

    // Radien Sortieren
    std::sort(potentalRadii->begin(), potentalRadii->end());

    delete redPoints;
    delete bluePoints;

    return potentalRadii;
}



bool fastAnchorFairlett::checkRadius(vector<ColoredPoint>* points, AnchorMatrix& anchorMatrix, double potRad){    
    // Graphenstruktur aufbauen
    // Variablen erzeugen
	Graph g;
	FGraphData gData;
	CapacityMap capacity(g);

    // AnkerMatrixadresse übertragen
    gData.anchorDistance = anchorMatrix;


    // Graph Initialisieren
    fastAnchorFlow::buildupGraphFromAnchorDist(g, gData, capacity, potRad, points);


    // Fluss berechnen
    int maxFlowValue = fastAnchorFlow::getMaxFlow(g, capacity, gData);


    // Vergleichwert holen
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();


    // Aufräumen
    delete(redPoints);
    
    // Zurückgeben ob Fluss groß genug ist
    return maxFlowValue >= nRed;
}












// ==== Matrix Calculation ==== //
void fastAnchorFairlett::calculateAnchors(vector<ColoredPoint>* points, AnchorMatrix& anchorMatrix){
    // Erstmal nach Blau und Rot filtern
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = ColoredPoint::getPointsOfColor(points, BLUE);

    // Distanzmatrix als Look-Up berechnen
    vector<vector<double>> distLookMatrix;
    fillDistanceMatrix(points, distLookMatrix);

    // Größen bestimmen
    int nRed = (int) redPoints->size();
    int nBlue = (int) bluePoints->size();
    int n = (int) points->size();

    // Größe auf Matrix bringen
    anchorMatrix.resize(nRed);
    for (int i = 0; i < nRed; ++i) {
        anchorMatrix[i].resize(nBlue);
    }
    
    // Indizes für in die Anker-Matric
    int redAnchorIndex = 0;
    int blueAnchorIndex = 0;

    // Alle Punkte durchgehen (rotseitig)
    for (int redSideIndex = 0; redSideIndex < n; redSideIndex++){
        // Wenn Paar nicht matched, einfach direkt weitermachen
        if (points->at(redSideIndex).getColor() != RED ){
            continue;
        }

        // Alle Punkte durchgenen (blauseitig)
        for (int blueSideIndex = 0; blueSideIndex < n; blueSideIndex++){
            // Wenn Paar nicht matched, einfach direkt weitermachen
            if (points->at(blueSideIndex).getColor() != BLUE ){
                continue;
            }
            // Startwerte (Wähle einfach den Roten Punkt als Anker)
            // Wert ist auf jedenfall möglich aber potentiell nicht der beste
            anchorMatrix[redAnchorIndex][blueAnchorIndex].distToPartners = distLookMatrix[redSideIndex][blueSideIndex];
            anchorMatrix[redAnchorIndex][blueAnchorIndex].trueAnchorID = redSideIndex;

            // Alle möglichen Anker ausprobieren
            for (int anchorIndex = 0; anchorIndex < n; anchorIndex++) {
                // Distanz zu potenziellemn Anker Ausrechnen
                double rDist = distLookMatrix[redSideIndex][anchorIndex];
                double bDist = distLookMatrix[blueSideIndex][anchorIndex];;

                // Maximum bestimmen
                double newMax = rDist;
                if (bDist > newMax)
                    newMax = bDist;

                // ist der neu gefundene Anker besser?
                if (newMax < anchorMatrix[redAnchorIndex][blueAnchorIndex].distToPartners) {
                    // Alten Anker durch neuen ersetzen
                    anchorMatrix[redAnchorIndex][blueAnchorIndex].distToPartners = newMax;
                    anchorMatrix[redAnchorIndex][blueAnchorIndex].trueAnchorID = anchorIndex;
                }
            }
            blueAnchorIndex++;
        } 
        blueAnchorIndex = 0;
        redAnchorIndex++;
        
        #ifdef PROCESS_BAR
        // Progressbar
        if (redAnchorIndex % 100 == 0){
            printProcess("--- Calculatet Anchors for " << redAnchorIndex << " red points")
        }
        #endif  
    }

    delete redPoints;
    delete bluePoints;    
}




void fastAnchorFairlett::fillDistanceMatrix(vector<ColoredPoint>* points, vector<vector<double>>& matrix){

    // Größen bestimmen
    int n= (int) points->size();

    // Größe auf Matrix bringen
    matrix.resize(n);
    for (int i = 0; i < n; ++i) {
        matrix[i].resize(n);
    }

    // Alle roten Punkte durchgehen
    for (int firstIndex = 0; firstIndex < n; firstIndex++){
        // Für alle Blaue Punkte den Vektor berechnen
        //vector<double>* blueDistancesOfSingleRedPoint = new vector<double>;
        for (int secondIndex = 0; secondIndex < n; secondIndex++){
            // Distanz ausrechnen
            double distance = points->at(firstIndex).distTo(points->at(secondIndex));

            // in Matrix stecken
            matrix[firstIndex][secondIndex] = distance;    
        }        
    }
}
























// ==== Utility ==== //
int fastAnchorFairlett::mapIDtoIndexByColor(int ID, Pointcolor color, int nRed){
    // Farben-Fallunterscheidung
    if (color == RED)   { return ID; }
    if (color == BLUE)  { return ID - nRed; }
    
    // Fehlerfall  
    return -1;
}



void fastAnchorFairlett::markFairlettWithAnchor(int fairlettID, int anchorID, int nodeID, Pointcolor color, int nRed, vector<ColoredPoint>* points){
    // Stelle finden an welcher der Punkt in der echten Liste ist
    int trueIndex = getTrueIndexOfPoint(nodeID, color, nRed, points);

    // FairlettID an dieser Stelle abändern
    points->at(trueIndex).setFairlettID(fairlettID);

    // AnkerID an dieser Stelle abändern
    points->at(trueIndex).setAnchorID(anchorID);

    return;
}



int fastAnchorFairlett::getTrueIndexOfPoint(int colorOnlyIndex, Pointcolor color, int nRed, vector<ColoredPoint>* points){
    // Die Nummer wievielter Punkt dieser Farbe der Punkt ist
    int colorIndex = mapIDtoIndexByColor(colorOnlyIndex, color, nRed);

    // Index des entsprechenden Punktes suchen
    int trueIndex = -1;
    // So lange durchgehen bis ich den richtigen Index gefunden habe oder am Ende der Liste bin
    for (int i = 0; i < (int) points->size(); i++){
        // Hat der Knoten die richtige Farbe?
        if (points->at(i).getColor() == color){
            // Haben wir schon genug gesehen?
            // Nein:
            if (colorIndex > 0) {
                colorIndex--;
                continue;
            }
            // Ja:
            trueIndex = i;
            break;
        }
        
    }
    return trueIndex;
}








// ==== Debugging ==== //
void fastAnchorFairlett::printAnchorMatrix(const std::vector<std::vector<Anchor>>& matrix) {
    for (const auto& row : matrix) {
        for (Anchor element : row) {
            std::cout << "(" << element.trueAnchorID << ", " << element.distToPartners << ")   ";
        }
        std::cout << std::endl;
    }
}




void fastAnchorFairlett::printDistMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}