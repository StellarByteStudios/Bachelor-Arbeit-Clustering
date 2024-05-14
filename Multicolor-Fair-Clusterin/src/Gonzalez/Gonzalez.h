#pragma once

#include <vector>

#include "../Points/ColoredPoint.h"

using namespace std;

namespace Gonzalez{
	// Struct with all importent Values returned by the Gonzalez-Algorithm
	struct GonzalezReturnValues{
		vector<ColoredPoint>* clusteredPoints;
		vector<ColoredPoint>* centers;
		double maxRadius;
	};

	// Creating an empty Struct for Gonzalez
	GonzalezReturnValues* createGonzalezReturns(vector<ColoredPoint>*);

	// Clean-Up for Gonzalez Returnvalues
	void deleteGonzalezReturns(GonzalezReturnValues*);
	



	// * * * =========== Main Gonzalez Algorithm =========== * * * //
	GonzalezReturnValues* makeGonzalez(vector<ColoredPoint>*, int);

	// Makes Gonzalez, but with fairlettpoints, where two partners can`t be both Centers
	GonzalezReturnValues* makeAwareGonzalez(vector<ColoredPoint>*, int);

	// Finds the Index of the fairlett-partner of given Point
	int getIndexOfPartner(ColoredPoint, int, vector<ColoredPoint>*);
}
