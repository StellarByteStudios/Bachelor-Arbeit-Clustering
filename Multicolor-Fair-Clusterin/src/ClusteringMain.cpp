#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateien ein/auslesen)
#include <string>

#include "Points/ColoredPoint.h"
#include "Points/PointParser.h"
#include "Gonzalez/Gonzalez.h"

#include "RedClustering/RedCenterClustering.h"
#include "FastAnchorClustering/FastAnchorClustering.h"

#ifdef PROCESS_BAR
    #define printProcess(process) std::cout << process << endl;
#else
    #define printProcess(process)
#endif

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

		// Build Headder of File:
		stringstream header;
		header << "maxRadius," << returnValues->maxRadius; 

		// Save Clustering to File
		savePointsToFile(outputFileName, returnValues->clusteredPoints, header.str());

		// Free struct space of returnvalues
		Gonzalez::deleteGonzalezReturns(returnValues);

		printProcess("Gonzalez without problems");
		break;
	}
	case 'r':{

		// ==== Red-Clustering Gonzalez ==== //
		redclustering::FairFlowReturnValues* returnValues = redclustering::makeFairRedClustering(points, numberOfCluster);

		// Build Headder of File:
		stringstream header;
		header << "maxClusterRadius," << returnValues->maxClusterRadius << ",";
		header << "maxFairletRadius," << returnValues->maxFairlettRadius;

		// Save Clustering to File
		savePointsToFile(outputFileName, returnValues->clusteredPoints, header.str());

		// Free struct space of returnvalues
		redclustering::deleteFairFlowReturns(returnValues);

		printProcess("Red-Clustering without problems");
		break;
	}
	case 'f':{
		// ==== Fast-Anchor-Clustering Gonzalez ==== //
		fastAnchorClustering::FastAnchorReturnValues * returnValues = fastAnchorClustering::makeFastAnchorClustering(points, numberOfCluster);

		// Build Headder of File:
		stringstream header;
		header << "maxClusterRadius," << returnValues->maxClusterRadius << ",";
		header << "maxFairletRadius," << returnValues->maxFairlettRadius;

		// Save Clustering to File
		savePointsToFile(outputFileName, returnValues->clusteredPoints, header.str());

		// Free struct space of returnvalues
		fastAnchorClustering::deleteFastAnchorReturns(returnValues);

		printProcess("Fast-Anchor Clustering without problems");
		break;
	}
	default:
		cout << "ERROR: Algorithm not Found!" << endl;
		break;
	}


	// ==== Clear-Up ==== //
	// vector für Punkte wieder Freigeben
	delete points;
}



void savePointsToFile(string outputFileName, vector<ColoredPoint>* clusteredPoints, string header){
    printProcess("\n===== Write Data into File =====\n");

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
