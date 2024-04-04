#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateien ein/auslesen)
#include <iomanip> // setw() Feste Anzahl an Digits
#include <string>

#include "ColoredPoint.h"
#include "PointParser.h"
#include "Gonzalez.h"
#include "FairlettFinder.h"
#include "RedCenterClustering.h"
#include "GraphFlow.h"

#include "FastAnchorClustering.h"
#include "FastAnchorFairlett.h"
#include "FastAnchorFlow.h"


// Declaration of Test functions
vector<ColoredPoint>* testGonzalez(vector<ColoredPoint>*, int);
void testGraphBuildup(vector<ColoredPoint>*);
void testMaximumRadiusFunction(vector<ColoredPoint>*, int);
void testRadiusChecker(vector<ColoredPoint>*);
void testCalculationOfAllRadii(vector<ColoredPoint>*);
void testMarkingFairlets(vector<ColoredPoint>*);
void testColorFiltering(vector<ColoredPoint>*);
void testOnlyRedClustering(vector<ColoredPoint>*, int);
void testFairRedClustering(vector<ColoredPoint>*, int);
void testFairlettFlitering(vector<ColoredPoint>*);
void testAnchorMatrixFill(vector<ColoredPoint>*);
void testAnchorRadiusChecker(vector<ColoredPoint>*);

void printAllpoints(vector<ColoredPoint>*);

void localPrintAnchorMatrix(const vector<vector<Anchor>>&);

void savePointsToFile(string, vector<ColoredPoint>*);




int main(int argc, char *argv[]) {

	/* ==== getting Commandlinearguments ==== //
	* Format:
	*	1) Inputfile Path 
	*	2) Outputfile Path
	*	3) number of Clusters
	*	[4) later: kind of Algorithm]
	*/
 
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
    
    // Get new Points
	string unfairHandpointsFile = "Data/RandomGenerated/HandmadeFairlettPoints.csv"; //"Data/RandomGenerated/Unfair-Twocolor-2D.txt";
	parser =  PointParser(unfairHandpointsFile);
	vector<ColoredPoint>* unfairPoints = parser.parseFile();
	
	
	// ==== * ==== * ==== Gonzalez Testing ==== * ==== * ==== ///
	// ==== Testing of Gonzalez ==== //
	// vector<ColoredPoint>* clusteredPoints = testGonzalez(points, numberOfCluster);
    
    //cout << "Alle Punkte direkt nach Gonzalez" << endl;
    //printAllpoints(clusteredPoints);
	


	// ==== Testing of MaxRadius function ==== //
    //testMaximumRadiusFunction(clusteredPoints, numberOfCluster);





	// ==== * ==== * ==== Red-Clustering Testing ==== * ==== * ==== ///
	// ==== Testing graph Buildup ==== //
    //testGraphBuildup(points);



    // ==== Check some possible Radii ==== //
    //testRadiusChecker(unfairPoints);

	

	// ==== Calculate all possible Radii ==== //
    //testCalculationOfAllRadii(points);



    // ==== Mark the Fairletts ==== //
    //testMarkingFairlets(clusteredPoints);




	// ==== Testing Color-Filter ==== //
    //testColorFiltering(unfairPoints);	


	// ==== Testing Clustering only with red points ==== //
	//testOnlyRedClustering(unfairPoints, numberOfCluster);


	// ==== Testing Fair-Red-Clustering ==== ///
	//testFairRedClustering(points, numberOfCluster);








	// ==== * ==== * ==== Fast-Anchor Testing ==== * ==== * ==== ///
	// ==== Testing Fair-Red-Clustering ==== ///
	//testFairlettFlitering(unfairPoints);


	// ==== Testing Calculation of Anchormatrix ==== ///
	//testAnchorMatrixFill(points);

	// ==== Testing Searching Opt Rad with Anchors ==== ///
	testAnchorRadiusChecker(unfairPoints);





    // ==== Write Clusterdata into File ==== //
    //savePointsToFile(outputFileName, clusteredPoints);

	// ==== Clear-Up ==== //
	// vector für Punkte wieder Freigeben
	delete points;
	delete unfairPoints;
    //delete clusteredPoints;

	

	cout << "\n\n===== End of Programm =====\n" << endl;

}










vector<ColoredPoint>* testGonzalez(vector<ColoredPoint>* points, int numberOfCluster){
    cout << "\n\n===== Testing of Gonzalez =====\n" << endl;

	Gonzalez::GonzalezReturnValues* returnValues = Gonzalez::makeGonzalez(points, numberOfCluster);

	cout << "MaxRadius (PlainGonzalez): " << returnValues->maxRadius << endl;

    /*
	cout << "Centers: " << endl;
	// Centren anzeigen
	for (int i = 0; i < (int) returnValues->centers->size(); i++){
		cout << "\t- " << returnValues->centers->at(i).toString() << endl;
	}*/

    // Punkte zum zurückgeben vorbereiten
    vector<ColoredPoint>* returnPoints = new vector<ColoredPoint>;
    for (int i = 0; i < (int) returnValues->clusteredPoints->size(); i++){
        returnPoints->push_back(returnValues->clusteredPoints->at(i));
    }
    

    // Struct für Gonzaleswerte wieder freigeben
	Gonzalez::deleteGonzalezReturns(returnValues);

    return returnPoints;
}









