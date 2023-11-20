#include "BetterReader.h"

#include <iostream> // std::cout; std::endl
#include <sstream>  // stringstream (String builder)
#include <fstream>  // ifstream (Dateieneinlesen)
#include <iomanip> // setw()

#define MAXLINE 250



BetterReader::BetterReader(string path)
{
	this->path = path;
}

BetterReader::~BetterReader()
{
	std::cout << "Reader is deleted" << std::endl;
}

string BetterReader::readFile()
{
    // File aufmachen
    ifstream* file = new ifstream(this->path, ios::in);
    

    // Fehler falls File nicht offen

    if (!file->good())
    {
        std::cout << "ERROR while opening File " << path << std::endl;
        return nullptr;
    }


    // C++ Version des Stringbuilders
    stringstream fileStringStream;

    // Zeilenzähler
    int row = 0;

    // Stück für Stück durch das File gehen und einlesen
    while (!file->eof())
    {
        // Buffer zum reinladen erzeugen
        char line[MAXLINE];
        // Zeile einlesen
        file->getline(line, MAXLINE-1);
        // Alles in den String Stream packen
        fileStringStream << setw(3) << row << ":" << line << endl;
        // Zeilenzähler erhöhen
        row++;
    }

    // Neuen groß genugen String erzeugen
    //char* page = new char[strlen(fileStringStream.str().c_str())];
    //strcpy_s(page, strlen(page), fileStringStream.str().c_str());
	return fileStringStream.str();
}
