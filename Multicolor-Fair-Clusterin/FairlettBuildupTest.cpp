#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"

#include "Lemon-Libary/lemon-1.3.1-build//preflow.h"

#include "FairlettBuildupTest.h"


// * Eigenes Dynamisches Beispiel * //
void buildBipatiteGraph(Graph& graph, CapacityMap& capacityMap, GraphData& gData){

    printf("Vor allem\n");

    // * = Knoten = * //
    // Quelle und Senke hinzufügen
    gData.s = graph.addNode();
    gData.t = graph.addNode();

    printf("Quelle und Senke hinzugefügt\n");

    // 10 Rote und 10 Blaue Knoten hinzufügen
    //std::vector<Node> redNodes;
    //std::vector<Node> blueNodes;

    for (int i = 0; i < 10; i++){
        gData.redNodes.push_back(graph.addNode());
        gData.blueNodes.push_back(graph.addNode());
    }

    printf("Hauptknoten hinzugefügt\n");

    // * = Kanten = * //
    // Kanten von s zu Rot
    //std::vector<Arc> sourceArcs;
    for (size_t i = 0; i < 10; i++){
        gData.sourceArcs.push_back(graph.addArc(gData.s, gData.redNodes.at(i)));
    }

    // Kanten von Blau zu t
    //std::vector<Arc> sinkArcs;
    for (size_t i = 0; i < 10; i++){
        gData.sinkArcs.push_back(graph.addArc(gData.blueNodes.at(i), gData.t));
    }

    printf("Quelle- und Senke-Kanten hinzugefügt\n");

    // Kanten von Rot nach Blau, aber um eins versetzt, bzw letztes Rot geht auf erstes Blau
    //std::vector<Arc> mainArcs;
    for (size_t i = 0; i < 9; i++){
        gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(i), gData.blueNodes.at(i+1)));
    }
    // Letzte Quer-Kante
    gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(9), gData.blueNodes.at(0)));

    printf("Hauptkanten hinzugefügt\n");

    // * = Kapazitäten = * //
    // Kapazitäten map erstellen
    //CapacityMap capacity(graph);
    //bibatiteGraph->capacityValues = new ListDigraph::ArcMap<LimitValueType>(bibatiteGraph->graph);
    //ListDigraph::ArcMap<double> capacity(bibatiteGraph->graph);
    //bibatiteGraph->capacityValues = capacity;
    
    
    // Kapazität 5 von Quelle zu allen Roten
    for (size_t i = 0; i < 10; i++){
        capacityMap[gData.sourceArcs.at(i)] = 5;
    }

    // Kapazität 6 von allen Blauen zur Senke
    for (size_t i = 0; i < 10; i++){
        capacityMap[gData.sinkArcs.at(i)] = 6;
    }

    // Zwischenkanten Kapazität hochzählen
    for (size_t i = 0; i < 10; i++){
        capacityMap[gData.mainArcs.at(i)] = i+1;
    }

    printf("Kapazitäten hinzugefügt\n");

    printf("Ist sorce noch Valid?: %d\n", gData.s != INVALID);

    printf("Inhalt Vector sinkArcs: %ld\n", gData.sinkArcs.size());
    printf("Inhalt Vector mainArcs: %ld\n", gData.mainArcs.size());
    printf("Inhalt Vector redNodes: %ld\n", gData.redNodes.size());
 
	// calculate max flow via preflows
    /*
	Preflow<Graph> preflow(bibatiteGraph, capacity, s, t);

	preflow.run();

	std::cout << "maximum (Hardcoded Graph)flow by preflow: " << preflow.flowValue() << std::endl << std::endl;
    */

    // Finale Ausgabe
    /*
    // print graph details
	digraphWriter(graph).                 			 // write g to the standard output
			arcMap("cap", capacityMap).        	 // write 'cost' for for arcs
			//arcMap("flow", preflow.flowMap()).   // write 'flow' for for arcs
			node("source", gData.s).            		 // write s to 'source'
			node("target", gData.t).            		 // write t to 'target'
			run();*/
    return;  
}

Flow* calculateFlow(Graph& graph, CapacityMap& capacityMap, GraphData& gData){

    printf("Ist sorce noch Valid (in calculateFlow)?: %d\n", gData.s != INVALID);
    printf("Ist target noch Valid (in calculateFlow)?: %d\n", gData.t != INVALID);
    //printf("Ist CapacityMap noch Valid (in calculateFlow)?: %d\n", capacityMap[gData.sinkArcs.at(0)]);

    Flow* preflow = new Flow(graph, capacityMap, gData.s, gData.t);
    //Flow preflow = Flow(graph, capacityMap, gData.s, gData.t);
    //Preflow<Graph> preflow(g, capacity, s, t);

    printf("Flow erstellt\n");
    /*
    preflow.init();
    printf("Flow initialisiert\n");
	preflow.startFirstPhase();
    printf("Flow erste Phase geschaft\n");
    */
    preflow->run();

    return preflow;
}

void printFlow(Flow* preflow, Graph& graph, CapacityMap& capacityMap, GraphData& gData){
    // Kapazitäten bestimmen
    //CapacityMap capacity(graph);

    //Node source = gData.s;
    //Node target = gData.t;


    digraphWriter(graph).                 			 // write g to the standard output
			arcMap("cap", capacityMap).        	 // write 'cost' for for arcs
			arcMap("flow", preflow->flowMap()).   // write 'flow' for for arcs
			//node("source", gData.s).                		 // write s to 'source'
			//node("target", gData.t).            		 // write t to 'target'
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
    
    Graph graph;
    GraphData gData;
    CapacityMap capacity(graph);
    
    buildBipatiteGraph(graph, capacity, gData);

    printf("Graph erstellt\n\n\n");

    printf("Ist sorce noch Valid (in Main)?: %d\n\n", gData.s != INVALID);

    printf("Inhalt Vector sinkArcs (in Main): %ld\n", gData.sinkArcs.size());
    printf("Inhalt Vector mainArcs (in Main): %ld\n", gData.mainArcs.size());
    printf("Inhalt Vector redNodes (in Main): %ld\n\n", gData.redNodes.size());

    Flow* preflow = calculateFlow(graph, capacity, gData);

    printf("Flow Berechnet\n");

    printFlow(preflow, graph, capacity, gData);

    return 0;
}








// GPT Funktionierende Funktionsaufrufe
/*
// Define a function that modifies the ListGraph
void modifyGraph(Graph& graph) {
    // Add nodes and edges to the graph
    Node u = graph.addNode();
    Node v = graph.addNode();
    graph.addArc(u, v);

    // Example operation: print the number of nodes after modification
    std::cout << "After modification, the graph has " << lemon::countNodes(graph) << " nodes." << std::endl;
}

int main() {
    // Create a ListGraph instance
    Graph g;

    // Initially, the graph is empty
    std::cout << "Initially, the graph has " << lemon::countNodes(g) << " nodes." << std::endl;

    // Call the function, passing the graph as an argument
    modifyGraph(g);

    // The graph has been modified by the function
    std::cout << "Finally, the graph has " << lemon::countNodes(g) << " nodes." << std::endl;

    return 0;
}

*/