#pragma once
#include <vector>

#include "../Points/ColoredPoint.h"
#include "../Gonzalez/Gonzalez.h"
#include "FastAnchorFairlett.h"


using namespace std;

namespace fastAnchorClustering{
    // * * * =========== Struct of Returnvalues =========== * * * //
    struct FastAnchorReturnValues{
		vector<ColoredPoint>* clusteredPoints;
		vector<ColoredPoint>* centers;
		double maxClusterRadius;
        double maxFairlettRadius;
	};

    // * * * =========== Main Fast-Anchor Algorithm =========== * * * //
    // Method which uses the Max-Flow and Gonzalez Algorithm to cluster an unfair amount of Points
    FastAnchorReturnValues* makeFastAnchorClustering(vector<ColoredPoint>*, int);

    // Creating an empty Struct for Max-Flow-Clustering
	FastAnchorReturnValues* createFastAnchorReturns(vector<ColoredPoint>*);

	// Clean-Up for Max-Flow-Clustering Returnvalues
	void deleteFastAnchorReturns(FastAnchorReturnValues*);





    // * * * =========== Clustering with Fairlets =========== * * * //
    // clusters points who are in a fairlett with Gonzalez algorithm
    void clusterFairlettPoints(FastAnchorReturnValues*, int);

    // Updates the rest of the Points which are not Outliers
    void updateClusterOfMainPoints(vector<ColoredPoint>*, vector<ColoredPoint>*);

    // Updates the centers from Gonzalez Returns to FastAnchorReturns
    void updateCentersOfMainPoints(vector<ColoredPoint>*, vector<ColoredPoint>*, vector<ColoredPoint>*);

    // Updates the Cluster of all Points which partners are Centers
    void updateCenterPartners(vector<ColoredPoint>*, vector<ColoredPoint>*);







    // * * * =========== Utility =========== * * * //  
    // walks though all points, filter by their cluster and calculates the biggest cluster
    double calculateMaxRadius(vector<ColoredPoint>, int);

    // Returns a Array in which every Point save the Clusternum of the neares Center
    vector<int>* getNearesCenters(vector<ColoredPoint>*, vector<ColoredPoint>*);

    // Goes through all Centers and returns the Clusternumber of the nearest one
    int getNextCenterOfPoint(ColoredPoint, vector<ColoredPoint>*);
}


