#include "EuclidPoint.h";

EuclidPoint::EuclidPoint(int dimensions, double coords[])
{
	// Dimensionen übertragen
	this->dim = dimensions;

	// Platz anlegen
	this->coordinates = (double*)malloc(dimensions * sizeof(double));

	// Daten übertragen
	for (int i = 0; i < this->dim; i++)
	{
		*(this->coordinates + 1) = coords[i];
	}
	
}

EuclidPoint::~EuclidPoint()
{
	free(this->coordinates);
}

double EuclidPoint::distTo(EuclidPoint)
{
	return 0.0;
}

char* EuclidPoint::toString()
{
	return nullptr;
}

int EuclidPoint::getDim()
{
	return this->dim;
}
