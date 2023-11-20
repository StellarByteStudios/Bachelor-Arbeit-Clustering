#pragma once

#include <string>

using namespace std;

enum Pointcolor
{
	RED = 0,
	BLUE = 1,
	GREEN = 2
};

class ColoredPoint
{
private:
	// Coordinates of the Point (Pointer because variable dimensions)
	double* coordinates;

	// Dimensionality of the Point
	int dim;

	// Color of the Point
	Pointcolor color;


public:
	/* Konstructor
	*/
	ColoredPoint(int, double[], Pointcolor);

	/* Destructor
	* Prints death Message
	*/
	~ColoredPoint();


	/* Distance-Method
	* Calculates the relative distance beween caller 
	* and the as Argument given Point
	*
	* @param partner: Other Point to messure Distance to
	*
	* @return relative distance
	*/
	double distTo(ColoredPoint);

	/* ToString-Method
	* Constructs a String representive of calling Point
	* and returns it as char*
	*
	* @return string to Stringrepresentation of Point
	*/
	string toString();

	/* Info-Method
	* Simply returns the size of the Point
	*
	* @return dimensions
	*/
	int getDim();

	/* Info-Method
	* Simply returns the color of the Point
	*
	* @return color
	*/
	Pointcolor getColor();
};

