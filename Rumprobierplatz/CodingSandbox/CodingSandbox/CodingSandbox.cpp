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

   std::cout << "End Programm" << std::endl; 

}