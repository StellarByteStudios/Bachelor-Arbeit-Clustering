#pragma once

#include <string>
#include <vector>

#include "ColoredPoint.h"

#define MAXLINEPARSER 250
#define MAXPOINTS 10000

using namespace std;

class PointParser{
public:
	// Constructor
	PointParser(string);

	// Reads komplete File and converts into vector of Points
	vector<ColoredPoint>* parseFile();

private:
	// Path of the File which is Parsed
	string path;

	// Utility Method for counting how much Dimensions the Inputdata has
	int countDim(string);
};
