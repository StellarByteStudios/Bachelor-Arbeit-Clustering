#pragma once
#include <vector>

#include "ColoredPoint.h"
#include "Gonzalez.h"

#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"
#include "Lemon-Libary/lemon-1.3.1-build/preflow.h"

using namespace std;
using namespace lemon;

typedef ListDigraph Graph;
typedef Graph::Node Node;
typedef Graph::Arc Arc;
typedef ListDigraph::ArcMap<int> CapacityMap;
typedef Preflow<Graph, CapacityMap> Flow;

namespace fairlettFinder{
    
    // ==== Calculating the Fairlets ==== //
    // calclulates the fairletts of some Points and updates the vector
    void markFairletts(vector<ColoredPoint>*); // * * TO-DO * * //

    // Change Kritical feature that 0 has less member than 1 for simpler calculation
    void makeCritFeatureSmalestFirst(vector<ColoredPoint>*);

    // Calculate all possible radii and find the lowest working radius
    double findPotentionalRadius(vector<ColoredPoint>*); // * * TO-DO * * //

    // Calculates a List of all Potentional Radii, which is sorted
    vector<double>* calculateAllRadii(vector<ColoredPoint>*);

    

    


    
    // ==== Building the Graph and let it Flow ==== //
    // struct of an build-up graph to pass-through functions
    struct GraphData{
        // Key-Nodes (source and target)
        Node s;
        Node t;

        // Nodes of the Points which should be matched
        std::vector<Node> redNodes;
        std::vector<Node> blueNodes;

        // Base-structure arcs (everything using source and target)
        std::vector<Arc> targetArcs;
        // Maybe not used in future
        std::vector<Arc> sourceArcs;

        // Arcs between the main-nodes of the graph
        std::vector<Arc> mainArcs;

        // Quantities of Nodes
        int nRed;
        int nBlue;
    };

    // Adding all red and blue Nodes and s and t to the graph
    void addNodesToGraph(Graph&, GraphData&, vector<ColoredPoint>*);
    
    // Adding all needed arcs to Graph
    // source --> redNodes
    // blueNodes --> target
    // redNodes --> blueNodes (potRadius)
    void addArcsToGraph(Graph&, GraphData&, double, vector<ColoredPoint>*); // * * TO-DO * * //

    // sets the capacity of all arcs to one
    void addCapacitiesToGraph(CapacityMap&, GraphData&);

    // calculates the Flow of the build-up graph
    Flow* calculateFlow(Graph&, CapacityMap&, GraphData&); // * * TO-DO * * //

    // gets the Flow on a single Arc
    int getFlowOfArc(Flow&, Arc); // * * TO-DO * * //

    


    // ==== Utility ==== //
    // goes though vector of points and returns a new vector with just one color
    vector<ColoredPoint>* getPointsOfColor(vector<ColoredPoint>*, Pointcolor);



    // ==== Debugging ==== //
    // Print Data from Graph
    void printGraph(Graph&, GraphData&);
    
    // Print Data from Graph
    void printGraphCapacity(Graph&, CapacityMap&, GraphData&);

    // Print all Data with Flow
    void printFlow(Flow*, Graph&, CapacityMap&, GraphData&);
}