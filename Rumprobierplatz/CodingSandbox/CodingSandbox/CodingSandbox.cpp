#include <iostream>
#include <filesystem>
#include <string>
//#include <sstream>
#include "Printer.h"
#include "BetterReader.h"
#include "ColoredPoint.h"
#include "PointParser.h"



int main()
{
    std::cout << "Hello World!\n";
    //std::cout << "Current path is " << std::filesystem::current_path() << '\n';

    std::string fileName = "Points.txt";


    


    //std::stringstream pathStream;

    //pathStream << std::filesystem::current_path() << fileName;

    //std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    //std::cout << fileStringStream.str() << endl;;

    //const char* path;

    Printer* printer = new Printer();
    PointParser* parser = new PointParser(fileName);

    vector<ColoredPoint>* points = parser->parseFile();

    for (int i = 0; i < points->size(); i++)
    {
        printer->printnl(points->at(i).toString());
    }

    //Reader* reader = new Reader(fileName);
    //BetterReader* reader = new BetterReader(fileName);

    /*

    // Knoten erzeugen und Ausgeben
    double coords[] = { 1.0, 2.0, 3.0 };
    std::cout << coords[0] << std::endl;
    std::cout << coords[1] << std::endl;
    std::cout << coords[2] << std::endl;
    ColoredPoint* point = new ColoredPoint(3, coords, RED);
    */

    //printer->printnl(point->toString().c_str());


    
    //printer->printnl("Printing via Printer");
    //printer->printnl(fileName);

    //char* fileInput = reader->readFile();

    //printer->printnl(fileInput);

    
    /*
    printer->printWithCounter("Printing via Object");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    */
    //delete printer;
    //delete reader;
    //delete fileInput;

   std::cout << "End Programm" << std::endl; 

}