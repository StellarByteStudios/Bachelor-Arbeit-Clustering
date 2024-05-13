#include "FastAnchorFlow.h"

// * * * =========== Building the Graph and let it Flow =========== * * * //
void fastAnchorFlow::buildupGraphFromAnchorDist(Graph& graph, GraphData& gData, CapacityMap& capacity, double potRad, vector<ColoredPoint>* points){
    // Knoten hinzufügen
	addNodesToGraph(graph, gData, points);

	// Kanten hinzufügen
	addArcsToGraph(graph, gData, potRad, points);

	// Kapazitäten hinzufügen
	addCapacitiesToGraph(capacity, gData);
}



void fastAnchorFlow::addNodesToGraph(Graph& graph, GraphData& gData, vector<ColoredPoint>* points){

    // Anzahl aller Punkte
    int n = (int) points->size();

    // Rote Knoten hinzufügen (Krit Feature = 0)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == RED){
            gData.redNodes.push_back(graph.addNode());
        }
    }

    // Blaue Knoten hinzufügen (Krit Feature = 1)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == BLUE){
            gData.blueNodes.push_back(graph.addNode());
        }
    }

    // Quelle und Senke hinzufügen
    gData.s = graph.addNode();
    gData.t = graph.addNode();

    return; 
}



void fastAnchorFlow::addArcsToGraph(Graph& graph, GraphData& gData, double potRad, vector<ColoredPoint>* points){
    // Anzahl an Knoten herausfinden
    int nRed = (int) gData.redNodes.size();
    int nBlue = (int) gData.blueNodes.size();

    // Kanten von s zu allen Roten Knoten
    for (int i = 0; i < nRed; i++){
        gData.sourceArcs.push_back(graph.addArc(gData.s, gData.redNodes.at(i)));
    }

    // Kanten von Blau zu t
    for (int i = 0; i < nBlue; i++){
        gData.targetArcs.push_back(graph.addArc(gData.blueNodes.at(i), gData.t));
    }

    // Kanten von Rot nach Blau, abhänging von ihrem Abstand (potRad)
    // Punkte in Farben Aufteilen
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = ColoredPoint::getPointsOfColor(points, BLUE);


    // Kurzer Sanity Check
    if (nRed != (int) redPoints->size() || nBlue != (int) bluePoints->size()){
        printf("ERROR: Fehler bei Grapherstellung!\n");
        printf("Anzahl roter Knoten im Graph %d; \t Anzahl roter Punkte %ld\n", nRed, redPoints->size());
        printf("Anzahl blauer Knoten im Graph %d; \t Anzahl blauer Punkte %ld\n", nBlue, bluePoints->size());
    }
    
    // Alle roten Punkte durchgehen
    for (int redIndex = 0; redIndex < nRed; redIndex++){
        // Alle blauen Punkte durchgehen
        for (int blueIndex = 0; blueIndex < nBlue; blueIndex++){
            // Schauen ob das eine Passende Kante ist
            if (gData.anchorDistance[redIndex][blueIndex].distToPartners <= potRad){
                // Kante Hinzufügen
                gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(redIndex), gData.blueNodes.at(blueIndex)));
            } 
        }
    }

    // Gefilterte Punkte wieder frei geben
    delete redPoints;
    delete bluePoints;

    return;
}



void fastAnchorFlow::addCapacitiesToGraph(CapacityMap& capacityMap, GraphData& gData){
    // Kapazität von Quelle zu allen Roten
    for (size_t i = 0; i < gData.sourceArcs.size(); i++){
        capacityMap[gData.sourceArcs.at(i)] = 1;
    }

    // Kapazität von allen Blauen zur Senke
    for (size_t i = 0; i < gData.targetArcs.size(); i++){
        capacityMap[gData.targetArcs.at(i)] = 1;
    }

    // Zwischenkanten Kapazität
    for (size_t i = 0; i < gData.mainArcs.size(); i++){
        capacityMap[gData.mainArcs.at(i)] = 1;
    }

}



