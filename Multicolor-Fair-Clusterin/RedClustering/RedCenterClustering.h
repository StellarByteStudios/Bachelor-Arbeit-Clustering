#pragma once
#include <vector>

#include "../Points/ColoredPoint.h"
#include "../Gonzalez/Gonzalez.h"
#include "FairlettFinder.h"


using namespace std;

namespace redclustering{
    struct FairFlowReturnValues{
		vector<ColoredPoint>* clusteredPoints;
		vector<ColoredPoint>* centers;
		double maxClusterRadius;
        double maxFairlettRadius;
	};

    // Method which uses the Max-Flow and Gonzalez Algorithm to cluster an unfair amount of Points
    FairFlowReturnValues* makeFairRedClustering(vector<ColoredPoint>*, int);

    // Creating an empty Struct for Max-Flow-Clustering
	FairFlowReturnValues* createFairFlowReturns(vector<ColoredPoint>*);

	// Clean-Up for Max-Flow-Clustering Returnvalues
	void deleteFairFlowReturns(FairFlowReturnValues*);





    // ==== Clustering with Fairlets ==== //
    
    // clusters points with krit-feature = 0 with Gonzalez algorithm
    void clusterRedPoints(FairFlowReturnValues*, int);

    // walks though all points, filter by their cluster and calculates the biggest cluster
    double calculateMaxRadius(vector<ColoredPoint>, int);

    // Updates the red points in the real of the clustering points from the filtered List of points
    void updateClusterOfMainRedPoints(vector<ColoredPoint>*, vector<ColoredPoint>*, vector<ColoredPoint>*);

    // Using the clustered red points and their fairlettID to asign 
    // the clusters to blue points. Includes outlier
    void updateClusterOfBluePoints(vector<ColoredPoint>*);

    // Gets the FairlettID of a blue Point and searches for his red Partner
    // returns the index of the red partner
    int getRedFairlettPartnerIndex(vector<ColoredPoint>*, int);
}


