#include <iostream>

#include "ColoredPoint.h"
#include "PointParser.h"

int main(int argc, char **argv) {
	std::cout << "Hello World!\n";

	std::string fileName = "HandmadePoints.txt";

	//Printer printer = Printer();
	PointParser parser =  PointParser(fileName);

	vector<ColoredPoint>* points = parser.parseFile();

	for (int i = 0; i < (int) points->size(); i++)
	{
		std::cout << i << ": " << points->at(i).toString() << endl;;
	}

	// vector für Punkte wieder Freigeben
	delete points;

	std::cout << "\nTesting Distance\n";

	double coord1[] = { 0, 2 };
	ColoredPoint point1 = ColoredPoint(2, RED, coord1);

	double coord2[] = { 0, 0 };
	ColoredPoint point2 = ColoredPoint(2, BLUE, coord2);

	std::cout << "Distance: " << point1.distTo(point2) << endl;

	std::cout << "End Program" << std::endl;
}
