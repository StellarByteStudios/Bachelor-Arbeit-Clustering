#include "Gonzalez.h"
#include <iostream> // std::cout; std::endl


Gonzalez::GonzalezReturnValues* Gonzalez::makeGonzalez(vector<ColoredPoint>* points, int clusters)
{
    // Zählen wie viele Punkte (überhaubt genung für die Cluster) O(1)
	int n = (int) points->size();

	if(n < clusters){
		cout << "ERROR: No valid ClusterCount of Gonzalez-Algorithm" << endl;
		return nullptr;
	}

	// Returnstruct erstellen, sodass wir mehrere Werte zurückgeben können
	GonzalezReturnValues* retValues = Gonzalez::createGonzalezReturns(points);

	// Array für die Minimalen Distanzen erzeugen O(1)
	// minDist = -1 => Punkt ist Zentrum
	double minDist[n];

	// Beliebiges erstes Zentrum wählen (Einfach Index 0) O(1)
	retValues->clusteredPoints->at(0).setToCenter();
	retValues->clusteredPoints->at(0).setCluster(0);
	retValues->centers->push_back(retValues->clusteredPoints->at(0));
	minDist[0] = -1.0;

	// Minimale Distanz ausrechnen O(n)
	for(int i = 1; i < n; i++){
		// Distanz zum einzigen gewählten Zentrum
		minDist[i] = retValues->clusteredPoints->at(0).distTo(retValues->clusteredPoints->at(i));
	}

	// Clusterzugehörigkeit eingragen O(n)
	for(int i = 0; i < n; i++){
		retValues->clusteredPoints->at(i).setCluster(0);
	}

	// So oft wie man Cluster haben will O(k)
	for(int i = 1; i < clusters; i++){
		// Die Größte Distanz zu allen Clustern bestimmen (max von d_min) O(n)
		double maxDist = minDist[0];
		int maxIndex = 0;

		for(int a = 1; a < n; a++){
			if( maxDist < minDist[a]){
				maxDist = minDist[a];
				maxIndex = a;
			}
		}

		// Diesen Punkt zu neuem Zentrum machen O(1)
		retValues->clusteredPoints->at(maxIndex).setToCenter();
		retValues->clusteredPoints->at(maxIndex).setCluster(i);
		retValues->centers->push_back(retValues->clusteredPoints->at(maxIndex));
		minDist[maxIndex] = -1.0; // Soll nicht noch einem anderem Cluster zugeteilt werden

		// Alle minimalen Distanzen aktuallisieren ggf. Clusterzugehörigkeit aktuallisieren O(n)
		// Aber nur wenn nicht selbst schon Zentrum
		for(int a = 0; a < n; a++){
			double distToNewCenter = retValues->clusteredPoints->at(maxIndex).distTo(retValues->clusteredPoints->at(a));
			if(distToNewCenter < minDist[a] ){
				// Distanz aktualliesieren
				minDist[a] = distToNewCenter;
				// Clusterzugehörigkeit Aktuallisieren
				retValues->clusteredPoints->at(a).setCluster(i);
			}
		}

	}

	// maximalen Radius zurückgeben (max of d_min)
	double maxRad = minDist[0];
	for(int a = 1; a < n; a++){
		if(maxRad < minDist[a]){
			maxRad = minDist[a];
		}
	}

	retValues->maxRadius = maxRad;
	return retValues;
}

Gonzalez::GonzalezReturnValues* Gonzalez::createGonzalezReturns(vector<ColoredPoint>* originalPoints){
	GonzalezReturnValues* values = new GonzalezReturnValues();
	
	// Vielleicht hier schon Deep-Copy
	values->clusteredPoints = new vector<ColoredPoint>(*originalPoints);
	values->centers = new vector<ColoredPoint>();
	values->maxRadius = -1.0;

    return values;
}

void Gonzalez::deleteGonzalezReturns(GonzalezReturnValues* values){
	delete values->clusteredPoints;
	delete values->centers;
	delete values;
}




