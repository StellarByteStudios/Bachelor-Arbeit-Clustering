#include "FairlettFinder.h"

#include <iostream> // std::cout; std::endl

using namespace fairlettFinder;


// * * * =========== Using the Algorithm =========== * * * //
FairFlowReturnValues makeFairFlowClustering(vector<ColoredPoint> *, int){
    return FairFlowReturnValues();
}

FairFlowReturnValues *fairlettFinder::createGonzalezReturns(vector<ColoredPoint> *){
    return nullptr;
}

void fairlettFinder::deleteFairFlowReturns(FairFlowReturnValues *){
}





// * * * =========== Building the Graph and let it Flow =========== * * * //

void fairlettFinder::addNodesToGraph(Graph &, GraphData &){
}

void fairlettFinder::addArcsToGraph(Graph &, GraphData &, double){
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