Flow* fastAnchorFlow::calculateFlow(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Preflow-Object erstellen
    Flow* preflow = new Flow(graph, capacityMap, gData.s, gData.t);

    // Flussalgorithmus ausführen
    preflow->run();

    return preflow;
}


int fastAnchorFlow::getMaxFlow(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Flussalgorithmus laufen lassen
    Flow* flow = calculateFlow(graph, capacityMap, gData);

    // Wert abspeichern
    double flowValue = flow->flowValue();

    // Speicher wieder freigeben
    delete(flow);

    // Wert zurück geben
    return flowValue;
}



int fastAnchorFlow::getFlowOfArc(const Flow& flow, const Arc arc){
    int flowValue = flow.flow(arc);
    return flowValue;
}












// ==== Debugging ==== //
void fastAnchorFlow::printGraph(const Graph& graph, const GraphData& gData){
    // Grunddaten
    printf("=== Daten welche zum Graphen gespeichert sind ===\n");
    printf("Anzahl roter Knoten im Graphen: %d\n", (int) gData.redNodes.size());
    printf("Anzahl blauer Knoten im Graphen: %d\n", (int) gData.blueNodes.size());
    
    
    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
            node("first-red:", gData.redNodes.at(0)).// Erster Roter Knoten
            node("first-blue:", gData.blueNodes.at(0)).// Erster Roter Knoten
			node("source:", gData.s).                // write s to 'source'
			node("target:", gData.t).                // write t to 'target'
			run();
    return; 
}

void fastAnchorFlow::printGraphCapacity(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Grunddaten
    printf("=== Daten welche zum Graphen gespeichert sind ===\n");
    printf("Anzahl roter Knoten im Graphen: %d\n", (int) gData.redNodes.size());
    printf("Anzahl blauer Knoten im Graphen: %d\n", (int) gData.blueNodes.size());

    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
			arcMap("cap", capacityMap).             // write 'cost' for for arcs
            node("first-red:", gData.redNodes.at(0)).// Erster Roter Knoten
            node("first-blue:", gData.blueNodes.at(0)).// Erster Roter Knoten
			node("source:", gData.s).                // write s to 'source'
			node("target:", gData.t).                // write t to 'target'
			run();
    return; 
}

void fastAnchorFlow::printFlow(const Flow& preflow, const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Grunddaten
    printf("=== Daten welche zum Graphen gespeichert sind ===\n");
    printf("Anzahl roter Knoten im Graphen: %d\n", (int) gData.redNodes.size());
    printf("Anzahl blauer Knoten im Graphen: %d\n", (int) gData.blueNodes.size());
    // Maximaler Flussert ausgeben
    printf("Maximaler Flusswert: %d\nGraphausgabe:\n", preflow.flowValue());

    // Graphstruktur ausgeben
    digraphWriter(graph).                           // write g to the standard output
			arcMap("cap", capacityMap).             // write 'cost' for for arcs
			arcMap("flow", preflow.flowMap()).     // write 'flow' for for arcs
            node("first-red:", gData.redNodes.at(0)).// Erster Roter Knoten
            node("first-blue:", gData.blueNodes.at(0)).// Erster Roter Knoten
			node("source:", gData.s).                // write s to 'source'
			node("target:", gData.t).                // write t to 'target'
			run();
    return; 
}







































































// * * * =========== Building the Graph and let it Flow =========== * * * //
void fastAnchorFlow:: buildupGraphFromAnchorDistMinCost(Graph& graph, GraphData& gData, CapacityMap& capacity, CostMap& costs, double potRad, vector<ColoredPoint>* points){
    // Knoten hinzufügen
	addNodesToGraphMinCost(graph, gData, points);

	// Kanten hinzufügen
	addArcsToGraphMinCost(graph, gData, costs, potRad, points);

	// Kapazitäten hinzufügen
	addCapacitiesToGraphMinCost(capacity, gData);
}



