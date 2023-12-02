#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateien ein/auslesen)

#include "ColoredPoint.h"
#include "PointParser.h"
#include "Gonzales.h"

int main(int argc, char **argv) {
	cout << "Hello World!\n";

	//std::string fileName = "HandmadePoints.txt";
	string fileName = "Pythonskripte/Points2D.txt";
	string outputFileName = "ClusterOut2D.csv";
	int numberOfCluster = 5;

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


	cout << "\nTesting Distance\n";

	double coord1[] = { 0, 2 };
	ColoredPoint point1 = ColoredPoint(2, RED, coord1);

	double coord2[] = { 0, 0 };
	ColoredPoint point2 = ColoredPoint(2, BLUE, coord2);

	cout << "Distance Hard: " << point1.distTo(point2) << endl;
	cout << "Distance ReadIn: " << points->at(0).distTo(points->at(1)) << endl;





	cout << "\n-----------------\nTesting Gonzales\n";
	Gonzales gonzales = Gonzales();
	double maxRadius = gonzales.makeGonzales(points, numberOfCluster);

	for (int i = 0; i < (int) points->size(); i++){
		cout << i << ": " << points->at(i).toString() << endl;
	}

	cout << "MaxRadius: " << maxRadius << endl;


	cout << "\n-----------------\nWrite Data into File\n";

	ofstream outputFile = ofstream(outputFileName, ios::out);

	if(!outputFile.good()){
		cout << "Error opening Outputfile" << endl;
	} else{
		for (int i = 0; i < (int) points->size(); i++){
			outputFile << points->at(i).toCSV() << endl;
		}
	}





	// vector für Punkte wieder Freigeben
	delete points;

	cout << "End Program" << endl;
}
