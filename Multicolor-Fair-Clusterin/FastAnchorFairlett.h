#pragma once
#include <vector>

#include "ColoredPoint.h"
#include "Gonzalez.h"
#include "FastAnchorFlow.h"

typedef fastAnchorFlow::GraphData FGraphData;
typedef fastAnchorFlow::Anchor Anchor;
typedef vector<vector<fastAnchorFlow::Anchor>> AnchorMatrix;

namespace fastAnchorFairlett{
    
    // ==== Calculating the Fairlets ==== //
    // calclulates the fairletts of some Points and updates the vector
    // returns the biggest distance of a fairlett
    double markFairletts(vector<ColoredPoint>*); // === TO-DO ===

    // Goes though all main arcs and marks the Fairletts if there is Flow
    // Also saves the AnchorsID
    // returns the Number of Fairletts made
    int markMainNodes(const Graph&, const Flow&, vector<Arc>, int, vector<ColoredPoint>*, AnchorMatrix&); // === TO-DO ===

    // Goes though all target arcs and marks all outliers which havent been
    // submittet to a Fairlett
    // returns the amount of outliers
    int markOutliers(const Graph&, const Flow&, vector<Arc>, int, vector<ColoredPoint>*); // === TO-DO ===

    // Change Kritical feature that 0 has less member than 1 for simpler calculation
    void makeCritFeatureSmalestFirst(vector<ColoredPoint>*);

    // Calculate all possible radii and find the lowest working radius with binary search
    double findBinaryPotentionalRadius(vector<ColoredPoint>*, AnchorMatrix&);

    // Calculates a List of all Potentional Radii, which is sorted
    vector<double>* calculateAllRadii(vector<ColoredPoint>*);

    // Checks if given radius is building all Fairletts
    // Needs first to have nRed <= nBlue
    bool checkRadius(vector<ColoredPoint>*, AnchorMatrix&, double);
    




    // ==== Matrix Calculation ==== //
    // Calculates the Anchors for all possible pairs
    void calculateAnchors(vector<ColoredPoint>*, AnchorMatrix&);

    // Calculates a n x n Matrix containing all pairwise distances
    void fillDistanceMatrix(vector<ColoredPoint>*, vector<vector<double>>&);


    



    // ==== Utility ==== //
    // maps the ID of a Node in a Graph to the Index in the filtered Points list
    int mapIDtoIndexByColor(int, Pointcolor, int);

    // Marks the Point in the base List with the new Fairlett ID
    void markFairlettWithAnchor(int, int, int, Pointcolor, int, vector<ColoredPoint>*); // === TO-DO ===

    // Gets the Index of the nth Point of a certain color
    int getTrueIndexOfPoint(int, Pointcolor, int, vector<ColoredPoint>*);






    // ==== Debugging ==== //
    void printAnchorMatrix(const AnchorMatrix&); 

    void printDistMatrix(const vector<vector<double>>&);

    void fairlettPartnerSanaty(vector<ColoredPoint>*);




    // ==== Testing Min Cost Flow ====//
    // calclulates the fairletts of some Points and updates the vector
    // returns the biggest distance of a fairlett
    double markMinCostFairletts(vector<ColoredPoint>*); // === TO-DO ===


    // Goes though all main arcs and marks the Fairletts if there is Flow
    // Also saves the AnchorsID
    // returns the Number of Fairletts made
    int markMainNodesMinCost(const Graph&, const CapScaling&, vector<Arc>, int, vector<ColoredPoint>*, AnchorMatrix&); // === TO-DO ===

    // Goes though all target arcs and marks all outliers which havent been
    // submittet to a Fairlett
    // returns the amount of outliers
    int markOutliersMinCost(const Graph&, const CapScaling&, vector<Arc>, int, vector<ColoredPoint>*); // === TO-DO ===
}