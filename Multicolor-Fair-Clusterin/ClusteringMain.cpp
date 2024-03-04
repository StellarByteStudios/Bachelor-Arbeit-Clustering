#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateien ein/auslesen)
#include <string>

#include "ColoredPoint.h"
#include "PointParser.h"
#include "Gonzalez.h"

int main(int argc, char *argv[]) {

	/* ==== getting Commandlinearguments ==== //
	* Format:
	*	1) Inputfile Path 
	*	2) Outputfile Path
	*	3) number of Clusters
	*	[4) later: kind of Algorithm]
	*/

	/*
	cout << "Number of Arguments: " << argc-1 << endl;
	cout << "Name of Programm: " << argv[0] << endl;;
	cout << "Now the Arguments: " << endl;
	for(int i = 1; i < argc; i++){
		cout << "\t- " << argv[i] << endl;
	}*/
 
	if (argc < 4)
	{
		cout << "Not enough Arguments\nneeded: \"inputFilePath\" \"outputFilePath\" numOfClusters" << endl;
		return -1;
	}
	
	string inputFileName = argv[1];//"Data/RandomGenerated/Points2D.txt";
	string outputFileName = argv[2];//"Data/OutputData/ClusteredData/ClusterOut2DNew.csv";
	int numberOfCluster = stoi(argv[3]);

	// ==== Parsing of Points ==== //

	PointParser parser =  PointParser(inputFileName);
	vector<ColoredPoint>* points = parser.parseFile();
	
	
	
	// ==== Testing of Gonzalez ==== //
	cout << "\n-----------------\nTesting Gonzalez: \n";

	Gonzalez::GonzalezReturnValues* returnValues = Gonzalez::makeGonzalez(points, numberOfCluster);

	cout << "MaxRadius: " << returnValues->maxRadius << endl;
	cout << "Centers: " << endl;
	// Centren anzeigen
	for (int i = 0; i < (int) returnValues->centers->size(); i++){
		cout << "\t- " << returnValues->centers->at(i).toString() << endl;
	}


	// ==== Write Clusterdata into File ==== //

	cout << "\n-----------------\nWrite Data into File:\n";

	ofstream outputFile = ofstream(outputFileName, ios::out);

	if(!outputFile.good()){
		cout << "Error opening Outputfile" << endl;
	} else{
		// max Radius an den Anfang packen
		outputFile << "maxRadius," << returnValues->maxRadius << endl;

		// Punte abspeichern
		for (int i = 0; i < (int) returnValues->clusteredPoints->size(); i++){
			outputFile << returnValues->clusteredPoints->at(i).toCSV() << endl;
		}
	}

	// ==== Clear-Up ==== //

	// vector für Punkte wieder Freigeben
	delete points;

	// Struct für Gonzaleswerte wieder freigeben
	Gonzalez::deleteGonzalezReturns(returnValues);

	cout << "\n-----------------\nEnd Program" << endl;
}
