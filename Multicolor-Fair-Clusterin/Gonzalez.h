#pragma once

#include <vector>

#include "ColoredPoint.h"

using namespace std;

class Gonzalez{
public:
	/* Konstruktor
	*/
	Gonzalez();

	/* Destruktor
	*/
	~Gonzalez();

	/* Gonzales-Algorithm
	* Calculates the good Centers for given Points
	*
	* @param points: Set of Points to be Clusterd
	* @param clusters: Number of desired Clusters
	*
	* @return max radius
	*/
	double makeGonzalez(vector<ColoredPoint>*, int);

private:
};
