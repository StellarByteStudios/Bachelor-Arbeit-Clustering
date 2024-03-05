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
    
    
    struct FairFlowReturnValues{
		vector<ColoredPoint>* clusteredPoints;
		vector<ColoredPoint>* centers;
		double maxRadius;
	};

    // Method which uses the Max-Flow and Gonzalez Algorithm to cluster an unfair amount of Points
    FairFlowReturnValues makeFairFlowClustering(vector<ColoredPoint>*, int);

    // Creating an empty Struct for Max-Flow-Clustering
	FairFlowReturnValues* createGonzalezReturns(vector<ColoredPoint>*);

	// Clean-Up for Max-Flow-Clustering Returnvalues
	void deleteFairFlowReturns(FairFlowReturnValues*);

    
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
    };

    // Adding all red and blue Nodes and s and t to the graph
    void addNodesToGraph(Graph&, GraphData&);
    
    // Adding all needed arcs to Graph
    // source --> redNodes
    // blueNodes --> target
    // redNodes --> blueNodes (potRadius)
    void addArcsToGraph(Graph&, GraphData&, double);

    // sets the capacity of all arcs to one
    void addCapacitiesToGraph(CapacityMap&, GraphData&);

    // calculates the Flow of the build-up graph
    Flow* calculateFlow(Graph&, CapacityMap&, GraphData&);

    // gets the Flow on a single Arc
    int getFlowOfArc(Flow&, Arc);


    // ==== Calculating the Fairlets ==== //
    // Calculate all possible radii and find the lowest working radius
    double findPotentionalRadius(vector<ColoredPoint>*);   

    // Change Kritical feature that 0 has less member than 1 for simpler calculation
    void makeCritFeatureSmalestFirst(vector<ColoredPoint>*);

    // calclulates the fairletts of some Points and updates the vector
    void markFairletts(vector<ColoredPoint>*);
    



    // ==== Clustering with Fairlets ==== //
    // clusters points with krit-feature = 0 with Gonzalez algorithm
    void clusterRedPoints(vector<ColoredPoint>*);
    
    // returns just the red points which a used for the clustering
    vector<ColoredPoint>* filterRedPoints(vector<ColoredPoint>*);

    // walks though all points, filter by their cluster and calculates the biggest cluster
    double calculateMaxRadius(vector<ColoredPoint>, int);

    // using the clustered red points and their fairlettID to asign 
    // the clusters to blue points. Includes outlier
    void updateClusterOfBluePoints(vector<ColoredPoint>*);



    // ==== Debugging ==== //
    // Print Data from Graph
    void printGraph(Graph&, GraphData&);
    
    // Print Data from Graph
    void printGraphCapacity(Graph&, CapacityMap&, GraphData&);

    // Print all Data with Flow
    void printFlow(Flow*, Graph&, CapacityMap&, GraphData&);
}