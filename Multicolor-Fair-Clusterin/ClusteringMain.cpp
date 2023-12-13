#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateien ein/auslesen)

#include "ColoredPoint.h"
#include "PointParser.h"
#include "Gonzales.h"

int main(int argc, char *argv[]) {
	cout << "Hello World!\n";

	// ==== getting Commandlinearguments ==== //

	cout << "Number of Arguments: " << argc-1 << endl;
	cout << "Name of Programm: " << argv[0] << endl;;
	cout << "Now the Arguments: " << endl;
	for(int i = 1; i < argc; i++){
		cout << "\t- " << argv[i] << endl;
	}
 

	// ==== Parsing of Points ==== //

	//std::string fileName = "HandmadePoints.txt";
	string inputFileName = "Data/RandomGenerated/Points2D.txt"; //Pythonskripte/Points2D.txt";
	string outputFileName = "Data/OutputData/ClusteredData/ClusterOut2DNew.csv";
	int numberOfCluster = 15;

	//Printer printer = Printer();
	PointParser parser =  PointParser(inputFileName);

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

	// ==== Testing of Distancefunction ==== //

	cout << "\nTesting Distance\n";

	double coord1[] = { 0, 2 };
	ColoredPoint point1 = ColoredPoint(2, RED, coord1);

	double coord2[] = { 0, 0 };
	ColoredPoint point2 = ColoredPoint(2, BLUE, coord2);

	cout << "Distance Hard: " << point1.distTo(point2) << endl;
	cout << "Distance ReadIn: " << points->at(0).distTo(points->at(1)) << endl;




	// ==== Testing of Gonuales ==== //

	cout << "\n-----------------\nTesting Gonzales\n";
	Gonzales gonzales = Gonzales();
	double maxRadius = gonzales.makeGonzales(points, numberOfCluster);

	/*
	for (int i = 0; i < (int) points->size(); i++){
		cout << i << ": " << points->at(i).toString() << endl;
	}*/

	cout << "MaxRadius: " << maxRadius << endl;

	// ==== Write Clusterdata into File ==== //

	cout << "\n-----------------\nWrite Data into File\n";

	ofstream outputFile = ofstream(outputFileName, ios::out);

	if(!outputFile.good()){
		cout << "Error opening Outputfile" << endl;
	} else{
		// max Radius an den Anfang packen
		outputFile << "maxRadius," << maxRadius << endl;

		// Punte abspeichern
		for (int i = 0; i < (int) points->size(); i++){
			outputFile << points->at(i).toCSV() << endl;
		}
	}



	// ==== Clear-Up ==== //

	// vector für Punkte wieder Freigeben
	delete points;

	cout << "End Program" << endl;
}
