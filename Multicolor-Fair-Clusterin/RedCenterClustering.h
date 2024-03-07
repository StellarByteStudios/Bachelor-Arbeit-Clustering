#pragma once
#include <vector>

#include "ColoredPoint.h"

using namespace std;

namespace redclustering{
    struct FairFlowReturnValues{
		vector<ColoredPoint>* clusteredPoints;
		vector<ColoredPoint>* centers;
		double maxRadius;
	};

    // Method which uses the Max-Flow and Gonzalez Algorithm to cluster an unfair amount of Points
    FairFlowReturnValues* makeFairRedClustering(vector<ColoredPoint>*, int);  // * * TO-DO * * //

    // Creating an empty Struct for Max-Flow-Clustering
	FairFlowReturnValues* createFairFlowReturns(vector<ColoredPoint>*);  // * * TO-DO * * //

	// Clean-Up for Max-Flow-Clustering Returnvalues
	void deleteFairFlowReturns(FairFlowReturnValues*);  // * * TO-DO * * //





    // ==== Clustering with Fairlets ==== //
    // clusters points with krit-feature = 0 with Gonzalez algorithm
    void clusterRedPoints(vector<ColoredPoint>*);  // * * TO-DO * * //
    
    // returns just the red points which a used for the clustering
    vector<ColoredPoint>* filterRedPoints(vector<ColoredPoint>*);  // * * TO-DO * * //

    // walks though all points, filter by their cluster and calculates the biggest cluster
    double calculateMaxRadius(vector<ColoredPoint>, int);

    // using the clustered red points and their fairlettID to asign 
    // the clusters to blue points. Includes outlier
    void updateClusterOfBluePoints(vector<ColoredPoint>*);  // * * TO-DO * * //
}


