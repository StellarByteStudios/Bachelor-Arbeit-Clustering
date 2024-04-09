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
    printProcess("-finished marking of fairlets");
 
    // ==== Clustering berechnen ====
    clusterFairlettPoints(fairValues, k);
    printProcess("-finished clustering");


    // maximalen Radius der Cluster berechnen
    fairValues->maxClusterRadius = calculateMaxRadius(*fairValues->clusteredPoints, k); 
    printProcess("-finished maxRadius Calc");

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
    //printProcess("========== before Gonzalez");
    //printf("Wie viele Punke gibt es, welche in fairletts sind?: %d\n", (int) fairlettPoints->size());

    // Gonzalez mit Punkten welche zu einem Fairlett gehören
    Gonzalez::GonzalezReturnValues* gonzalezValues = Gonzalez::makeAwareGonzalez(fairlettPoints, k);
    printProcess("----made Gonzalez with only Fairlett-points");

    // Punkte in Clustered Points aktuallisieren
    // erstmal Zentren aktuallisieren
    updateCentersOfMainPoints(returnValues->clusteredPoints, returnValues->centers, gonzalezValues->clusteredPoints);
    printProcess("----updated the centers");

    // Partner der Zentren zuweißen
    updateCenterPartners(returnValues->clusteredPoints, returnValues->centers);
    printProcess("----updated Partner of centers");

    // Alle anderen Punkte welche keine Ausreißer sind ihr Cluster zuweißen
    updateClusterOfMainPoints(returnValues->clusteredPoints, returnValues->centers);
    printProcess("----updated the rest of the points");

    // Speicher wieder Freigeben
    delete fairlettPoints;
    Gonzalez::deleteGonzalezReturns(gonzalezValues);
}




void fastAnchorClustering::updateClusterOfMainPoints(vector<ColoredPoint>* markedPoints, vector<ColoredPoint>* centers){
    // Nearest Center berechnen
    vector<int>* nearestCenters = getNearesCenters(markedPoints, centers);
    
    // Durch alle Punkte (Alle Farben) durchgehen
    for (int i = 0; i < (int) markedPoints->size(); i++){
        // Falls das ein Ausreißer-Punkt ist muss dieser nicht Aktuallisiert werden
        if (markedPoints->at(i).getFairlettID() < 0){
            continue;
        }
        
        // wenn er schon hinzugefügt wurde überspringen (Zentren und ihre Partner)
        if (markedPoints->at(i).getCluster() >= 0){
            // einen Punkt bei den Gefilterten weiter gehen
            continue;
        }

        // Überschreiben des Clusters mit dem, welchem der Anker am nächsten ist
        int anchorID = markedPoints->at(i).getAnchorID();
        markedPoints->at(i).setCluster(nearestCenters->at(anchorID)); 
    }

    // Nearest Center wieder freigeben
    delete(nearestCenters);
}



void fastAnchorClustering::updateCentersOfMainPoints(vector<ColoredPoint>* markedPoints, vector<ColoredPoint>* centers, vector<ColoredPoint>* clusteredPoints){
    // Index, wievielter Punkt zugeteilt wurde
    int filterIndex = 0;
    
    // Durch alle Punkte (Alle Farben) durchgehen
    for (int i = 0; i < (int) markedPoints->size(); i++){
        // Falls das kein Ausreißer ist, muss er aktuallisiert werden
        if (markedPoints->at(i).getFairlettID() >= 0){
            // Wenn es ein Zentrum ist, sich selbst zuweisen
            if (clusteredPoints->at(filterIndex).getIsCenter()){
                // Punkt in Rückgabeliste zum Zentrum machen
                markedPoints->at(i).setToCenter();
                // Punkt in Rückgabeliste zum Cluster zuweißen, welches die gefilterten Punkte von Gonzalez bekommen haben
                markedPoints->at(i).setCluster(clusteredPoints->at(filterIndex).getCluster());
                // Punkt noch der Zentrenliste zuweißen
                centers->push_back(markedPoints->at(i));
            }
            // einen Punkt bei den Gefilterten weiter gehen
            filterIndex++;
        }
        
    }
    
    // Sanity-Check
    if(filterIndex < (int) clusteredPoints->size()){
        printf("ERROR: von den %d an Punkten in Fairletts wurden nicht alle benutzt zum Aktuallisieren sondern nur %d\n", (int) clusteredPoints->size(), filterIndex);
    }
}


void fastAnchorClustering::updateCenterPartners(vector<ColoredPoint>* markedPoints, vector<ColoredPoint>* centers){
    int pointUpdates = 0;
    // Durch alle Punkte (Alle Farben) durchgehen
    for (int i = 0; i < (int) markedPoints->size(); i++){
        // Falls das ein Ausreißer ist, muss er nicht aktuallisiert werden
        if (markedPoints->at(i).getFairlettID() < 0){
            continue;
        }
        
        // Default wert --> Partner ist kein Zentrum
        int partnerCenter = -1;

        // Alle Zentren durchgehen, ob eines davon der Partner vom Punkt i ist
        for (int centerIndex = 0; centerIndex < (int) centers->size(); centerIndex++){
            // Tatsächlich Partner gefunden
            if (centers->at(centerIndex).getFairlettID() == markedPoints->at(i).getFairlettID()){
                partnerCenter = centerIndex;
                // Schleife kann abgebrochen werden
                break;
            }
            
        }
        
        // Wenn es ein Zentrum-Partner ist, muss er aktualisiert werden
        if (partnerCenter >= 0){
            // Punkt aktuallisieren und zum Cluster seinen Partners hinzufügen
            markedPoints->at(i).setCluster(centers->at(partnerCenter).getCluster());
            pointUpdates++;
        }
        
    }
    
    // Sanity-Check
    if(pointUpdates < (int) centers->size()){
        printf("ERROR: von den %d an roten Punkten wurden nicht alle benutzt zum Aktuallisieren sondern nur %d\n", (int) centers->size(), pointUpdates);
    }
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