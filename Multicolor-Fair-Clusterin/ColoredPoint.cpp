#include "ColoredPoint.h"
#include <sstream>  // stringstream (String builder)
#include <math.h>   // sqrt, pow

ColoredPoint::ColoredPoint(int dimensions, Pointcolor color, double coords[])
{
	// Dimensionen �bertragen
	this->dim = dimensions;

	// Farbe �bertragen
	this->color = color;


	// Daten �bertragen
	for (int i = 0; i < this->dim; i++)
	{
		this->coordinates.push_back(coords[i]);
	}

	// Keinem Cluster zuweisen
	this->cluster = -1;
}

ColoredPoint::~ColoredPoint()
{
}

double ColoredPoint::distTo(ColoredPoint other)
{
	// R�ckgabevariable
	double dist = 0;

	//Euklidische Distanz. Erst quadrate aufsummieren
	for (int i = 0; i < dim; i++)
	{
		// p_i - q_i
		double simpleDist = (this->coordinates[i] - other.coordinates[i]);
		//(...)^2
		dist += pow(simpleDist, 2);
	}

	// Wurzel ziehen
	dist = sqrt(dist);

	return dist;
}


bool ColoredPoint::sameClusterAs(ColoredPoint other)
{
	return this->cluster == other.cluster;
}



string ColoredPoint::toString()
{
	stringstream stringStream;
	stringStream << "Dims: " << this->dim ;
	stringStream << "; Cluster: ";

	if(this->cluster == -1){
		stringStream << "--";
	} else{
		stringStream << this->cluster;
	}

	stringStream << "; Color: ";
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

int ColoredPoint::getCluster()
{
	return this->cluster;
}

void ColoredPoint::setCluster(int cluster)
{
	this->cluster = cluster;
}
