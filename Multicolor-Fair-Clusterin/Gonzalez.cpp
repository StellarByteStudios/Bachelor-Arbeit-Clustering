#include "Gonzalez.h"
#include <iostream> // std::cout; std::endl

double Gonzalez::makeGonzalez(vector<ColoredPoint>* points, int clusters){
	// Zählen wie viele Punkte (überhaubt genung für die Cluster) O(1)
	int n = (int) points->size();

	if(n < clusters){
		cout << "No valid ClusterCount" << endl;
		return -1.0;
	}

	// Array für die Minimalen Distanzen erzeugen O(1)
	// minDist = -1 => Punkt ist Zentrum
	double minDist[n];

	// Beliebiges erstes Zentrum wählen (Einfach Index 0) O(1)
	points->at(0).setToCenter();
	minDist[0] = -1.0;

	// Minimale Distanz ausrechnen O(n)
	for(int i = 1; i < n; i++){
		// Distanz zum einzigen gewählten Zentrum
		minDist[i] = points->at(0).distTo(points->at(i));
	}

	// Clusterzugehörigkeit eingragen O(n)
	for(int i = 0; i < n; i++){
		points->at(i).setCluster(0);
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
		points->at(maxIndex).setToCenter();
		points->at(maxIndex).setCluster(i);

		// Alle minimalen Distanzen aktuallisieren ggf. Clusterzugehörigkeit aktuallisieren O(n)
		for(int a = 0; a < n; a++){
			double distToNewCenter = points->at(maxIndex).distTo(points->at(a));
			if(distToNewCenter < minDist[a] ){
				// Distanz aktualliesieren
				minDist[a] = distToNewCenter;
				// Clusterzugehörigkeit Aktuallisieren
				points->at(a).setCluster(i);
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

	return maxRad;
}
