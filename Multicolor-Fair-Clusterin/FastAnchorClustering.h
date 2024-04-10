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

    // Updates the rest of the Points which are not Outliers
    void updateClusterOfMainPoints(vector<ColoredPoint>*, vector<ColoredPoint>*);  // === TO-DO ===

    // Updates the centers from Gonzalez Returns to FastAnchorReturns
    void updateCentersOfMainPoints(vector<ColoredPoint>*, vector<ColoredPoint>*, vector<ColoredPoint>*);  // === TO-DO ===

    // Updates the Cluster of all Points which partners are Centers
    void updateCenterPartners(vector<ColoredPoint>*, vector<ColoredPoint>*); // === TO-DO ===







    // ==== Utility ==== //

    // walks though all points, filter by their cluster and calculates the biggest cluster
    double calculateMaxRadius(vector<ColoredPoint>, int);  // === TO-DO ===


    // Returns a Array in which every Point save the Clusternum of the neares Center
    vector<int>* getNearesCenters(vector<ColoredPoint>*, vector<ColoredPoint>*); // === TO-DO ===

    // Goes through all Centers and returns the Clusternumber of the nearest one
    int getNextCenterOfPoint(ColoredPoint, vector<ColoredPoint>*); // === TO-DO ===
}


