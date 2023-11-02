// ClusterAlgorithemBA.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "Printer.h"

int main()
{
    std::cout << "Hello World!\n";
    Printer* printer = new Printer();

    printer->printWithPrintfnl("Printing via Object");
    printer->printWithPrintfnl("Printing again");
    printer->printWithPrintfnl("Printing again");
    printer->printWithPrintfnl("Printing again");
    printer->printWithPrintfnl("Printing again");
    printer->printWithPrintfnl("Printing again");

    delete printer;

}
