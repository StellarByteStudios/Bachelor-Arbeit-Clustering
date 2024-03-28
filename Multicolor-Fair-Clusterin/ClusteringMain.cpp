#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateien ein/auslesen)
#include <string>

#include "ColoredPoint.h"
#include "PointParser.h"
#include "Gonzalez.h"
#include "FairlettFinder.h"
#include "RedCenterClustering.h"

void savePointsToFile(string, vector<ColoredPoint>*, string);



int main(int argc, char *argv[]) {

	/* ==== getting Commandlinearguments ==== //
	* Format:
	*	1) Inputfile Path 
	*	2) Outputfile Path
	*	3) number of Clusters
	*	4) kind of Algorithm 
	* 		g = Gonzalez
	*		r = red-Clustering
	* 		f = fast-anchor-Clustering
	*/
	if (argc < 5){
		cout << "Not enough Arguments\nneeded: \"inputFilePath\" \"outputFilePath\" numOfClusters algorithm" << endl;
		return -1;
	}
	
	// ==== Getting Inputparameters ==== //
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	int numberOfCluster = stoi(argv[3]);
	char algorithm = argv[4][0];

	// ==== Sanaty-Check - Algorithm avaialble ==== //
	if (algorithm != 'g' && algorithm != 'r' && algorithm != 'f'){
		cout << "The Algorithm with the Letter " << algorithm << " is not avaiable" << endl;
		cout << "The possible algorithms are (g)onzalez, (r)ed-clustering, (f)ast-anchor-Clustering" << endl;
		return 1;
	}
	


	// ==== Parsing of Points ==== //
	PointParser parser =  PointParser(inputFileName);
	vector<ColoredPoint>* points = parser.parseFile();
	
	
	
	// ==== Switch for the different Algorithms ==== //
	switch (algorithm){
	case 'g':{
		// ==== Doing Gonzalez ==== //
		Gonzalez::GonzalezReturnValues* returnValues = Gonzalez::makeGonzalez(points, numberOfCluster);

		// Dateiheader zusammenbauen:
		stringstream header;
		header << "maxRadius," << returnValues->maxRadius; 

		// Ergebniss Abspeichern
		savePointsToFile(outputFileName, returnValues->clusteredPoints, header.str());

		// Struct für Gonzaleswerte wieder freigeben
		Gonzalez::deleteGonzalezReturns(returnValues);

		cout << "Gonzalez ohne Probleme" << endl;
		break;
	}
	case 'r':{
		cout << "ERROR: Red-Clustering is not implemented yet" << endl;
		break;
	}
	case 'f':{
		cout << "ERROR: Fast-Anchor-Clustering is not implemented yet" << endl;
		break;
	}
	default:
		cout << "ERROR: wrong case" << endl;
		break;
	}





	




	// ==== Write Clusterdata into File ==== //

	/*
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
	*/


	// ==== Clear-Up ==== //
	// vector für Punkte wieder Freigeben
	delete points;

	//cout << "\n-----------------\nEnd Program" << endl;
}



void savePointsToFile(string outputFileName, vector<ColoredPoint>* clusteredPoints, string header){
    cout << "\n\n===== Write Data into File =====\n" << endl;

	ofstream outputFile = ofstream(outputFileName, ios::out);

	if(!outputFile.good()){
		cout << "Error opening Outputfile" << endl;
		return;
	} 
	
	// Header an den Anfang packen
	outputFile << header << endl;

	// Punte abspeichern
	for (int i = 0; i < (int) clusteredPoints->size(); i++){
		outputFile << clusteredPoints->at(i).toCSV() << endl;
	}
}
