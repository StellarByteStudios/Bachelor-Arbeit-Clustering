#include "FairlettFinder.h"

#include <iostream> // std::cout; std::endl

using namespace fairlettFinder;

// * * * =========== Calculating the Fairlets =========== * * * //


void fairlettFinder::markFairletts(vector<ColoredPoint> *){
}

void fairlettFinder::makeCritFeatureSmalestFirst(vector<ColoredPoint> *){
}

double fairlettFinder::findPotentionalRadius(vector<ColoredPoint> *){
    return 0.0;
}


// * * * =========== Building the Graph and let it Flow =========== * * * //
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
    /*
    for (size_t i = 0; i < 9; i++){
        gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(i), gData.blueNodes.at(i+1)));
    }
    // Letzte Quer-Kante
    gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(9), gData.blueNodes.at(0)));
    */
    return;
}

void fairlettFinder::addCapacitiesToGraph(CapacityMap &, GraphData &){
}

Flow *fairlettFinder::calculateFlow(Graph &, CapacityMap &, GraphData &){
    return nullptr;
}

int fairlettFinder::getFlowOfArc(Flow &, Arc){
    return 0;
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











// ==== Debugging ==== //
void fairlettFinder::printGraph(Graph& graph, GraphData& gData){
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

void fairlettFinder::printGraphCapacity(Graph& graph, CapacityMap& capacityMap, GraphData& gData){
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

void fairlettFinder::printFlow(Flow* preflow, Graph& graph, CapacityMap& capacityMap, GraphData& gData){
    // Grunddaten
    printf("=== Daten welche zum Graphen gespeichert sind ===\n");
    printf("Anzahl roter Knoten im Graphen: %d\n", (int) gData.redNodes.size());
    printf("Anzahl blauer Knoten im Graphen: %d\n", (int) gData.blueNodes.size());
    // Maximaler Flussert ausgeben
    printf("Maximaler Flusswert: %d\nGraphausgabe:\n", preflow->flowValue());

    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
			arcMap("cap", capacityMap).             // write 'cost' for for arcs
			arcMap("flow", preflow->flowMap()).     // write 'flow' for for arcs
            node("first-red:", gData.redNodes.at(0)).// Erster Roter Knoten
            node("first-blue:", gData.blueNodes.at(0)).// Erster Roter Knoten
			node("source:", gData.s).                // write s to 'source'
			node("target:", gData.t).                // write t to 'target'
			run();
    return; 
}
