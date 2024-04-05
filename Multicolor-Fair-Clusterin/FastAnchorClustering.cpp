#include "FastAnchorClustering.h"
#include <iostream> // std::cout; std::endl

#ifdef PROCESS_BAR
    #define printProcess(process) std::cout << process << endl;
#else
    #define printProcess(process)
#endif




// * * * =========== Using the Algorithm =========== * * * //
fastAnchorClustering::FastAnchorReturnValues* fastAnchorClustering::makeFastAnchorClustering(vector<ColoredPoint>* points, int k){
    // Rückgabestruct erzeugen
    fastAnchorClustering::FastAnchorReturnValues* fairValues = fastAnchorClustering::createFastAnchorReturns(points);
    
    // Fairletts markieren
    double fairlettRadius = fastAnchorFairlett::markFairletts(fairValues->clusteredPoints);
    fairValues->maxFairlettRadius = fairlettRadius;

 
    // ==== Clustering berechnen ====



    // maximalen Radius der Cluster berechnen
    fairValues->maxClusterRadius = calculateMaxRadius(*fairValues->clusteredPoints, k); 


    return fairValues;
}


fastAnchorClustering::FastAnchorReturnValues* fastAnchorClustering::createFastAnchorReturns(vector<ColoredPoint>* originalPoints){
    FastAnchorReturnValues* values = new FastAnchorReturnValues();

    // Deep-Copy der Punkte
    values->clusteredPoints = new vector<ColoredPoint>(*originalPoints);
    values->centers = new vector<ColoredPoint>();
	values->maxClusterRadius = -1.0;  
    values->maxFairlettRadius = -1.0;   
    
    return values;
}


void fastAnchorClustering::deleteFastAnchorReturns(FastAnchorReturnValues* values){
    delete values->clusteredPoints;
	delete values->centers;
	delete values;
}











// * * * =========== Clustering with Fairlets =========== * * * //
void fastAnchorClustering::clusterFairlettPoints(FastAnchorReturnValues* returnValues, int k){
    // Nur Punkten welche zu einem Fairlett gehören holen
    vector<ColoredPoint>* fairlettPoints = ColoredPoint::getPointsOfFairletts(returnValues->clusteredPoints);

    // Gonzalez mit Punkten welche zu einem Fairlett gehören
    Gonzalez::GonzalezReturnValues* gonzalezValues = Gonzalez::makeGonzalez(fairlettPoints, k);

    // ============================

    // Punkte in Clustered Points aktuallisieren
    // erstmal Zentren aktuallisieren

    // Partner der Zentren zuweißen

    // Alle anderen Punkte welche keine Ausreißer sind ihr Cluster zuweißen

    // ============================
    // Speicher wieder Freigeben
    delete fairlettPoints;
    Gonzalez::deleteGonzalezReturns(gonzalezValues);
}




void fastAnchorClustering::updateClusterOfMainPoints(vector<ColoredPoint>* realPoints, vector<ColoredPoint>* centers, vector<ColoredPoint>* filteredPoints){
    // Nearest Center berechnen
    
    
    
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

    // Nearest Center wieder freigeben

}







// * * * =========== Utility =========== * * * //
double fastAnchorClustering::calculateMaxRadius(vector<ColoredPoint> clusteredPoints, int k){
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
                break;
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






vector<int>* fastAnchorClustering::getNearesCenters(vector<ColoredPoint>* points, vector<ColoredPoint>* centers){
    // Neues Array erstellen
    vector<int>* nearestCenters = new vector<int>();
    nearestCenters->resize(points->size());

    // Für jeden Punkt sein nächstes Cluster suchen
    for (int i = 0; i < (int) points->size(); i++){
        nearestCenters->at(i) = getNextCenterOfPoint(points->at(i), centers);
    }
    
    return nearestCenters;
}


int fastAnchorClustering::getNextCenterOfPoint(ColoredPoint singlePoint, vector<ColoredPoint>* centers){
    // Als Startwert mal das erste Zentrum wählen
    int nearestCluster = 0;
    double closestDistance = singlePoint.distTo(centers->at(0));

    // Durch alle anderen Zentren durchgehen und schauen ob es näher dran ist
    for (int i = 1; i < (int) centers->size(); i++){
        // Neue Distanz berechnen
        double newDistance = singlePoint.distTo(centers->at(i));

        // Ist dieses Zentrum besser?
        if (newDistance < closestDistance){
            // Neue Daten abspeichern
            nearestCluster = i;
            closestDistance = newDistance;
        }
    }

    return nearestCluster;
}