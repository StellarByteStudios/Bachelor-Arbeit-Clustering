#include "PointParser.h"
#include <iostream> // std::cout; std::endl
#include <fstream>  // ifstream (Dateieneinlesen)



PointParser::PointParser(string path)
{
	this->path = path;
}

PointParser::~PointParser()
{
	cout << "PointParser is deleted" << endl;
}

vector<ColoredPoint>* PointParser::parseFile()
{
    // File aufmachen
    ifstream* file = new ifstream(this->path, ios::in);

    // Vector erstellen als Dynamische Datenstruktur
    vector<ColoredPoint>* points = new vector<ColoredPoint>;


    // Fehler falls File nicht offen
    if (!file->good())
    {
        std::cout << "ERROR while opening File " << path << std::endl;
        return nullptr;
    }

    // Punktezähler
    int numberOfPoints = 0;

    // Stück für Stück durch das File gehen und einlesen
    while (!file->eof() && numberOfPoints < MAXPOINTS)
    {
        // Zeile als String holen
        string line;
        std:getline(*file, line);

        // Gunddaten anlegen
        int dim;
        int colorAsInt;
        Pointcolor color;

        // Grunddaten aus dem String holen
        size_t pos = 0;
        // Dimensionen
        pos = line.find(',');
        dim = atoi(line.substr(0, pos).c_str());
        line.erase(0, pos + 1);
        // Farbe
        pos = line.find(',');
        colorAsInt = atoi(line.substr(0, pos).c_str());
        line.erase(0, pos + 1);
        color = static_cast<Pointcolor>(colorAsInt);

        // Abbruchfall für die letzte Zeile
        if (dim < 1)
        {
            break;
        }

        // Array für Punkte anlegen
        double* coords = new double[dim];

        // Einzelne Koordinaten parsen
        for (int i = 0; i < dim; i++)
        {
            pos = line.find(',');
            double temp = atof(line.substr(0, pos).c_str());
            line.erase(0, pos + 1);
            coords[i] = temp;
        }

        // Alles zu einem Punkt zusammenfassen
        ColoredPoint* temp = new ColoredPoint(dim, coords, color);

        // In den Vector pushen
        points->push_back(*temp);

        // Zähler erhöhen
        numberOfPoints++;
    }

	return points;
}
