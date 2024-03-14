#include "FairlettFinder.h"

//#include <iostream> // std::cout; std::endl

using namespace fairlettFinder;

// * * * =========== Calculating the Fairlets =========== * * * //
double fairlettFinder::markFairletts(vector<ColoredPoint>* points){
    // Farben richtig Sortieren
    makeCritFeatureSmalestFirst(points);

    // Optimalen Radius Finden
    double optRad = findPotentionalRadius(points);

    // Graph mit Optimalem Radius Aufbauen
    // Variablen erzeugen
	Graph g;
	GraphData gData;
	CapacityMap capacity(g);

    // Graph Initialisieren
    buildupGraphFromRadius(g, gData, capacity, optRad, points);

    // Fluss berechnen
    Flow* preflow = calculateFlow(g, capacity, gData);

    // Main-Kanten durchgehen und Partner markieren
    // Punkte Filtern
    vector<ColoredPoint>* redPoints = getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();
	//vector<ColoredPoint>* bluePoints = getPointsOfColor(points, BLUE);

    // Main Fairletts bilden
    int fairlettCounter = markMainNodes(g, *preflow, gData.mainArcs, nRed, points);    

    // Ausreißer markieren
    
    int numOfOutlier = markOutliers(g, *preflow, gData.targetArcs, nRed, points);

    // Debug
    printf("Anzahl an Fairletts: %d;\tAnzahl an Outlier: %d\n", fairlettCounter, numOfOutlier);

    // Aufräumen
    delete redPoints;
    //delete bluePoints;
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
        if (getFlowOfArc(preflow, mainArcs.at(i)) < 1){
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
        if (getFlowOfArc(preflow, targetArcs.at(i)) > 0){
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


void fairlettFinder::makeCritFeatureSmalestFirst(vector<ColoredPoint> *points)
{
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

    // Solange durchprobieren, bis ein Radius erfolgreich ist
    for (int i = 0; i < (int) potRadii->size(); i++){
        // Ist der Radius Groß genug
        if (checkRadius(points, potRadii->at(i))){
            // Funktionierenden Radius abspeichern
            double trueRadius = potRadii->at(i);
            // Aufräumen
            delete(potRadii);
            // Zurückgeben
            return trueRadius;
        }
        
    }
    // Fehlerfall
    printf("ERROR: Es können keine Fairlets gebildet werden. Größter Radius %f ist nicht groß genung\n", potRadii->back());
    delete potRadii;
    return -1.0;
}



vector<double>* fairlettFinder::calculateAllRadii(vector<ColoredPoint>* points){
    // Erstmal nach Blau und Rot filtern
    vector<ColoredPoint>* redPoints = getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = getPointsOfColor(points, BLUE);

    // Liste für alle Radien Anlegen
    vector<double>* potentalRadii = new vector<double>;

    // Alle möglichen Radien berechnen
    // Alle roten Punkte durchgehen
    for (int redIndex = 0; redIndex < (int) redPoints->size(); redIndex++){
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
    buildupGraphFromRadius(g, gData, capacity, potRad, points);


    // Fluss berechnen
    int maxFlowValue = getMaxFlow(g, capacity, gData);
    
    // Vergleichwert holen
    vector<ColoredPoint>* redPoints = getPointsOfColor(points, RED);
    int nRed = (int) redPoints->size();

    // Aufräumen
    delete(redPoints);

    // Zurückgeben ob Fluss groß genug ist
    return maxFlowValue >= nRed;
}






// * * * =========== Building the Graph and let it Flow =========== * * * //
void fairlettFinder::buildupGraphFromRadius(Graph& graph, GraphData& gData, CapacityMap& capacity, double potRad, vector<ColoredPoint>* points){
    // Knoten hinzufügen
	addNodesToGraph(graph, gData, points);

	// Kanten hinzufügen
	addArcsToGraph(graph, gData, potRad, points);

	// Kapazitäten hinzufügen
	addCapacitiesToGraph(capacity, gData);

}



void fairlettFinder::addNodesToGraph(Graph& graph, GraphData& gData, vector<ColoredPoint>* points){

    // Anzahl aller Punkte
    int n = (int) points->size();

    // Rote Knoten hinzufügen (Krit Feature = 0)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == RED){
            gData.redNodes.push_back(graph.addNode());
        }
    }
    //printf("Rote Knoten hinzugefügt\n");

    // Blaue Knoten hinzufügen (Krit Feature = 1)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == BLUE){
            gData.blueNodes.push_back(graph.addNode());
        }
    }
    //printf("Blaue Knoten hinzugefügt\n");

    // Quelle und Senke hinzufügen
    gData.s = graph.addNode();
    gData.t = graph.addNode();
    //printf("Quelle und Senke hinzugefügt\n");

    return; 
}



