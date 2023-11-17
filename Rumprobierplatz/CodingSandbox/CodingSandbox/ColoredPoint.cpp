#include "EuclidPoint.h";
#include <sstream>  // stringstream (String builder)

ColoredPoint::ColoredPoint(int dimensions, double coords[], Pointcolor color)
{
	// Dimensionen übertragen
	this->dim = dimensions;

	// Farbe übertragen
	this->color = color;

	// Platz anlegen
	this->coordinates = (double*)malloc(dimensions * sizeof(double));

	

	// Daten übertragen
	for (int i = 0; i < this->dim; i++)
	{
		this->coordinates[i] = coords[i];
	}
	
}

ColoredPoint::~ColoredPoint()
{
	free(this->coordinates);
}

double ColoredPoint::distTo(ColoredPoint)
{
	return 0.0;
}

char* ColoredPoint::toString()
{
	std::stringstream stringStream;
	stringStream << "Dims: " << this->dim << "; Color: ";
	switch (this->color)
	{
	case(RED):
		stringStream << "Red; ";
		break;
	case(BLUE):
		stringStream << "Blue; ";
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
	char* string = new char[strlen(stringStream.str().c_str())];
	strcpy_s(string, strlen(string), stringStream.str().c_str());
	return string;
}

int ColoredPoint::getDim()
{
	return this->dim;
}

Pointcolor ColoredPoint::getColor()
{
	return this->color;
}
