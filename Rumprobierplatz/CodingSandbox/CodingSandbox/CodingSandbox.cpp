#include <iostream>
#include <filesystem>
//#include <sstream>
#include "Printer.h"
//#include "Reader.h"
#include "BetterReader.h"



int main()
{
    std::cout << "Hello World!\n";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';

    const char* fileName = "CodingSandbox.cpp";

    //std::stringstream pathStream;

    //pathStream << std::filesystem::current_path() << fileName;

    //std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    //std::cout << fileStringStream.str() << endl;;

    //const char* path;

    Printer* printer = new Printer();
    //Reader* reader = new Reader(fileName);
    BetterReader* reader = new BetterReader(fileName);

    printer->printnl("Printing via Printer");
    printer->printnl(fileName);

    char* fileInput = reader->readFile();

    printer->printnl(fileInput);

    
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