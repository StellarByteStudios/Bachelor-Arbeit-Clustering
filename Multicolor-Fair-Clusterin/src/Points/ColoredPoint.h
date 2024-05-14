#pragma once

#include <string>
#include <vector>

using namespace std;

enum Pointcolor{
	RED = 0,
	BLUE = 1,
	GREEN = 2
};

class ColoredPoint{
private:
	// Coordinates of the Point (Pointer because variable dimensions)
	vector<double> coordinates;

	// Dimensionality of the Point
	int dim;

	// Which cluster the Point is part of
	int cluster;

	// Which Fairlett the Point is part of
	int fairlettID;

	// Index of the point, which is this points anchor
	int anchorID;

	// Is the Point a Center
	bool isCenter;

	// Color of the Point
	Pointcolor color;


public:
	// Constructor
	ColoredPoint(int, Pointcolor, double[]);

	// Calculates the relative, eucledean distance beween caller and the as Argument given Point
	double distTo(ColoredPoint);

	// Same-Cluster-Method
	// Lookup if given Point is in thesame vluster as caller
	bool sameClusterAs(ColoredPoint);

	// ToString-Method
	// Constructs a String representive of calling Point and returns it as char*
	string toString();

	// ToString-Method
	// Constructs a String of csv's with data of the Point
	string toCSV();

	// * * * =========== Getter and Setter =========== * * * //
	int getDim();

	Pointcolor getColor();
	void setColor(Pointcolor);

	int getCluster();
	void setCluster(int);

	void setToCenter();
	bool getIsCenter();

	int getFairlettID();
	void setFairlettID(int);

	int getAnchorID();
	void setAnchorID(int);



	// * * * =========== Static-Utility-Methods =========== * * * //
	// Filters a list of Points in a certain color
	static vector<ColoredPoint>* getPointsOfColor(vector<ColoredPoint>*, Pointcolor);

	// Filterst Points if they belong to a Fairlett
    static vector<ColoredPoint>* getPointsOfFairletts(vector<ColoredPoint>*);
};

