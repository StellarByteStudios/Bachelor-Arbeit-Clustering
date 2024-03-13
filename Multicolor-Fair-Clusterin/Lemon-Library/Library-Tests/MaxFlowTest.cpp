// Copied and edited from https://gist.github.com/huanyud/45f98d8bf8d6df66d3e7ab3e9a85af90

#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"


#include "Lemon-Libary/lemon-1.3.1-build/preflow.h"

using namespace lemon;
typedef ListDigraph Graph;
typedef int LimitValueType;
typedef Graph::Node Node;
typedef Graph::Arc Arc;


// * Eigenes Dynamisches Beispiel * //
void maxFlowDynamicBipatite(){

    // Leeren Graph erzeugen
    Graph bibatiteGraph;


    /* = Knoten = */
    // Quelle und Senke hinzufügen
    Node s = bibatiteGraph.addNode();
    Node t = bibatiteGraph.addNode();

    // 10 Rote und 10 Blaue Knoten hinzufügen
    std::vector<Node> redNodes;
    std::vector<Node> blueNodes;

    for (int i = 0; i < 10; i++){
        redNodes.push_back(bibatiteGraph.addNode());
        blueNodes.push_back(bibatiteGraph.addNode());
    }


    /* = Kanten = */
    // Kanten von s zu Rot
    std::vector<Arc> sourceArcs;
    for (size_t i = 0; i < 10; i++){
        sourceArcs.push_back(bibatiteGraph.addArc(s, redNodes.at(i)));
    }

    // Kanten von Blau zu t
    std::vector<Arc> sinkArcs;
    for (size_t i = 0; i < 10; i++){
        sinkArcs.push_back(bibatiteGraph.addArc(blueNodes.at(i), t));
    }

    // Kanten von Rot nach Blau, aber um eins versetzt, bzw letztes Rot geht auf erstes Blau
    std::vector<Arc> mainArcs;
    for (size_t i = 0; i < 9; i++){
        mainArcs.push_back(bibatiteGraph.addArc(redNodes.at(i), blueNodes.at(i+1)));
    }
    // Letzte Quer-Kante
    mainArcs.push_back(bibatiteGraph.addArc(redNodes.at(9), blueNodes.at(0)));


    /* = Kapazitäten = */
    // Kapazitäten map erstellen
    ListDigraph::ArcMap<LimitValueType> capacity(bibatiteGraph);

    // Kapazität 5 von Quelle zu allen Roten
    for (size_t i = 0; i < 10; i++){
        capacity[sourceArcs.at(i)] = 5;
    }

    // Kapazität 6 von allen Blauen zur Senke
    for (size_t i = 0; i < 10; i++){
        capacity[sinkArcs.at(i)] = 6;
    }

    // Zwischenkanten Kapazität hochzählen
    for (size_t i = 0; i < 10; i++){
        capacity[mainArcs.at(i)] = i+1;
    }
    /**
	 * calculate max flow via preflows
	 */
	Preflow<Graph> preflow(bibatiteGraph, capacity, s, t);

	preflow.run();

	std::cout << "maximum (Hardcoded Graph)flow by preflow: " << preflow.flowValue() << std::endl << std::endl;


    // Finale Ausgabe

    // print graph details
	digraphWriter(bibatiteGraph).                 			 // write g to the standard output
			arcMap("cap", capacity).        	 // write 'cost' for for arcs
			arcMap("flow", preflow.flowMap()).   // write 'flow' for for arcs
			node("source", s).            		 // write s to 'source'
			node("target", t).            		 // write t to 'target'
			run();
    return;  
}





// * Kopiertes & Modifiziertes Beispiel * //
void flowPreflowHardcoded()
{
/*    Beispielgraph 1
*      o---->q
*     / \     \
*    /   \     \
*   s     \     t
*    \     \   /
*     \     \ /
*      p---->r
*/

	Graph g;

	// source and sink vertices
	Node s = g.addNode();
    Node t = g.addNode();

	// a and b
	Node o = g.addNode();
    Node p = g.addNode();
    Node q = g.addNode();
    Node r = g.addNode();

	Arc so = g.addArc(s, o);
    Arc sp = g.addArc(s, p);
    Arc oq = g.addArc(o, q);
    Arc pr = g.addArc(p, r);
    Arc rt = g.addArc(r, t);
    Arc qt = g.addArc(q, t);
    Arc o_r = g.addArc(o, r); // or ist vorreserviert


	std::vector<Arc> arcs = { so, sp, oq, pr, rt, qt, o_r};

	ListDigraph::ArcMap<LimitValueType> capacity(g);
	capacity[so] = 4; 
    capacity[sp] = 4;
	capacity[oq] = 2;
	capacity[pr] = 1;
	capacity[qt] = 3; 
    capacity[rt] = 3;
    capacity[o_r] = 5;

	/**
	 * calculate max flow via preflows
	 */
	Preflow<Graph> preflow(g, capacity, s, t);

	preflow.run();

	std::cout << "maximum (Hardcoded Graph)flow by preflow: " << preflow.flowValue() << std::endl << std::endl;

	// print graph details
	digraphWriter(g).                 			 // write g to the standard output
			arcMap("cap", capacity).        	 // write 'cost' for for arcs
			arcMap("flow", preflow.flowMap()).   // write 'flow' for for arcs
			node("source", s).            		 // write s to 'source'
			node("target", t).            		 // write t to 'target'
			run();

}

int main(){

    flowPreflowHardcoded();
    printf("\n===========================\nJetzt Dynamischer Graph:\n");
    maxFlowDynamicBipatite();
    return 0;
}