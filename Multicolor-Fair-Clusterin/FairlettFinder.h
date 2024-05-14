#pragma once
#include <vector>

#include "Points/ColoredPoint.h"
#include "Gonzalez/Gonzalez.h"
#include "GraphFlow.h"

typedef graphFlow::GraphData GraphData;

namespace fairlettFinder{
    
    // ==== Calculating the Fairlets ==== //
    // calclulates the fairletts of some Points and updates the vector
    // returns the biggest distance of a fairlett
    double markFairletts(vector<ColoredPoint>*);

    // Goes though all main arcs and marks the Fairletts if there is Flow
    // returns the Number of Fairletts made
    int markMainNodes(const Graph&, const Flow&, vector<Arc>, int, vector<ColoredPoint>*);

    // Goes though all target arcs and marks all outliers which havent been
    // submittet to a Fairlett
    // returns the amount of outliers
    int markOutliers(const Graph&, const Flow&, vector<Arc>, int, vector<ColoredPoint>*);

    // Change Kritical feature that 0 has less member than 1 for simpler calculation
    void makeCritFeatureSmalestFirst(vector<ColoredPoint>*);

    // Calculate all possible radii and find the lowest working radius with binary search
    double findBinaryPotentionalRadius(vector<ColoredPoint>*);

    // Calculates a List of all Potentional Radii, which is sorted
    vector<double>* calculateAllRadii(vector<ColoredPoint>*);

    // Checks if given radius is building all Fairletts
    // Needs first to have nRed <= nBlue
    bool checkRadius(vector<ColoredPoint>*, double);
    

    



    // ==== Utility ==== //
    // maps the ID of a Node in a Graph to the Index in the filtered Points list
    int mapIDtoIndexByColor(int, Pointcolor, int);

    // Marks the Point in the base List with the new Fairlett ID
    void markSinglePointWithFairlett(int, int, Pointcolor, int, vector<ColoredPoint>*);


}