void fairlettFinder::addArcsToGraph(Graph& graph, GraphData& gData, double potRad, vector<ColoredPoint>* points){

    // Anzahl an Knoten herausfinden
    //int n = (int) points->size();
    int nRed = (int) gData.redNodes.size();
    int nBlue = (int) gData.blueNodes.size();


    // Kanten von s zu allen Roten Knoten
    for (int i = 0; i < nRed; i++){
        gData.sourceArcs.push_back(graph.addArc(gData.s, gData.redNodes.at(i)));
    }

    // Kanten von Blau zu t
    for (int i = 0; i < nBlue; i++){
        gData.targetArcs.push_back(graph.addArc(gData.blueNodes.at(i), gData.t));
    }


    // Kanten von Rot nach Blau, abhänging von ihrem Abstand (potRad)
    // Punkte in Farben Aufteilen
    vector<ColoredPoint>* redPoints = getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = getPointsOfColor(points, BLUE);

    // Kurzer Sanity Check
    if (nRed != (int) redPoints->size() || nBlue != (int) bluePoints->size()){
        printf("ERROR: Fehler bei Grapherstellung!\n");
        printf("Anzahl roter Knoten im Graph %d; \t Anzahl roter Punkte %ld\n", nRed, redPoints->size());
        printf("Anzahl blauer Knoten im Graph %d; \t Anzahl blauer Punkte %ld\n", nBlue, bluePoints->size());
    }
    
    // Alle roten Punkte durchgehen
    for (int redIndex = 0; redIndex < nRed; redIndex++){
        // Alle blauen Punkte durchgehen
        for (int blueIndex = 0; blueIndex < nBlue; blueIndex++){
            // Schauen ob das eine Passende Kante ist
            if (redPoints->at(redIndex).distTo(bluePoints->at(blueIndex)) < potRad){
                // Kante Hinzufügen
                gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(redIndex), gData.blueNodes.at(blueIndex)));
            } 
        } 
    }
    
    // Gefilterte Punkte wieder frei geben
    delete redPoints;
    delete bluePoints;

    return;
}



void fairlettFinder::addCapacitiesToGraph(CapacityMap& capacityMap, GraphData& gData){
    // Kapazität von Quelle zu allen Roten
    for (size_t i = 0; i < gData.sourceArcs.size(); i++){
        capacityMap[gData.sourceArcs.at(i)] = 1;
    }

    // Kapazität von allen Blauen zur Senke
    for (size_t i = 0; i < gData.targetArcs.size(); i++){
        capacityMap[gData.targetArcs.at(i)] = 1;
    }

    // Zwischenkanten Kapazität
    for (size_t i = 0; i < gData.mainArcs.size(); i++){
        capacityMap[gData.mainArcs.at(i)] = 1;
    }

}



Flow* fairlettFinder::calculateFlow(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Preflow-Object erstellen
    Flow* preflow = new Flow(graph, capacityMap, gData.s, gData.t);

    // Flussalgorithmus ausführen
    preflow->run();

    return preflow;
}


int fairlettFinder::getMaxFlow(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Flussalgorithmus laufen lassen
    Flow* flow = calculateFlow(graph, capacityMap, gData);

    // Wert abspeichern
    double flowValue = flow->flowValue();

    // Speicher wieder freigeben
    delete(flow);

    // Wert zurück geben
    return flowValue;
}



int fairlettFinder::getFlowOfArc(const Flow& flow, const Arc arc){
    int flowValue = flow.flow(arc);
    return flowValue;
}








// ==== Utility ==== //
vector<ColoredPoint>* fairlettFinder::getPointsOfColor(vector<ColoredPoint>* points, Pointcolor color){
    // Neuer Vector anlegen
    vector<ColoredPoint>* filteredPoints = new vector<ColoredPoint>;

    // Wie viele Punkte muss ich durchgehen
    int n = (int) points->size();

    for (int i = 0; i < n; i++){
        // Falls der Punkt die richtige Farbe hat, hinzufügen
        if(points->at(i).getColor() == color){
            filteredPoints->push_back(points->at(i));
        }
    }
    
    // den neuen, einfarbigen vector zurückgeben
    return filteredPoints;
}

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











// ==== Debugging ==== //
void fairlettFinder::printGraph(const Graph& graph, const GraphData& gData){
    // Grunddaten
    printf("=== Daten welche zum Graphen gespeichert sind ===\n");
    printf("Anzahl roter Knoten im Graphen: %d\n", (int) gData.redNodes.size());
    printf("Anzahl blauer Knoten im Graphen: %d\n", (int) gData.blueNodes.size());
    
    
    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
            node("first-red:", gData.redNodes.at(0)).// Erster Roter Knoten
            node("first-blue:", gData.blueNodes.at(0)).// Erster Roter Knoten
			node("source:", gData.s).                // write s to 'source'
			node("target:", gData.t).                // write t to 'target'
			run();
    return; 
}

void fairlettFinder::printGraphCapacity(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Grunddaten
    printf("=== Daten welche zum Graphen gespeichert sind ===\n");
    printf("Anzahl roter Knoten im Graphen: %d\n", (int) gData.redNodes.size());
    printf("Anzahl blauer Knoten im Graphen: %d\n", (int) gData.blueNodes.size());

    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
			arcMap("cap", capacityMap).             // write 'cost' for for arcs
            node("first-red:", gData.redNodes.at(0)).// Erster Roter Knoten
            node("first-blue:", gData.blueNodes.at(0)).// Erster Roter Knoten
			node("source:", gData.s).                // write s to 'source'
			node("target:", gData.t).                // write t to 'target'
			run();
    return; 
}

void fairlettFinder::printFlow(const Flow& preflow, const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Grunddaten
    printf("=== Daten welche zum Graphen gespeichert sind ===\n");
    printf("Anzahl roter Knoten im Graphen: %d\n", (int) gData.redNodes.size());
    printf("Anzahl blauer Knoten im Graphen: %d\n", (int) gData.blueNodes.size());
    // Maximaler Flussert ausgeben
    printf("Maximaler Flusswert: %d\nGraphausgabe:\n", preflow.flowValue());

    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
			arcMap("cap", capacityMap).             // write 'cost' for for arcs
			arcMap("flow", preflow.flowMap()).     // write 'flow' for for arcs
            node("first-red:", gData.redNodes.at(0)).// Erster Roter Knoten
            node("first-blue:", gData.blueNodes.at(0)).// Erster Roter Knoten
			node("source:", gData.s).                // write s to 'source'
			node("target:", gData.t).                // write t to 'target'
			run();
    return; 
}
