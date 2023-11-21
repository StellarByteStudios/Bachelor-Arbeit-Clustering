#include <iostream>
//#include <filesystem>
#include <string>
//#include <sstream>
#include "Printer.h"
#include "BetterReader.h"
#include "ColoredPoint.h"
#include "PointParser.h"



int main()
{
    std::cout << "Hello World!\n";

    std::string fileName = "Points.txt";

    Printer printer = Printer();
    PointParser parser =  PointParser(fileName);

    vector<ColoredPoint>* points = parser.parseFile();

    for (int i = 0; i < (int) points->size(); i++)
    {
        printer.printnl(points->at(i).toString());
    }

    delete points;

    std::cout << "\nTesting Distance\n";

    double coord1[] = { 0, 2 };
    ColoredPoint point1 = ColoredPoint(2, RED, coord1);

    double coord2[] = { 0, 0 };
    ColoredPoint point2 = ColoredPoint(2, BLUE, coord2);

    std::cout << "Distance: " << point1.distTo(point2) << endl;

    std::cout << "End Programm" << std::endl; 

}