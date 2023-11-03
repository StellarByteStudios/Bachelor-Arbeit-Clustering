#include "Reader.h"

#include <iostream>
#include <sstream>
#include <filesystem>

#define LINELENGHT 250

Reader::Reader(const char* path)
{
    this->path = path;
}

Reader::~Reader()
{
    std::cout << "Reader is deleted" << std::endl;
}

const char* Reader::readLine(ifstream* inStream)
{
    // Testen ob Methode aufgerufen wird (wieder entfernen)
    std::cout << "Append on FileStringStream" << std::endl;
    return "new line\n";


    // Fehler falls File nicht offen
    if (!inStream->good())
    {
        return nullptr;
    }

    // R¸ckgabestring erstellen zum einlesen
    char* line = new char[LINELENGHT+1];

    // Zeile einlesen (max LINELENGHT Lang)
    inStream->getline(line, (std::streamsize) LINELENGHT);

    return line;
}



const char* Reader::readFile()
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
    std::stringstream fileStringStream; 
    
    // Versucht den Pfad auszulesen (wieder entfernen)
    fileStringStream << this->path;

    // Ausgabe des filestreams, ob der Pfad wirklich drin steht (wieder entfernen)
    std::cout << fileStringStream.str() << endl;;
    
    // F¸r alle Zeilen durchgehen
    /*
    while (!file->eof())
    {
        fileStringStream << this->readLine(file);
    }
    */
    
    // Testweiﬂe 5 Zeilen versuchen einzulesen (hier noch dummy lines)
    for (int i = 0; i < 5; i++)
    {
        fileStringStream << this->readLine(file);
    }
   
    // was ist jetzt im filestream? (wieder entfernen)
    std::cout << fileStringStream.str() << endl;;

    // File schlieﬂen
    file->close();

    return fileStringStream.str().c_str();
}
