#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"

#include "Lemon-Libary/lemon-1.3.1-build//preflow.h"

using namespace lemon;
typedef ListDigraph Graph;
typedef int LimitValueType;
typedef Graph::Node Node;
typedef Graph::Arc Arc;

// Struktur eines Aufgebauten Graphen zum durchreichen durch Methoden
struct GraphStructure{
    // Graph an sich
    Graph graph;

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

    // Kapazitäten der einzelnen Kanten
    // Vielelicht Rausschmeißen und in jeder Methode neu erzeugen
    // Persistenz ist dann noch zu überprüfen
    ListDigraph::ArcMap<LimitValueType> capacityValues;

    //GraphStructure(){ListDigraph::ArcMap<LimitValueType> capacityValues(graph)}
};


// * Eigenes Dynamisches Beispiel * //
GraphStructure* buildBipatiteGraph();

Preflow<Graph>* calculateFlow(GraphStructure*);

ListDigraph::ArcMap<double> createCapacityMap(Graph& );

void printFlow(Preflow<Graph>*, GraphStructure*);