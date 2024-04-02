#include "RedCenterClustering.h"
#include <iostream> // std::cout; std::endl

#ifdef PROCESS_BAR
    #define printProcess(process) std::cout << process << endl;
#else
    #define printProcess(process)
#endif




// * * * =========== Using the Algorithm =========== * * * //
redclustering::FairFlowReturnValues* redclustering::makeFairRedClustering(vector<ColoredPoint>* points, int k){
    // Rückgabestruct erzeugen
    redclustering::FairFlowReturnValues* fairValues = redclustering::createFairFlowReturns(points);
    
    // Fairletts markieren
    double fairlettRadius = fairlettFinder::markFairletts(fairValues->clusteredPoints);
    fairValues->maxFairlettRadius = fairlettRadius;

    // Clustern nur mit roten Punkten
	clusterRedPoints(fairValues, k);
    //printf("--clustered only red Points-- ");
    printProcess("--clustered only red Points-- ")

    // Blaue Punkte über Fairletts zuweißen
    updateClusterOfBluePoints(fairValues->clusteredPoints);
    //printf("--updated all Clusters with Fairlett-- \n");
    printProcess("--updated all Clusters with Fairlett-- ")

    // maximalen Radius der Cluster berechnen
    fairValues->maxClusterRadius = calculateMaxRadius(*fairValues->clusteredPoints, k); 


    return fairValues;
}


redclustering::FairFlowReturnValues* redclustering::createFairFlowReturns(vector<ColoredPoint>* originalPoints){
    FairFlowReturnValues* values = new FairFlowReturnValues();

    // Deep-Copy der Punkte
    values->clusteredPoints = new vector<ColoredPoint>(*originalPoints);
    values->centers = new vector<ColoredPoint>();
	values->maxClusterRadius = -1.0;  
    values->maxFairlettRadius = -1.0;   
    
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



void redclustering::updateClusterOfBluePoints(vector<ColoredPoint>* points){

    // Alle Punkte durchgehen
    for (int i = 0; i < (int) points->size(); i++){
        // Wenn ein Blauer Punkt gefunden wurde
        if (points->at(i).getColor() == BLUE){
            // FairlettID == -2 -> Überspringen (Ausreißer)
            if (points->at(i).getFairlettID() == -2){
                continue;
            }
            // Suche seinen Partner (Index)
            int partnerIndex = getRedFairlettPartnerIndex(points, points->at(i).getFairlettID());
            
            // hole Cluster-Nummer von diesem
            int clusterID = points->at(partnerIndex).getCluster();

            // Aktuallisiere blauen Punkt
            points->at(i).setCluster(clusterID);
        }
    }  
}



int redclustering::getRedFairlettPartnerIndex(vector<ColoredPoint>* points, int searchID){
    // Alle Punkte durchgehen
    for (int i = 0; i < (int) points->size(); i++){
        // Ist es ein roter Punkt und passt die FairlettID zusammen
        if (points->at(i).getColor() == RED && points->at(i).getFairlettID() == searchID){
            // Index des Roten Punktes zurückgeben
            return i;
        }
    }
    // Fehlerfall
    return -1;
}