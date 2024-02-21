#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"

#include "Lemon-Libary/lemon-1.3.1-build//preflow.h"

#include "FairlettBuildupTest.h"


// * Eigenes Dynamisches Beispiel * //
GraphStructure* buildBipatiteGraph(){

    printf("Vor allem\n");
    // Leeren Graph erzeugen
    GraphStructure* bibatiteGraph;
    //Graph g;

    //graphCopy(g, bibatiteGraph->graph).run();
    //bibatiteGraph->graph = g;

    printf("Graph-Struktur erzeugt\n");
    //digraphCopy(*emptyGraph, bibatiteGraph->graph);
    //bibatiteGraph->graph = new Graph();

    printf("Inhalt vom Graphen: %p\n", &bibatiteGraph->graph);
    //printf("Inhalt vom lokalen Graphen: %p\n", &g);


    /* = Knoten = */
    // Quelle und Senke hinzufügen
    bibatiteGraph->s = bibatiteGraph->graph.addNode();
    bibatiteGraph->t = bibatiteGraph->graph.addNode();

    printf("Quelle und Senke hinzugefügt\n");

    // 10 Rote und 10 Blaue Knoten hinzufügen
    //std::vector<Node> redNodes;
    //std::vector<Node> blueNodes;

    for (int i = 0; i < 10; i++){
        bibatiteGraph->redNodes.push_back(bibatiteGraph->graph.addNode());
        bibatiteGraph->blueNodes.push_back(bibatiteGraph->graph.addNode());
    }

    printf("Hauptknoten hinzugefügt\n");

    /* = Kanten = */
    // Kanten von s zu Rot
    //std::vector<Arc> sourceArcs;
    for (size_t i = 0; i < 10; i++){
        bibatiteGraph->sourceArcs
        .push_back(bibatiteGraph->graph.addArc(bibatiteGraph->s, bibatiteGraph->redNodes.at(i)));
    }

    // Kanten von Blau zu t
    std::vector<Arc> sinkArcs;
    for (size_t i = 0; i < 10; i++){
        sinkArcs.push_back(bibatiteGraph->graph.addArc(bibatiteGraph->blueNodes.at(i), bibatiteGraph->t));
    }

    printf("Quelle- und Senke-Kanten hinzugefügt\n");

    // Kanten von Rot nach Blau, aber um eins versetzt, bzw letztes Rot geht auf erstes Blau
    //std::vector<Arc> mainArcs;
    for (size_t i = 0; i < 9; i++){
        bibatiteGraph->mainArcs.push_back(bibatiteGraph->graph.addArc(bibatiteGraph->redNodes.at(i), bibatiteGraph->blueNodes.at(i+1)));
    }
    // Letzte Quer-Kante
    bibatiteGraph->mainArcs.push_back(bibatiteGraph->graph.addArc(bibatiteGraph->redNodes.at(9), bibatiteGraph->blueNodes.at(0)));

    printf("Hauptkanten hinzugefügt\n");

    /* = Kapazitäten = */
    // Kapazitäten map erstellen
    //ListDigraph::ArcMap<LimitValueType> capacity(bibatiteGraph->graph);
    //bibatiteGraph->capacityValues = new ListDigraph::ArcMap<LimitValueType>(bibatiteGraph->graph);
    //ListDigraph::ArcMap<double> capacity(bibatiteGraph->graph);
    //bibatiteGraph->capacityValues = capacity;
    
    
    // Kapazität 5 von Quelle zu allen Roten
    for (size_t i = 0; i < 10; i++){
        bibatiteGraph->capacityValues[bibatiteGraph->sourceArcs.at(i)] = 5;
    }

    // Kapazität 6 von allen Blauen zur Senke
    for (size_t i = 0; i < 10; i++){
        bibatiteGraph->capacityValues[bibatiteGraph->sinkArcs.at(i)] = 6;
    }

    // Zwischenkanten Kapazität hochzählen
    for (size_t i = 0; i < 10; i++){
        bibatiteGraph->capacityValues[bibatiteGraph->mainArcs.at(i)] = i+1;
    }

    printf("Kapazitäten hinzugefügt\n");
 
	// calculate max flow via preflows
    /*
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
    */
   return bibatiteGraph;
}
/*
Preflow<Graph>* calculateFlow(GraphStructure* graph){
    //Preflow<Graph> preflow(graph->graph, graph->capacityValues, graph->s, graph->t);
    Preflow<Graph> preflow((graph->graph), graph->capacityValues, graph->s, graph->t);

	preflow.run();

    return &preflow;
}
*/
void printFlow(Preflow<Graph>* preflow, GraphStructure* graph){
    digraphWriter(graph->graph).                 			 // write g to the standard output
			arcMap("cap", graph->capacityValues).        	 // write 'cost' for for arcs
			//arcMap("flow", preflow.flowMap()).   // write 'flow' for for arcs
			node("source", graph->s).            		 // write s to 'source'
			node("target", graph->t).            		 // write t to 'target'
			run();
    return; 
}
/*
ListDigraph::ArcMap<double> createCapacityMap(Graph& g) {
    // Kapazität von gegeben Graph erstellen
    ListDigraph::ArcMap<double> capacity(g);

    // leere Map zurückgeben
    return capacity;
}
*/

int main(){
    //GraphStructure* myGraph = buildBipatiteGraph();
    GraphStructure* myGraph;
    Graph local;
    printf("Adresse vom Graphen: %p\n", &myGraph->graph);
    printf("Adresse vom lokalen Graphen: %p\n", &local);
    printFlow(nullptr, myGraph);

    return 0;
}