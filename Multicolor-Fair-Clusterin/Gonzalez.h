#pragma once

#include <vector>

#include "ColoredPoint.h"

using namespace std;

namespace Gonzalez{
	/* Gonzalez Return Struct
	* Struct with all importent Values returned
	* by the Gonzalez-Algorithm
	*
	* clusteredPoints: Deep-Copy of Points with Clustersignature
	* centers: List of all Centers as Points
	* maxRadius: value of the calculated maxRadius
	*/
	struct GonzalezReturnValues{
		vector<ColoredPoint>* clusteredPoints;
		vector<ColoredPoint>* centers;
		double maxRadius;
	};

	// Creating an empty Struct for Gonzalez
	GonzalezReturnValues* createGonzalezReturns(vector<ColoredPoint>*);

	// Clean-Up for Gonzalez Returnvalues
	void deleteGonzalezReturns(GonzalezReturnValues*);
	



	/* Gonzalez-Algorithm
	* Calculates the good Centers for given Points
	*
	* @param points: Set of Points to be Clusterd
	* @param clusters: Number of desired Clusters
	*
	* @return max radius
	*/
	GonzalezReturnValues* makeGonzalez(vector<ColoredPoint>*, int);
};
