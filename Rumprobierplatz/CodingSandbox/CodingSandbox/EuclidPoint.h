#pragma once

#include <string>

class EuclidPoint
{
private:
	// Coordinates of the Point (Pointer because variable dimensions)
	double* coordinates;

	// Dimensionality of the Point
	int dim;

public:
	/* Konstructor
	*/
	EuclidPoint(int, double[]);

	/* Destructor
	* Prints death Message
	*/
	~EuclidPoint();


	/* Distance-Method
	* Calculates the relative distance beween caller 
	* and the as Argument given Point
	*
	* @param partner: Other Point to messure Distance to
	*
	* @return relative distance
	*/
	double distTo(EuclidPoint);

	/* ToString-Method
	* Constructs a String representive of calling Point
	* and returns it as char*
	*
	* @return char Pointer to Stringrepresentation of Point
	*/
	char* toString();

	/* ToString-Method
	* Simply returns the size of the Point
	*
	* @return dimensions
	*/
	int getDim();
};

