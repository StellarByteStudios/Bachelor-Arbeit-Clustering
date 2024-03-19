#include "FairlettFinder.h"

#include <chrono>

using namespace std::chrono;

// * * * =========== Calculating the Fairlets =========== * * * //
double fairlettFinder::markFairletts(vector<ColoredPoint>* points){
    // Farben richtig Sortieren
    makeCritFeatureSmalestFirst(points);
    printf("--smallFeature-- ");

    // Optimalen Radius Finden
    double optRad = findPotentionalRadius(points);
    printf("--found potRad-- ");

    // Graph mit Optimalem Radius Aufbauen
    // Variablen erzeugen
	Graph g;
	GraphData gData;
	CapacityMap capacity(g);

    // Graph Initialisieren
    graphFlow::buildupGraphFromRadius(g, gData, capacity, optRad, points);
    printf("--build Graph-- ");

    // Fluss berechnen
    Flow* preflow = graphFlow::calculateFlow(g, capacity, gData);
    printf("--Made Flow-- ");

    // Main-Kanten durchgehen und Partner markieren
    // Punkte Filtern
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();


    // Main Fairletts bilden
    int fairlettCounter = markMainNodes(g, *preflow, gData.mainArcs, nRed, points);
    printf("--marked Fairlets-- ");    

    // Ausreißer markieren
    int numOfOutlier = markOutliers(g, *preflow, gData.targetArcs, nRed, points);
    printf("--marked outlier-- ");

    // Debug
    printf("Anzahl an Fairletts: %d;\tAnzahl an Outlier: %d\n", fairlettCounter, numOfOutlier);

    // Aufräumen
    delete redPoints;
    delete preflow;

    return optRad;
}


int fairlettFinder::markMainNodes(const Graph& g, const Flow& preflow, 
                                    vector<Arc> mainArcs, int nRed, 
                                    vector<ColoredPoint>* points){
    //int nRed = (int) redPoints->size();

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


double fairlettFinder::findPotentionalRadius(vector<ColoredPoint>* points){
    // Alle möglichen Radien berechnen
    vector<double>* potRadii = calculateAllRadii(points);
    printf("\nChecking %d potentional Radii\n", (int) potRadii->size());
    int checkedNumbers = 0;

    // Solange durchprobieren, bis ein Radius erfolgreich ist
    for (int i = 0; i < (int) potRadii->size(); i++){
        // Ist der Radius Groß genug
        if (checkRadius(points, potRadii->at(i))){
            // Funktionierenden Radius abspeichern
            double trueRadius = potRadii->at(i);
            // Aufräumen
            delete(potRadii);

            printf("\n");

            // Zurückgeben
            return trueRadius;
        }

        printf("Check: %d---------------------------------------------------\n\n", checkedNumbers);
        // Progressbar
        if (checkedNumbers > (int) potRadii->size()/100){
            printf("-c%%-");
            checkedNumbers = 0;
        }
        

        checkedNumbers++;        
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
    
    time_point startTime = high_resolution_clock::now();
    // Graphenstruktur aufbauen
    // Variablen erzeugen
	Graph g;
	GraphData gData;
	CapacityMap capacity(g);

    time_point timeAfterGraphVar = high_resolution_clock::now();
    printf("Zeit für Variablen anlegen: %ld µSec\n", duration_cast<microseconds>(timeAfterGraphVar - startTime).count());



    // Graph Initialisieren
    graphFlow::buildupGraphFromRadius(g, gData, capacity, potRad, points);

    time_point timeAfterGraphBuildup = high_resolution_clock::now();
    printf("Zeit für Graph aufbauen: %ld µSec\n", duration_cast<microseconds>(timeAfterGraphBuildup - timeAfterGraphVar).count());



    // Fluss berechnen
    int maxFlowValue = graphFlow::getMaxFlow(g, capacity, gData);

    time_point timeAfterFlow = high_resolution_clock::now();
    printf("Zeit für Fluss Berechnen: %ld µSec\n", duration_cast<microseconds>(timeAfterFlow - timeAfterGraphBuildup).count());


    // Vergleichwert holen
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();

    time_point timeAfterPointfilter = high_resolution_clock::now();
    printf("Zeit für Rot Filtern: %ld µSec\n", duration_cast<microseconds>(timeAfterPointfilter - timeAfterFlow).count());



    // Aufräumen
    delete(redPoints);
    //printf("Finished checking Radius %f\n", potRad);
    // Zurückgeben ob Fluss groß genug ist
    return maxFlowValue >= nRed;
}










// ==== Utility ==== //

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

    ///*
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
        
    }//*/

    // Noch unklar welche Variante ich benutze
    /*
    // Index des entsprechenden Punktes suchen
    int trueIndex = -1;
    // So lange durchgehen bis ich den richtigen Index gefunden
    while (colorIndex >= 0) {
        trueIndex++;

        // Hat der Knoten die richtige Farbe?
        if (points->at(trueIndex).getColor() == color){
                colorIndex--;
        }
    }*/

    points->at(trueIndex).setFairlettID(fairlettID);

    return;
}