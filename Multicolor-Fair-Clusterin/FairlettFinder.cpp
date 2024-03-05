#include "FairlettFinder.h"

#include <iostream> // std::cout; std::endl

using namespace fairlettFinder;


// * * * =========== Using the Algorithm =========== * * * //
FairFlowReturnValues* fairlettFinder::makeFairFlowClustering(vector<ColoredPoint> *, int){
    return nullptr;
}

FairFlowReturnValues* fairlettFinder::createGonzalezReturns(vector<ColoredPoint> *){
    return nullptr;
}

void fairlettFinder::deleteFairFlowReturns(FairFlowReturnValues *){
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

double fairlettFinder::findPotentionalRadius(vector<ColoredPoint> *){
    return 0.0;
}






// * * * =========== Calculating the Fairlets =========== * * * //

void fairlettFinder::makeCritFeatureSmalestFirst(vector<ColoredPoint> *){
}

void fairlettFinder::markFairletts(vector<ColoredPoint> *){
}










// * * * =========== Clustering with Fairlets =========== * * * //
void fairlettFinder::clusterRedPoints(vector<ColoredPoint> *){
}

vector<ColoredPoint> *fairlettFinder::filterRedPoints(vector<ColoredPoint> *){
    return nullptr;
}

double fairlettFinder::calculateMaxRadius(vector<ColoredPoint> clusteredPoints, int k){
    // Liste für die Radii aller Cluster anlegen
    vector<double> allMaxRadii;
    // Hilfsvariable
    int n = (int) clusteredPoints.size();

    // Itterieren durch jede Clusternummer
    // (outlier egal, da diese Radius 0 haben)
    for (int cluster = 0; cluster < k; cluster++) {
        
        // Suche Zentrum dieses Clusters
        ColoredPoint center = ColoredPoint(-1, RED, nullptr);
        for (int i = 0; i < n; i++) {
            if (clusteredPoints.at(i).getCluster() == cluster 
            && clusteredPoints.at(i).getIsCenter()){
                center = clusteredPoints.at(i);
            } 
        }
        
        // Berechne Distanz zu jedem Knoten, welcher Teil des Clusters ist
        // Aktuallisiere ggf den max Radius
        double potMaxRad = -1;
        for (int i = 0; i < n; i++){
            // Suche alle Knoten die zu diesem Cluster gehören
            if (clusteredPoints.at(i).getCluster() == cluster){
                // Distanz zum Zentrum messen
                double distance = center.distTo(clusteredPoints.at(i));
                // Aktuallierung des maxRadius
                if (distance > potMaxRad){
                    potMaxRad = distance;
                }
            }
            
        }

        // Potenzieller Radius der Liste hinzufügen
        allMaxRadii.push_back(potMaxRad);
        
        
    }

    // wares Maximum aus allen möglichen rausholen
    double trueMaxRadius = -1;
    for (int i = 0; i < (int) allMaxRadii.size(); i++) {
        if (allMaxRadii.at(i) > trueMaxRadius){
            trueMaxRadius = allMaxRadii.at(i);
        }
    }
    

    return trueMaxRadius;
}

void fairlettFinder::updateClusterOfBluePoints(vector<ColoredPoint> *){
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