void fastAnchorFlow::addNodesToGraphMinCost(Graph& graph, GraphData& gData, vector<ColoredPoint>* points){

    // Anzahl aller Punkte
    int n = (int) points->size();

    // Rote Knoten hinzufügen (Krit Feature = 0)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == RED){
            gData.redNodes.push_back(graph.addNode());
        }
    }

    // Blaue Knoten hinzufügen (Krit Feature = 1)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == BLUE){
            gData.blueNodes.push_back(graph.addNode());
        }
    }

    // Quelle und Senke hinzufügen
    gData.s = graph.addNode();
    gData.t = graph.addNode();

    return; 
}



void fastAnchorFlow::addArcsToGraphMinCost(Graph& graph, GraphData& gData, CostMap& costs, double potRad, vector<ColoredPoint>* points){
    // Anzahl an Knoten herausfinden
    int nRed = (int) gData.redNodes.size();
    int nBlue = (int) gData.blueNodes.size();

    // Kanten von s zu allen Roten Knoten
    for (int i = 0; i < nRed; i++){
        gData.sourceArcs.push_back(graph.addArc(gData.s, gData.redNodes.at(i)));
    }

    // Kanten von Blau zu t
    for (int i = 0; i < nBlue; i++){
        gData.targetArcs.push_back(graph.addArc(gData.blueNodes.at(i), gData.t));
    }

    // Kanten von Rot nach Blau, abhänging von ihrem Abstand (potRad)
    // Punkte in Farben Aufteilen
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = ColoredPoint::getPointsOfColor(points, BLUE);


    // Kurzer Sanity Check
    if (nRed != (int) redPoints->size() || nBlue != (int) bluePoints->size()){
        printf("ERROR: Fehler bei Grapherstellung!\n");
        printf("Anzahl roter Knoten im Graph %d; \t Anzahl roter Punkte %ld\n", nRed, redPoints->size());
        printf("Anzahl blauer Knoten im Graph %d; \t Anzahl blauer Punkte %ld\n", nBlue, bluePoints->size());
    }
    
    // Alle roten Punkte durchgehen
    for (int redIndex = 0; redIndex < nRed; redIndex++){
        // Alle blauen Punkte durchgehen
        for (int blueIndex = 0; blueIndex < nBlue; blueIndex++){
            // Schauen ob das eine Passende Kante ist
            if (gData.anchorDistance[redIndex][blueIndex].distToPartners <= potRad){
                // Kante in Graphen Packen
                Arc arc = graph.addArc(gData.redNodes.at(redIndex), gData.blueNodes.at(blueIndex));

                // Kante ihre Kosten geben
                costs[arc] = redPoints->at(redIndex).distTo(bluePoints->at(blueIndex));

                // Kante Hinzufügen
                gData.mainArcs.push_back(arc);
            } 
        }
    }

    // Gefilterte Punkte wieder frei geben
    delete redPoints;
    delete bluePoints;

    return;
}



void fastAnchorFlow::addCapacitiesToGraphMinCost(CapacityMap& capacityMap, GraphData& gData){
    // Kapazität von Quelle zu allen Roten
    for (size_t i = 0; i < gData.sourceArcs.size(); i++){
        capacityMap[gData.sourceArcs.at(i)] = 1;
    }

    // Kapazität von allen Blauen zur Senke
    for (size_t i = 0; i < gData.targetArcs.size(); i++){
        capacityMap[gData.targetArcs.at(i)] = 1;
    }

    // Zwischenkanten Kapazität
    for (size_t i = 0; i < gData.mainArcs.size(); i++){
        capacityMap[gData.mainArcs.at(i)] = 1;
    }

}



CapScaling* fastAnchorFlow::calculateFlowMinCost(const Graph& graph, const CapacityMap& capacityMap, CostMap& costs, const GraphData& gData){
    // Preflow-Object erstellen
    CapScaling* flow = new CapScaling(graph);

    // Parameter Festlegen
    flow->upperMap(capacityMap).costMap(costs).stSupply(gData.s, gData.t, (int) gData.redNodes.size());

    // Flussalgorithmus ausführen
    flow->run();

    return flow;
}





int fastAnchorFlow::getFlowOfArcMinCost(const CapScaling& flow, const Arc arc){
    int flowValue = flow.flow(arc);
    return flowValue;
}