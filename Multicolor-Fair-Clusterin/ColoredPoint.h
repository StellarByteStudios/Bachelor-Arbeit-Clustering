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
	/* Konstructor
	* (Dimensiones, Color of Point, Coords)
	*/
	ColoredPoint(int, Pointcolor, double[]);

	/* Destructor
	* Prints death Message
	*/
	~ColoredPoint();


	/* Distance-Method
	* Calculates the relative distance beween caller 
	* and the as Argument given Point
	*
	* @param partner: Other Point to messure Distance to
	*
	* @return relative distance
	*/
	double distTo(ColoredPoint);

	/* Same-Cluster-Method
	* Lookup if given Point is in the
	* same vluster as caller
	*
	* @param partner: Other Point to compare vluster
	*
	* @return true if same vluster
	*/
	bool sameClusterAs(ColoredPoint);

	/* ToString-Method
	* Constructs a String representive of calling Point
	* and returns it as char*
	*
	* @return string to Stringrepresentation of Point
	*/
	string toString();

	/* ToString-Method
	* Constructs a String of csv's with
	* data of the Point
	*
	* @return string of csv of the Point
	*/
	string toCSV();

	/* Info-Method
	* Simply returns the size of the Point
	*
	* @return dimensions
	*/
	int getDim();

	/* Info-Method
	* Simply returns the color of the Point
	*
	* @return color
	*/
	Pointcolor getColor();

	/* Update-Method
	* Sets Color of Point to new Color
	*
	* @param color: Value to set Color to
	*/
	void setColor(Pointcolor);

	/* Info-Method
	* Simply returns the cluster the Point is in
	*
	* @return cluster
	*/
	int getCluster();

	/* Cluster-Method
	* Sets Cluster of Point to given Value
	*
	* @param cluster: Value to set Cluster to
	*/
	void setCluster(int);

	/* Center-Method
	* Makes Point a Center
	*/
	void setToCenter();

	/* Info-Method
	* Simply returns if the Point is a center
	*
	* @return isCenter
	*/
	bool getIsCenter();

	/* Info-Method
	* Simply returns the fairlettID the Point belongs to
	*
	* @return fairlettID
	*/
	int getFairlettID();

	/* Cluster-Method
	* Sets the fairlettID of Point to given Value
	*
	* @param cluster: Value to set fairlettID to
	*/
	void setFairlettID(int);


	/* Info-Method
	* Simply returns the anchorID the Point belongs to
	*
	* @return anchorID
	*/
	int getAnchorID();

	/* Cluster-Method
	* Sets the fairlettID of Point to given Value
	*
	* @param cluster: Value to set anchorID to
	*/
	void setAnchorID(int);




	/* Utility-Method
	* Filters a list of Points in a certain color
	*/
	static vector<ColoredPoint>* getPointsOfColor(vector<ColoredPoint>*, Pointcolor);


	/* Utility-Method
	* Filterst Points if they belong to a Fairlett
	*/
    static vector<ColoredPoint>* getPointsOfFairletts(vector<ColoredPoint>*);
};

