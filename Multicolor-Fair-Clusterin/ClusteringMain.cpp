#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateien ein/auslesen)
#include <string>

#include "ColoredPoint.h"
#include "PointParser.h"
#include "Gonzalez.h"
#include "FairlettFinder.h"
#include "RedCenterClustering.h"

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

	cout << "MaxRadius (PlainGonzalez): " << returnValues->maxRadius << endl;
	/*
	cout << "Centers: " << endl;
	// Centren anzeigen
	for (int i = 0; i < (int) returnValues->centers->size(); i++){
		cout << "\t- " << returnValues->centers->at(i).toString() << endl;
	}*/


	// ==== Testing of MaxRadius function ==== //
	double maxRadiusViaFunction = redclustering::calculateMaxRadius(*returnValues->clusteredPoints, numberOfCluster);

	cout << "MaxRadius (Funktion): " << maxRadiusViaFunction << endl;






	// ==== Testing graph Buildup ==== //
	// Get new Points
	string unfairHandpointsFile = "Data/RandomGenerated/Unfair-Twocolor-2D.txt";
	parser =  PointParser(unfairHandpointsFile);
	vector<ColoredPoint>* unfairPoints = parser.parseFile();

	// Buildup Graph
	Graph g;
	fairlettFinder::GraphData gData;
	CapacityMap capacity(g);

	// Add Nodes
	fairlettFinder::addNodesToGraph(g, gData, unfairPoints);

	// Add Arcs
	fairlettFinder::addArcsToGraph(g, gData, 10, unfairPoints);

	// Add Capacities
	fairlettFinder::addCapacitiesToGraph(capacity, gData);

	// Print outcome
	//fairlettFinder::printGraphCapacity(g, capacity, gData);



	// ==== More Testing ==== //

	/*
	// Calculate all possible Radii
	vector<double>* potRadii = fairlettFinder::calculateAllRadii(unfairPoints);

	// Print Radii
	cout << "All Possible Radii:" << endl;
	for (size_t i = 0; i < potRadii->size(); i++){
		cout << potRadii->at(i) << endl;
	}

	delete potRadii;
	*/


	// ==== Testing Color-Filter ==== //
	/*	
	cout << "\n===== Testing Colorfilter =====\n" << endl;

	cout << "Original Vector before filtering:" << endl;
	for (size_t i = 0; i < unfairPoints->size(); i++){
		cout << unfairPoints->at(i).toString() << endl;
	}

	// Filtern
	vector<ColoredPoint>* redPoints = fairlettFinder::getPointsOfColor(unfairPoints, RED);
	vector<ColoredPoint>* bluePoints = fairlettFinder::getPointsOfColor(unfairPoints, BLUE);

	cout << "\nOriginal Vector after filtering:" << endl;
	for (size_t i = 0; i < unfairPoints->size(); i++){
		cout << unfairPoints->at(i).toString() << endl;
	}

	cout << "\nFiltered RedVector after filtering:" << endl;
	for (size_t i = 0; i < redPoints->size(); i++){
		cout << redPoints->at(i).toString() << endl;
	}
	
	cout << "\nSize-Comparison:" << endl;
	cout << "\nAll Points: " << unfairPoints->size() << endl;
	cout << "\nRed Points: " << redPoints->size() << endl;
	cout << "\nBlue Points: " << bluePoints->size() << endl;


	delete redPoints;
	delete bluePoints;
	*/



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
	delete unfairPoints;

	// Struct für Gonzaleswerte wieder freigeben
	Gonzalez::deleteGonzalezReturns(returnValues);

	cout << "\n-----------------\nEnd Program" << endl;
}
