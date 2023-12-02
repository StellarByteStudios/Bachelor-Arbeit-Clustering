#include <iostream>

#include "ColoredPoint.h"
#include "PointParser.h"
#include "Gonzales.h"

int main(int argc, char **argv) {
	std::cout << "Hello World!\n";

	//std::string fileName = "HandmadePoints.txt";
	std::string fileName = "Points5D.txt";

	//Printer printer = Printer();
	PointParser parser =  PointParser(fileName);

	// Punkte einlesen
	vector<ColoredPoint>* points = parser.parseFile();

	/*
	// Einige Punkte Clustern
	points->at(0).setCluster(1);
	points->at(1).setCluster(1);
	points->at(2).setCluster(2);
	points->at(3).setCluster(2);
	points->at(4).setCluster(points->at(3).getCluster());




	for (int i = 0; i < (int) points->size(); i++){
		std::cout << i << ": " << points->at(i).toString() << endl;
	}*/


	std::cout << "\nTesting Distance\n";

	double coord1[] = { 0, 2 };
	ColoredPoint point1 = ColoredPoint(2, RED, coord1);

	double coord2[] = { 0, 0 };
	ColoredPoint point2 = ColoredPoint(2, BLUE, coord2);

	std::cout << "Distance Hard: " << point1.distTo(point2) << endl;
	std::cout << "Distance ReadIn: " << points->at(0).distTo(points->at(1)) << endl;





	std::cout << "\n-----------------\nTesting Gonzales\n";
	Gonzales gonzales = Gonzales();
	double maxRadius = gonzales.makeGonzales(points, 3);

	for (int i = 0; i < (int) points->size(); i++){
			std::cout << i << ": " << points->at(i).toString() << endl;
		}

	std::cout << "MaxRadius: " << maxRadius << endl;


	// vector für Punkte wieder Freigeben
	delete points;

	std::cout << "End Program" << std::endl;
}
