#pragma once

#include <vector>

#include "ColoredPoint.h"

using namespace std;

class Gonzales{
public:
	/* Konstruktor
	*/
	Gonzales();

	/* Destruktor
	*/
	~Gonzales();

	/* Gonzales-Algorithm
	* Calculates the good Centers for given Points
	*
	* @param points: Set of Points to be Clusterd
	* @param clusters: Number of desired Clusters
	*
	* @return max radius
	*/
	double makeGonzales(vector<ColoredPoint>*, int);

private:
};
