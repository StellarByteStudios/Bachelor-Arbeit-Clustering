// ClusterAlgorithemBA.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <filesystem>
#include <sstream>
#include "Printer.h"
#include "Reader.h"



int main()
{
    std::cout << "Hello World!\n";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';

    const char* fileName = "Testfile.txt";

    std::stringstream pathStream;

    pathStream << std::filesystem::current_path() << fileName;

    //std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    //std::cout << fileStringStream.str() << endl;;

    const char* path;

    Printer* printer = new Printer();
    Reader* reader = new Reader(fileName);

    printer->printnl("Printing via Printer");
    printer->printnl(fileName);

    const char* fileInput = reader->readFile();

    printer->printnl(fileInput);

    
    /*
    printer->printWithCounter("Printing via Object");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    printer->printWithCounter("Printing again");
    */
    delete printer;
    delete reader;

    std::cout << "End Programm" << endl;

}