void testMaximumRadiusFunction(vector<ColoredPoint>* clusteredPoints, int numberOfCluster){
    cout << "\n\n===== Testing Radius checker =====\n" << endl;
    double maxRadiusViaFunction = redclustering::calculateMaxRadius(*clusteredPoints, numberOfCluster);

	cout << "MaxRadius (Funktion): " << maxRadiusViaFunction << endl;
    return;
}













void testGraphBuildup(vector<ColoredPoint>* points){
    cout << "\n\n===== Testing of Graphlogic =====\n" << endl;

	// Buildup Graph
	Graph g;
	graphFlow::GraphData gData;
	CapacityMap capacity(g);

	// Add Nodes
	graphFlow::addNodesToGraph(g, gData, points);

	// Add Arcs
	graphFlow::addArcsToGraph(g, gData, 15, points);

	// Add Capacities
	graphFlow::addCapacitiesToGraph(capacity, gData);

	// Get Max Flow Value
	int maxFlowValue = graphFlow::getMaxFlow(g, capacity, gData);

	// Get Flow itself
	Flow* flow = graphFlow::calculateFlow(g, capacity, gData);

	// Print outcome
	graphFlow::printFlow(*flow, g, capacity, gData);
	printf("Value of this Flow is %d\n", maxFlowValue);

	// Flow von Kante nehmen
	printf("Flow der ersten Haupt-Kante: %d\n", graphFlow::getFlowOfArc(*flow, gData.mainArcs.at(0)));
	printf("Flow der zweiten Haupt-Kante: %d\n", graphFlow::getFlowOfArc(*flow, gData.mainArcs.at(1)));
	

	delete(flow);

    return;
}













void testRadiusChecker(vector<ColoredPoint>* points){
    cout << "\n\n===== Testing Radius checker =====\n" << endl;

	// Farben richtig rum haben
	fairlettFinder::makeCritFeatureSmalestFirst(points);

	// Kleine Radius Testen
	double radSmall = 5;
	printf("Gibt es ein erfolgreiches Matching bei r = %f? \t%d\n", radSmall, fairlettFinder::checkRadius(points, radSmall));

	// Mittleren Radius Testen
	double radMedium = 20;
	printf("Gibt es ein erfolgreiches Matching bei r = %f? \t%d\n", radMedium, fairlettFinder::checkRadius(points, radMedium));

	// Großen Radius Testen
	double radBig = 50;
	printf("Gibt es ein erfolgreiches Matching bei r = %f? \t%d\n", radBig, fairlettFinder::checkRadius(points, radBig));

	// Optimalen Radius finden
	double optRad = fairlettFinder::findBinaryPotentionalRadius(points);

	printf("Der Optimale Radius, bei dem Fairlets gebildet werden können ist %f\n", optRad);

}











void testCalculationOfAllRadii(vector<ColoredPoint>* points){
    cout << "\n\n===== Testing to Calculate all Radii =====\n" << endl;
    vector<double>* potRadii = fairlettFinder::calculateAllRadii(points);

	// Print Radii
	cout << "All Possible Radii:" << endl;
	for (size_t i = 0; i < potRadii->size(); i++){
		cout << potRadii->at(i) << endl;
	}

	delete potRadii;
}












void testMarkingFairlets(vector<ColoredPoint>* clusteredPoints){
    cout << "\n\n===== Testing Marking of the Fairletts =====\n" << endl;

    double fairlettDistance = fairlettFinder::markFairletts(clusteredPoints);

    printf("Der größte Abstand in einem Fairlett ist %f\n", fairlettDistance);
    
    printf("Alle Punkte direkt nach dem Markieren:\n");
    printAllpoints(clusteredPoints);

}













void testColorFiltering(vector<ColoredPoint>* points){
    cout << "\n\n===== Testing Colorfilter =====\n" << endl;

	// Fehler reinbringen
	points->at(0).setColor(GREEN);
	points->at(1).setColor(GREEN);
	points->at(3).setColor(GREEN);

	// Filtern und Richtig mappen
	fairlettFinder::makeCritFeatureSmalestFirst(points);

	vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = ColoredPoint::getPointsOfColor(points, BLUE);

	

	cout << "\nSize-Comparison:" << endl;
	cout << "\nAll Points: " << points->size() << endl;
	cout << "\nRed Points: " << redPoints->size() << endl;
	cout << "\nBlue Points: " << bluePoints->size() << endl;


	delete redPoints;
	delete bluePoints;

}













