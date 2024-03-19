#include "RedCenterClustering.h"

#include <iostream> // std::cout; std::endl

void printAllpointsHere(vector<ColoredPoint>* points);


// * * * =========== Using the Algorithm =========== * * * //
redclustering::FairFlowReturnValues* redclustering::makeFairRedClustering(vector<ColoredPoint>* points, int k){
   
    return nullptr;
}

redclustering::FairFlowReturnValues* redclustering::createFairFlowReturns(vector<ColoredPoint>* originalPoints){
    FairFlowReturnValues* values = new FairFlowReturnValues();

    // Deep-Copy der Punkte
    values->clusteredPoints = new vector<ColoredPoint>(*originalPoints);
    values->centers = new vector<ColoredPoint>();
	values->maxRadius = -1.0;    
    
    return values;
}

void redclustering::deleteFairFlowReturns(FairFlowReturnValues* values){
    delete values->clusteredPoints;
	delete values->centers;
	delete values;
}











// * * * =========== Clustering with Fairlets =========== * * * //
void redclustering::clusterRedPoints(FairFlowReturnValues* returnValues, int k){
    // Nur Rote Punkte holen
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(returnValues->clusteredPoints, RED);

    // Gonzalez mit Roten Punkten
    Gonzalez::GonzalezReturnValues* gonzalezValues = Gonzalez::makeGonzalez(redPoints, k);

    // Punkte in Clustered Points aktuallisieren
    updateClusterOfMainRedPoints(returnValues->clusteredPoints, returnValues->centers, gonzalezValues->clusteredPoints);

    // Speicher wieder Freigeben
    delete redPoints;
    Gonzalez::deleteGonzalezReturns(gonzalezValues);
}



double redclustering::calculateMaxRadius(vector<ColoredPoint> clusteredPoints, int k){
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

void redclustering::updateClusterOfMainRedPoints(vector<ColoredPoint>* realPoints, vector<ColoredPoint>* centers, vector<ColoredPoint>* filteredPoints){
    // Index, wievielter Punkt zugeteilt wurde
    int filterIndex = 0;
    
    // Durch alle Punkte (Alle Farben) durchgehen
    for (int i = 0; i < (int) realPoints->size(); i++){
        // Falls das ein roter Punkt ist must dieser Aktuallisiert werden
        if (realPoints->at(i).getColor() == RED){
            // Überschreiben des Clusters mit der Nummer die der Gefilterte Punkt hatte
            realPoints->at(i).setCluster(filteredPoints->at(filterIndex).getCluster());

            // Noch überprüfen ob der Punkt vielleicht ein Zentrum ist
            if (filteredPoints->at(filterIndex).getIsCenter()){
                realPoints->at(i).setToCenter();
                centers->push_back(realPoints->at(i));
            }

            // einen Punkt bei den Gefilterten weiter gehen
            filterIndex++;
        }
        
    }
    
    // Sanity-Check
    if(filterIndex < (int) filteredPoints->size()){
        printf("ERROR: von den %d an roten Punkten wurden nicht alle benutzt zum Aktuallisieren sondern nur %d\n", (int) filteredPoints->size(), filterIndex);
    }

}

void redclustering::updateClusterOfBluePoints(vector<ColoredPoint> *){
}



void printAllpointsHere(vector<ColoredPoint>* points){
    cout << "\n\n===== Printing all given Points =====\n" << endl;

    for (size_t i = 0; i < points->size(); i++){
        cout << i << ": " << points->at(i).toString() << endl;
    }
}