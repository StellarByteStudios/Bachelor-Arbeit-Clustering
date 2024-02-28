#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"

#include "Lemon-Libary/lemon-1.3.1-build//preflow.h"

#include "FairlettBuildupTest.h"


// * Eigenes Dynamisches Beispiel * //
void buildBipatiteGraph(Graph& graph, CapacityMap& capacityMap, GraphData& gData){

    addNodesToGraph(graph, gData);
    printf("Knoten hinzugefügt\n");

    addArcsToGraph(graph, gData);
    printf("Arcs hinzugefügt\n");

    addCapacitiesToGraph(capacityMap, gData);
    printf("Kapazitäten hinzugefügt\n");

    return;     
}



// * = Knoten = * //
void addNodesToGraph(Graph& graph, GraphData& gData){
    
    // 10 Rote Knoten hinzufügen
    for (int i = 0; i < 10; i++){
        gData.redNodes.push_back(graph.addNode());
    }
    printf("Rote Knoten hinzugefügt\n");

    // 10 Blaue Knoten hinzufügen
    for (int i = 0; i < 10; i++){
        gData.blueNodes.push_back(graph.addNode());
    }
    printf("Blaue Knoten hinzugefügt\n");

    // Quelle und Senke hinzufügen
    gData.s = graph.addNode();
    gData.t = graph.addNode();
    printf("Quelle und Senke hinzugefügt\n");

    return; 
}



// * = Kanten = * //
void addArcsToGraph(Graph& graph, GraphData& gData){
    // Kanten von s zu Rot
    for (size_t i = 0; i < 10; i++){
        gData.sourceArcs.push_back(graph.addArc(gData.s, gData.redNodes.at(i)));
    }

    // Kanten von Blau zu t
    for (size_t i = 0; i < 10; i++){
        gData.targetArcs.push_back(graph.addArc(gData.blueNodes.at(i), gData.t));
    }

    // Kanten von Rot nach Blau, aber um eins versetzt, bzw letztes Rot geht auf erstes Blau
    for (size_t i = 0; i < 9; i++){
        gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(i), gData.blueNodes.at(i+1)));
    }
    // Letzte Quer-Kante
    gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(9), gData.blueNodes.at(0)));

    return;
}



// * = Kapazitäten = * //
void addCapacitiesToGraph(CapacityMap& capacityMap, GraphData& gData){
    // Kapazität 5 von Quelle zu allen Roten
    for (size_t i = 0; i < 10; i++){
        capacityMap[gData.sourceArcs.at(i)] = 5;
    }

    // Kapazität 6 von allen Blauen zur Senke
    for (size_t i = 0; i < 10; i++){
        capacityMap[gData.targetArcs.at(i)] = 6;
    }

    // Zwischenkanten Kapazität hochzählen
    for (size_t i = 0; i < 10; i++){
        capacityMap[gData.mainArcs.at(i)] = i+1;
    }
}



Flow* calculateFlow(Graph& graph, CapacityMap& capacityMap, GraphData& gData){

    // Preflow-Object erstellen
    Flow* preflow = new Flow(graph, capacityMap, gData.s, gData.t);

    // Flussalgorithmus ausführen
    preflow->run();

    return preflow;
}



void printFlow(Flow* preflow, Graph& graph, CapacityMap& capacityMap, GraphData& gData){
    // Maximaler Flussert ausgeben
    printf("Maximaler Flusswert: %d\nGraphausgabe:\n", preflow->flowValue());

    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
			arcMap("cap", capacityMap).             // write 'cost' for for arcs
			arcMap("flow", preflow->flowMap()).     // write 'flow' for for arcs
			node("source", gData.s).                // write s to 'source'
			node("target", gData.t).                // write t to 'target'
            arc("First-Main-Arc", gData.mainArcs.at(0)). 
			run();
    return; 
}



int getFlowOfArc(Flow& flow, Arc arc){
    int flowValue = flow.flow(arc);
    return flowValue;
}



int main(){
    
    Graph graph;
    GraphData gData;
    CapacityMap capacity(graph);
    
    buildBipatiteGraph(graph, capacity, gData);
    printf("Graph erstellt\n\n");


    Flow* preflow = calculateFlow(graph, capacity, gData);
    printf("Flow Berechnet\n");

    printf("Flow einzelner Kanten abfagen\n");
    int flowValTop = getFlowOfArc(*preflow, gData.mainArcs.at(0));
    int flowValBot = getFlowOfArc(*preflow, gData.mainArcs.at(9));

    printf("Flow der ersten Kante: %d\t(should be 1)\n", flowValTop);
    printf("Flow der letzten Kante: %d\t(should be 5)\n", flowValBot);

    printf("Zugriff auf Kante und ihre Inhaber\n");
    Arc firstArc = gData.mainArcs.at(0);
    Node arcSource = graph.source(firstArc);
    Node arcTarget = graph.target(firstArc);
    printf("Id der Kante: %d \tFlow auf der Kante: %d\n", graph.id(firstArc), getFlowOfArc(*preflow, firstArc));
    printf("Source: %d \t\tTarget: %d\n",graph.id(arcSource), graph.id(arcTarget));


    printf("Alle Daten Ausgeben:\n\n");
    printFlow(preflow, graph, capacity, gData);

    delete(preflow);

    return 0;
}

