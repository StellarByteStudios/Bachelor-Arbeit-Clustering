#include "FairlettFinder.h"

#ifdef PROCESS_BAR
    #define printProcess(process) std::cout << process << endl;
#else
    #define printProcess(process)
#endif

// * * * =========== Calculating the Fairlets =========== * * * //
double fairlettFinder::markFairletts(vector<ColoredPoint>* points){
    // Farben richtig Sortieren
    makeCritFeatureSmalestFirst(points);
    printProcess("--smallFeature-- ");

    // Optimalen Radius Finden
    double optRad = findBinaryPotentionalRadius(points);
    printProcess("--found potRad-- ");

    // Graph mit Optimalem Radius Aufbauen
    // Variablen erzeugen
	Graph g;
	GraphData gData;
	CapacityMap capacity(g);

    // Graph Initialisieren
    graphFlow::buildupGraphFromRadius(g, gData, capacity, optRad, points);
    printProcess("--build Graph-- ");

    // Fluss berechnen
    Flow* preflow = graphFlow::calculateFlow(g, capacity, gData);
    printProcess("--made Flow-- ");

    // Main-Kanten durchgehen und Partner markieren
    // Punkte Filtern
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();


    // Main Fairletts bilden
    int fairlettCounter = markMainNodes(g, *preflow, gData.mainArcs, nRed, points);
    printProcess("--marked Fairlets-- ");    

    // Ausreißer markieren
    int numOfOutlier = markOutliers(g, *preflow, gData.targetArcs, nRed, points);
    printProcess("--marked outlier-- ");
    printProcess("----number of fairletts: " << fairlettCounter << ";\tnuber of outlier: " << numOfOutlier <<" --");

    // Aufräumen 
    delete redPoints;
    delete preflow;

    return optRad;
}


int fairlettFinder::markMainNodes(const Graph& g, const Flow& preflow, 
                                    vector<Arc> mainArcs, int nRed, 
                                    vector<ColoredPoint>* points){

    int fairlettCounter = 0;

    // Alle main-Kanten durchgehen
    for (int i = 0; i < (int) mainArcs.size(); i++){
        // Hat die Kante überhaupt Fluss?
        if (graphFlow::getFlowOfArc(preflow, mainArcs.at(i)) < 1){
            continue;
        }
        
        // Nodes herausfinden
        Node redNode = g.source(mainArcs.at(i));
        Node blueNode = g.target(mainArcs.at(i));

        // Echte Punkte mit fairlettID markieren
        markSinglePointWithFairlett(fairlettCounter, g.id(redNode), RED, nRed, points);
        markSinglePointWithFairlett(fairlettCounter, g.id(blueNode), BLUE, nRed, points);

        // IDs hochzählen
        fairlettCounter++;
    }
    
    // Anzahl an Fairletts zurückgeben
    return fairlettCounter;
}


int fairlettFinder::markOutliers(const Graph& g, const Flow& preflow, 
                                    vector<Arc> targetArcs, int nRed, 
                                    vector<ColoredPoint>* points){
    int outlier = 0;

    // Alle main-Kanten durchgehen
    for (int i = 0; i < (int) targetArcs.size(); i++){
        // Hat die Kante überhaupt Fluss?
        if (graphFlow::getFlowOfArc(preflow, targetArcs.at(i)) > 0){
            continue;
        }
        
        // Nodes herausfinden
        Node blueNode = g.source(targetArcs.at(i));

        // Echte Punkte mit fairlettID markieren
        markSinglePointWithFairlett(-2, g.id(blueNode), BLUE, nRed, points);

        // Anzahl hochzählen
        outlier++;
    }

    return outlier;
}


void fairlettFinder::makeCritFeatureSmalestFirst(vector<ColoredPoint> *points){
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


double fairlettFinder::findBinaryPotentionalRadius(vector<ColoredPoint>* points){
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
        workingRadius = checkRadius(points, potRadii->at(mid));

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




vector<double>* fairlettFinder::calculateAllRadii(vector<ColoredPoint>* points){
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



bool fairlettFinder::checkRadius(vector<ColoredPoint>* points, double potRad){    
    // Graphenstruktur aufbauen
    // Variablen erzeugen
	Graph g;
	GraphData gData;
	CapacityMap capacity(g);


    // Graph Initialisieren
    graphFlow::buildupGraphFromRadius(g, gData, capacity, potRad, points);


    // Fluss berechnen
    int maxFlowValue = graphFlow::getMaxFlow(g, capacity, gData);


    // Vergleichwert holen
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();


    // Aufräumen
    delete(redPoints);
    
    // Zurückgeben ob Fluss groß genug ist
    return maxFlowValue >= nRed;
}










// * * * =========== Utility =========== * * * //
int fairlettFinder::mapIDtoIndexByColor(int ID, Pointcolor color, int nRed){
    // Farben-Fallunterscheidung
    if (color == RED)   { return ID; }
    if (color == BLUE)  { return ID - nRed; }
    
    // Fehlerfall  
    return -1;
}



void fairlettFinder::markSinglePointWithFairlett(int fairlettID, int nodeID, Pointcolor color, int nRed, vector<ColoredPoint>* points){
    // Die Nummer wievielter Punkt dieser Farbe der Punkt ist
    int colorIndex = mapIDtoIndexByColor(nodeID, color, nRed);

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
    // FairlettID an richtigem Punkt aktuallisieren
    points->at(trueIndex).setFairlettID(fairlettID);
    return;
}