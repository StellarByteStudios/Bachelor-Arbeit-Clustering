#include "ColoredPoint.h"
#include <sstream>  // stringstream (String builder)

ColoredPoint::ColoredPoint(int dimensions, double coords[], Pointcolor color)
{
	// Dimensionen übertragen
	this->dim = dimensions;

	// Farbe übertragen
	this->color = color;


	// Daten übertragen
	for (int i = 0; i < this->dim; i++)
	{
		this->coordinates.push_back(coords[i]);
	}
}

ColoredPoint::~ColoredPoint()
{
}

double ColoredPoint::distTo(ColoredPoint)
{
	return 0.0;
}

string ColoredPoint::toString()
{
	stringstream stringStream;
	stringStream << "Dims: " << this->dim << "; Color: ";
	switch (this->color)
	{
	case(RED):
		stringStream << "Red; ";
		break;
	case(BLUE):
		stringStream << "Blue; ";
		break;
	case(GREEN):
		stringStream << "Green; ";
		break;
	default:
		stringStream << "---; ";
		break;
	}
	stringStream << "Coords [";
	for (int i = 0; i < this->dim -1; i++)
	{
		stringStream << this->coordinates[i] << ", ";
	}
	stringStream << this->coordinates[dim-1];
	stringStream << "]";
	return stringStream.str();
}

int ColoredPoint::getDim()
{
	return this->dim;
}

Pointcolor ColoredPoint::getColor()
{
	return this->color;
}
