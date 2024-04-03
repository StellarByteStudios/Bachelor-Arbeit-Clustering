#pragma once
#include <vector>

#include "ColoredPoint.h"
#include "Gonzalez.h"
#include "FastAnchorFairlett.h"


using namespace std;

namespace fastAnchorClustering{
    struct FastAnchorReturnValues{
		vector<ColoredPoint>* clusteredPoints;
		vector<ColoredPoint>* centers;
		double maxClusterRadius;
        double maxFairlettRadius;
	};

    // Method which uses the Max-Flow and Gonzalez Algorithm to cluster an unfair amount of Points
    FastAnchorReturnValues* makeFastAnchorClustering(vector<ColoredPoint>*, int);  // === TO-DO ===

    // Creating an empty Struct for Max-Flow-Clustering
	FastAnchorReturnValues* createFastAnchorReturns(vector<ColoredPoint>*);  // === TO-DO ===

	// Clean-Up for Max-Flow-Clustering Returnvalues
	void deleteFastAnchorReturns(FastAnchorReturnValues*);  // === TO-DO ===





    // ==== Clustering with Fairlets ==== //
    
    // clusters points who are in a fairlett with Gonzalez algorithm
    void clusterFairlettPoints(FastAnchorReturnValues*, int);  // === TO-DO ===

    // walks though all points, filter by their cluster and calculates the biggest cluster
    double calculateMaxRadius(vector<ColoredPoint>, int);  // === TO-DO ===

    // Updates the red points in the real of the clustering points from the filtered List of points
    void updateClusterOfMainPoints(vector<ColoredPoint>*, vector<ColoredPoint>*, vector<ColoredPoint>*);  // === TO-DO ===

    // Using the clustered red points and their fairlettID to asign 
    // the clusters to blue points. Includes outlier
    void updateClusterOfOutliers(vector<ColoredPoint>*);  // === TO-DO ===
}


