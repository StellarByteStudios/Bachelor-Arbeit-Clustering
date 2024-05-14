#include "PointParser.h"
#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateieneinlesen)


// * * * =========== Kon/Destruktor =========== * * * //
PointParser::PointParser(string path){
	this->path = path;
}

PointParser::~PointParser(){
}


// * * * =========== Parsing of CSV File =========== * * * //
vector<ColoredPoint>* PointParser::parseFile(){
    // File aufmachen
    ifstream file = ifstream(this->path, ios::in);

    // Vector erstellen als Dynamische Datenstruktur
    vector<ColoredPoint>* points = new vector<ColoredPoint>;


    // Fehler falls File nicht offen
    if (!file.good()){
        std::cout << "ERROR while opening File " << path << std::endl;
        return nullptr;
    }

    // Punktezähler
    int numberOfPoints = 0;

    // Dimensionen bestimmen
    // Erste Zeile als String holen
    string firstLine;
    std::getline(file, firstLine);
    int dim = this->countDim(firstLine);

    // Stück für Stück durch das File gehen und einlesen
    while (!file.eof() && numberOfPoints < MAXPOINTS){
        // Zeile als String holen
        string line;
        std::getline(file, line);

        // Gunddaten anlegen
        int colorAsInt;
        Pointcolor color;

        // Farbe aus dem String holen
        size_t pos = 0;
        pos = line.find(',');
        colorAsInt = atoi(line.substr(0, pos).c_str());
        line.erase(0, pos + 1);
        color = static_cast<Pointcolor>(colorAsInt);

        //Abbruchfall für die letzte Zeile (leerzeilen)
        if (line.size() < 1){
            break;
        }

        // Array für Punkte anlegen
        double coords[dim];

        // Einzelne Koordinaten parsen
        for (int i = 0; i < dim; i++){
            pos = line.find(',');
            double temp = atof(line.substr(0, pos).c_str());
            line.erase(0, pos + 1);
            coords[i] = temp;
        }

        // Alles zu einem Punkt zusammenfassen
        ColoredPoint temp = ColoredPoint(dim, color, coords);

        // In den Vector pushen
        points->push_back(temp);


        // Zähler erhöhen
        numberOfPoints++;
    }

	return points;
}

int PointParser::countDim(string line){
    int coms = 0;
    // Durch alle Character des Strings durchgehen
    for (int i = 0; i < (int) line.length(); i++){
        // ist der Character ein Komma?
        if (line[i] == ','){
            coms++;
        }
    }
    return coms;
}