void testOnlyRedClustering(vector<ColoredPoint>* points, int k){
	cout << "\n\n===== Testing Clustering of only red points =====\n" << endl;

	printf("Aufbauen der Rückgabewerte\n");

	redclustering::FairFlowReturnValues* fairValues = redclustering::createFairFlowReturns(points);

	printf("Erstmal alle Punkte vor dem Clustern\n");
	printAllpoints(points);


	redclustering::clusterRedPoints(fairValues, k);

	printf("Alle Punkte nach dem Clustern nur mit den roten Punkten\n");
    printAllpoints(fairValues->clusteredPoints);

	printf("Jetzt nur die Zentren\n");
    printAllpoints(fairValues->centers);

	redclustering::deleteFairFlowReturns(fairValues);
}











void testFairRedClustering(vector<ColoredPoint>* points, int k){
	cout << "\n\n===== Testing Fair-Clustering with Red-Clustering =====\n" << endl;

	//printf("Erstmal alle Punkte vor dem Clustern\n");
	//printAllpoints(points);


	redclustering::FairFlowReturnValues* fairValues = redclustering::makeFairRedClustering(points, k);

	printf("\n\nAlle Punkte nach dem Clustern:\n");
    printAllpoints(fairValues->clusteredPoints);

	printf("\n\nJetzt nur die Zentren:\n");
    printAllpoints(fairValues->centers);

	printf("Maximaler Fairlettradius: %f \t Maximaler Clusterradius: %f\n", 
		fairValues->maxFairlettRadius, fairValues->maxClusterRadius);

	redclustering::deleteFairFlowReturns(fairValues);
}












void testFairlettFlitering(vector<ColoredPoint>* points){
	cout << "\n\n===== Testing Filter of Fairlets =====\n" << endl;
	// Fairletts in Punkten markieren
	fairlettFinder::markFairletts(points);

	// Punkte rausfiltern
	vector<ColoredPoint>* onlyFairlets = ColoredPoint::getPointsOfFairletts(points);

	// Punkte ungefiltert ausgeben
	cout << "=== Alle Punkte ungefiltert ===" << endl;
	printAllpoints(points);

	// Puntke gefiltert ausgeben
	cout << "=== Alle Punkte ungefiltert ===" << endl;
	printAllpoints(onlyFairlets);


	// Aufräumen
	delete(onlyFairlets);
}














void testAnchorMatrixFill(vector<ColoredPoint>* points){
	cout << "\n\n===== Testing the calculating of Anchors =====\n" << endl;

	// Matrix Anlegen
	vector<vector<fastAnchorFlow::Anchor>> anchorMatrix;

	// Anker berechnen
	fastAnchorFairlett::calculateAnchors(points, anchorMatrix);
	

	// Punkte alle ausgeben
	cout << "=== Alle Punkte ===" << endl;
	printAllpoints(points);

	// Matrix der Anker ausgeben
	cout << "=== AnkerMatrix ===" << endl;
	fastAnchorFairlett::printAnchorMatrix(anchorMatrix);
}
















void testAnchorRadiusChecker(vector<ColoredPoint>* points){
    cout << "\n\n===== Testing Searching Opt Rad with Anchors =====\n" << endl;

	// Farben richtig rum haben
	fastAnchorFairlett::makeCritFeatureSmalestFirst(points);

	// Anker berechnen
	AnchorMatrix aMatrix;
	fastAnchorFairlett::calculateAnchors(points, aMatrix);

	// Ankermatrix ausgeben
	fastAnchorFairlett::printAnchorMatrix(aMatrix);

	// Kleine Radius Testen
	double radSmall = 5;
	printf("Gibt es ein erfolgreiches Matching bei r = %f? \t%d\n", radSmall, fastAnchorFairlett::checkRadius(points, aMatrix, radSmall));

	// Mittleren Radius Testen
	double radMedium = 20;
	printf("Gibt es ein erfolgreiches Matching bei r = %f? \t%d\n", radMedium, fastAnchorFairlett::checkRadius(points, aMatrix, radMedium));

	// Großen Radius Testen
	double radBig = 50;
	printf("Gibt es ein erfolgreiches Matching bei r = %f? \t%d\n", radBig, fastAnchorFairlett::checkRadius(points, aMatrix, radBig));

	// Optimalen Radius finden
	double optRad = fastAnchorFairlett::findBinaryPotentionalRadius(points, aMatrix);

	printf("Der Optimale Radius, bei dem Fairlets gebildet werden können ist %f\n", optRad);

}












































void printAllpoints(vector<ColoredPoint>* points){
    //cout << "\n\n===== Printing all given Points =====\n" << endl;

    for (size_t i = 0; i < points->size(); i++){
        cout << std::setw(3) << i << ": " << points->at(i).toString() << endl;
    }
}















void savePointsToFile(string outputFileName, vector<ColoredPoint>* clusteredPoints){
    cout << "\n\n===== Write Data into File =====\n" << endl;

	ofstream outputFile = ofstream(outputFileName, ios::out);

	if(!outputFile.good()){
		cout << "Error opening Outputfile" << endl;
	} else{
		// max Radius an den Anfang packen
		//outputFile << "maxRadius," << returnValues->maxRadius << endl;

		// Punte abspeichern
		for (int i = 0; i < (int) clusteredPoints->size(); i++){
			outputFile << clusteredPoints->at(i).toCSV() << endl;
		}
	}
}