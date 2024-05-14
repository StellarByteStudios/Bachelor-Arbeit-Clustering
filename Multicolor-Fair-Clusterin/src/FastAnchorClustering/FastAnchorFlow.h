#pragma once
#include <vector>

#include "../Points/ColoredPoint.h"

#include <lemon/lgf_writer.h>
#include <lemon/list_graph.h>
#include <lemon/preflow.h>

using namespace lemon;

typedef ListDigraph Graph;
typedef Graph::Node Node;
typedef Graph::Arc Arc;
typedef ListDigraph::ArcMap<int> CapacityMap;
typedef Preflow<Graph, CapacityMap> Flow;
//typedef EdmondsKarp<Graph, CapacityMap> Flow;

namespace fastAnchorFlow{

    // Struct for the Anchors
    struct Anchor{
        // Distance to the Points who are Anchored to it
        double distToPartners;

        // True Index of the Anchorpoint in the pointslist
        int trueAnchorID;
    };


    // ==== Building the Graph ==== //
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

        // Anchor-Distances of each pair of points
        std::vector<std::vector<Anchor>> anchorDistance;
    };

    // uses an Radius and builds up finished Graph
    void buildupGraphFromAnchorDist(Graph&, GraphData&, CapacityMap&, double, vector<ColoredPoint>*);

    // Adding all red and blue Nodes and s and t to the graph
    void addNodesToGraph(Graph&, GraphData&, vector<ColoredPoint>*);
    
    // Adding all needed arcs to Graph
    // source --> redNodes
    // blueNodes --> target
    // redNodes --> blueNodes (if AnchorDist <= potRadius)
    void addArcsToGraph(Graph&, GraphData&, double, vector<ColoredPoint>*); 

    // sets the capacity of all arcs to one
    void addCapacitiesToGraph(CapacityMap&, GraphData&);



    // ==== Evaluate the Flow ==== //
    // calculates the Flow of the build-up graph
    Flow* calculateFlow(const Graph&, const CapacityMap&, const GraphData&);

    // Returns the Max-Flow Value of an given Graph
    int getMaxFlow(const Graph&, const CapacityMap&, const GraphData&);

    // gets the Flow on a single Arc
    int getFlowOfArc(const Flow&, const Arc);






    // ==== Debugging ==== //
    // Print Data from Graph
    void printGraph(const Graph&, const GraphData&);
    
    // Print Data from Graph
    void printGraphCapacity(const Graph&, const CapacityMap&, const GraphData&);

    // Print all Data with Flow
    void printFlow(const Flow&, const Graph&, const CapacityMap&, const GraphData&);
}