Gonzalez::GonzalezReturnValues* Gonzalez::makeAwareGonzalez(vector<ColoredPoint>* points, int clusters)
{
    // Zählen wie viele Punkte (überhaubt genung für die Cluster) O(1)
	int n = (int) points->size();

	if(n < clusters){
		cout << "ERROR: No valid ClusterCount of Gonzalez-Algorithm" << endl;
		return nullptr;
	}

	// Returnstruct erstellen, sodass wir mehrere Werte zurückgeben können
	GonzalezReturnValues* retValues = Gonzalez::createGonzalezReturns(points);

	// Array für die Minimalen Distanzen erzeugen O(1)
	// minDist = -1 => Punkt ist Zentrum
	double minDist[n];

	// Beliebiges erstes Zentrum wählen (Einfach Index 0) O(1)
	retValues->clusteredPoints->at(0).setToCenter();
	retValues->clusteredPoints->at(0).setCluster(0);
	retValues->centers->push_back(retValues->clusteredPoints->at(0));
	minDist[0] = -1.0;


	// Minimale Distanz ausrechnen O(n)
	for(int i = 1; i < n; i++){
		// Distanz zum einzigen gewählten Zentrum
		minDist[i] = retValues->clusteredPoints->at(0).distTo(retValues->clusteredPoints->at(i));
	}

	// ======= Aware Code =======
	// Partner berücksichtigen
	int partnerIndex = getIndexOfPartner(retValues->clusteredPoints->at(0), 0, retValues->clusteredPoints);
	if (partnerIndex >= 0){
		minDist[partnerIndex] = -1.0;
		retValues->clusteredPoints->at(partnerIndex).setCluster(0);
	}
	// ======= =======

	// Clusterzugehörigkeit eingragen O(n)
	for(int i = 0; i < n; i++){
		retValues->clusteredPoints->at(i).setCluster(0);
	}

	// So oft wie man Cluster haben will O(k)
	for(int i = 1; i < clusters; i++){
		// Die Größte Distanz zu allen Clustern bestimmen (max von d_min) O(n)
		double maxDist = minDist[0];
		int maxIndex = 0;

		for(int a = 1; a < n; a++){
			if( maxDist < minDist[a]){
				maxDist = minDist[a];
				maxIndex = a;
			}
		}

		// Diesen Punkt zu neuem Zentrum machen O(1)
		retValues->clusteredPoints->at(maxIndex).setToCenter();
		retValues->clusteredPoints->at(maxIndex).setCluster(i);
		retValues->centers->push_back(retValues->clusteredPoints->at(maxIndex));
		minDist[maxIndex] = -1.0; // Soll nicht noch einem anderem Cluster zugeteilt werden

		// ======= Aware Code =======
		// Partner berücksichtigen
		int partnerIndex = getIndexOfPartner(retValues->clusteredPoints->at(maxIndex), maxIndex, retValues->clusteredPoints);
		if (partnerIndex >= 0){
			minDist[partnerIndex] = -1.0;
			retValues->clusteredPoints->at(partnerIndex).setCluster(i);
		}
		// ======= =======

		// Alle minimalen Distanzen aktuallisieren ggf. Clusterzugehörigkeit aktuallisieren O(n)
		// Aber nur wenn nicht selbst schon Zentrum
		for(int a = 0; a < n; a++){
			double distToNewCenter = retValues->clusteredPoints->at(maxIndex).distTo(retValues->clusteredPoints->at(a));
			if(distToNewCenter < minDist[a] ){
				// Distanz aktualliesieren
				minDist[a] = distToNewCenter;
				// Clusterzugehörigkeit Aktuallisieren
				retValues->clusteredPoints->at(a).setCluster(i);
			}
		}
	}

	// maximalen Radius zurückgeben (max of d_min)
	double maxRad = minDist[0];
	for(int a = 1; a < n; a++){
		if(maxRad < minDist[a]){
			maxRad = minDist[a];
		}
	}

	retValues->maxRadius = maxRad;
	return retValues;
}


int Gonzalez::getIndexOfPartner(ColoredPoint widow, int widowIndex, vector<ColoredPoint>* points){

	for (int i = 0; i < (int) points->size(); i++){
		// Widow Punkt selbst überspringen
		if (i == widowIndex){
			continue;
		}
		
		// Partner gefunden
		if (widow.getFairlettID() == points->at(i).getFairlettID()){
			return i;
		}
	}
	
	// Keinen Partner gefunden
	return -1;
}