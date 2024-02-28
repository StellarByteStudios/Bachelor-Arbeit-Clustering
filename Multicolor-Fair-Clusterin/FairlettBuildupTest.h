#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"

#include "Lemon-Libary/lemon-1.3.1-build//preflow.h"

using namespace lemon;
typedef ListDigraph Graph;
typedef Graph::Node Node;
typedef Graph::Arc Arc;
typedef ListDigraph::ArcMap<int> CapacityMap;
typedef Preflow<Graph, CapacityMap> Flow;

// Struktur eines Aufgebauten Graphen zum durchreichen durch Methoden
struct GraphData{
    // Key-Nodes (Quelle und Senke)
    Node s;
    Node t;

    // Punkte welche Fairlets bilden Sollen
    std::vector<Node> redNodes;
    std::vector<Node> blueNodes;

    // Grundstruktur-Kanten (alles von Quelle und Senke)
    // Voraussichtlich nicht mehr notwendig
    std::vector<Arc> sourceArcs;
    std::vector<Arc> sinkArcs;

    // Kanten zwischen den Hauptpunkten des Graphen
    std::vector<Arc> mainArcs;
};


// * Eigenes Dynamisches Beispiel * //
void buildBipatiteGraph(Graph&, CapacityMap&, GraphData&);

void addNodesToGraph(Graph&, GraphData&);

void addArcsToGraph(Graph&, GraphData&);

void addCapacitiesToGraph(CapacityMap&, GraphData&);

Flow* calculateFlow(Graph&, CapacityMap&, GraphData&);

void printFlow(Flow*, Graph&, CapacityMap&, GraphData&);

int getFlowOfArc(Flow&, Arc);