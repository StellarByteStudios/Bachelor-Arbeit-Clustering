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

void fairlettFinder::addArcsToGraph(Graph &, GraphData &, double, vector<ColoredPoint>* points){
}

void fairlettFinder::addCapacitiesToGraph(CapacityMap &, GraphData &){
}

Flow *fairlettFinder::calculateFlow(Graph &, CapacityMap &, GraphData &){
    return nullptr;
}

int fairlettFinder::getFlowOfArc(Flow &, Arc){
    return 0;
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
