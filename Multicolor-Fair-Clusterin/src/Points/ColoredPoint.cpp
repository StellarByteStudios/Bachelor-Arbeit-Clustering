#include "ColoredPoint.h"
#include <sstream>  // stringstream (String builder)
#include <math.h>   // sqrt, pow


// * * * =========== Konstruktor =========== * * * //
ColoredPoint::ColoredPoint(int dimensions, Pointcolor color, double coords[]){
	// Dimensionen übertragen
	this->dim = dimensions;

	// Farbe übertragen
	this->color = color;


	// Daten übertragen
	for (int i = 0; i < this->dim; i++){
		this->coordinates.push_back(coords[i]);
	}

	// Keinem Cluster zuweisen
	this->cluster = -1;

	// Keinem Fairlett zuweisen
	this->fairlettID = -1;

	// Keinem Anker zuweisen
	this->anchorID = -1;

	// Punkt ist erstmal kein Zentrum
	this->isCenter = false;
}

double ColoredPoint::distTo(ColoredPoint other){
	// Rückgabevariable
	double dist = 0;

	//Euklidische Distanz. Erst quadrate aufsummieren
	for (int i = 0; i < dim; i++){
		// p_i - q_i
		double simpleDist = (this->coordinates[i] - other.coordinates[i]);
		//(...)^2
		dist += simpleDist * simpleDist;
	}

	// Wurzel ziehen
	dist = sqrt(dist);
	
	return dist;
}



// * * * =========== String-Methods =========== * * * //
string ColoredPoint::toString(){
	stringstream stringStream;
	stringStream << "Dims: " << this->dim ;
	stringStream << "; IsCenter: " << this->isCenter;
	stringStream << "; Cluster: ";

	if(this->cluster == -1){
		stringStream << "--";
	} else{
		stringStream << this->cluster;
	}

	stringStream << "; FairlettID: ";
	if(this->fairlettID == -1){
		stringStream << "--;\t\t";
	} else if (this->fairlettID == -2){
		stringStream << "Ausreißer;\t";
	} else {
		stringStream << this->fairlettID << ";\t\t";
	}
	stringStream << "; AnchorID: " << this->anchorID;

	stringStream << " Color: ";
	switch (this->color){
	case(RED):
		stringStream << "Red;   ";
		break;
	case(BLUE):
		stringStream << "Blue;  ";
		break;
	case(GREEN):
		stringStream << "Green; ";
		break;
	default:
		stringStream << "---;   ";
		break;
	}
	stringStream << "Coords [";
	for (int i = 0; i < this->dim -1; i++){
		stringStream << this->coordinates[i] << ", ";
	}
	stringStream << this->coordinates[dim-1];
	stringStream << "]";
	return stringStream.str();
}

string ColoredPoint::toCSV(){
	stringstream stringStream;
	stringStream << this->dim <<",";
	stringStream << this->isCenter <<",";
	stringStream << this->cluster <<",";
	stringStream << this->fairlettID <<",";
	stringStream << this->anchorID <<",";
	stringStream << this->color <<",";
	for (int i = 0; i < this->dim -1; i++){
		stringStream << this->coordinates[i] << ",";
	}
	stringStream << this->coordinates[dim-1];

	return stringStream.str();
}


// * * * =========== Getter/Setter =========== * * * //
int ColoredPoint::getDim(){
	return this->dim;
}

Pointcolor ColoredPoint::getColor(){
	return this->color;
}

void ColoredPoint::setColor(Pointcolor color){
	this->color = color;
}

int ColoredPoint::getCluster(){
    return this->cluster;
}

void ColoredPoint::setCluster(int cluster){
	this->cluster = cluster;
}

bool ColoredPoint::getIsCenter(){
    return this->isCenter;
}

void ColoredPoint::setToCenter(){
	this->isCenter = true;
}

int ColoredPoint::getFairlettID(){
	return this->fairlettID;
}

void ColoredPoint::setFairlettID(int fairlettID){
	this->fairlettID = fairlettID;
}

int ColoredPoint::getAnchorID(){
	return this->anchorID;
}

void ColoredPoint::setAnchorID(int anchorID){
	this->anchorID = anchorID;
}




// * * * =========== Instance-Methods =========== * * * //
bool ColoredPoint::sameClusterAs(ColoredPoint other){
	return this->cluster == other.cluster;
}


vector<ColoredPoint>* ColoredPoint::getPointsOfColor(vector<ColoredPoint>* points, Pointcolor color){
    // Neuer Vector anlegen
    vector<ColoredPoint>* filteredPoints = new vector<ColoredPoint>;

    // Wie viele Punkte muss ich durchgehen
    int n = (int) points->size();

    for (int i = 0; i < n; i++){
        // Falls der Punkt die richtige Farbe hat, hinzufügen
        if(points->at(i).getColor() == color){
            filteredPoints->push_back(points->at(i));
        }
    }
    
    // den neuen, einfarbigen vector zurückgeben
    return filteredPoints;
}


vector<ColoredPoint>* ColoredPoint::getPointsOfFairletts(vector<ColoredPoint>* points){
	// Neuer Vector anlegen
    vector<ColoredPoint>* filteredPoints = new vector<ColoredPoint>;

    // Wie viele Punkte muss ich durchgehen
    int n = (int) points->size();

    for (int i = 0; i < n; i++){
        // Falls der Punkt die richtige Farbe hat, hinzufügen
        if(points->at(i).getFairlettID() >= 0){
            filteredPoints->push_back(points->at(i));
        }
    }
    
    // den neuen, einfarbigen vector zurückgeben
    return filteredPoints;
}