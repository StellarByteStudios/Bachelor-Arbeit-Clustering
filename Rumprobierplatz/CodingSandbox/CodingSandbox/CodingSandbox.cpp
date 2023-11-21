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

    Printer* printer = new Printer();
    PointParser* parser = new PointParser(fileName);

    vector<ColoredPoint>* points = parser->parseFile();

    for (int i = 0; i < (int) points->size(); i++)
    {
        printer->printnl(points->at(i).toString());
    }

    //delete printer;
    //delete reader;
    //delete fileInput;

   std::cout << "End Programm" << std::endl; 

}