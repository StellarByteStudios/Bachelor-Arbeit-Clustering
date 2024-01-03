#pragma once

#include <string>
#include <vector>

#include "ColoredPoint.h"

#define MAXLINEPARSER 250
#define MAXPOINTS 1000

using namespace std;

class PointParser{
public:
	/* Konstruktor
	* @param path: Path of File to be read
	*/
	PointParser(string);

	/* Destruktor
	* Prints death Message
	*/
	~PointParser();

	/* Reads File
	* reads komplete File and converts into
	* a vector of Points
	*
	* @return char* of File-content
	*/
	vector<ColoredPoint>* parseFile();

private:
	string path;

	int countDim(string);
};
