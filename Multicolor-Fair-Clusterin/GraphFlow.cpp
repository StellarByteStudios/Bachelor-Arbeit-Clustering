#include "GraphFlow.h"
#include <chrono>

using namespace std::chrono;

// * * * =========== Building the Graph and let it Flow =========== * * * //
void graphFlow::buildupGraphFromRadius(Graph& graph, GraphData& gData, CapacityMap& capacity, 
                                    double potRad, vector<ColoredPoint>* points, vector<vector<double>>& distMatrix){
    
    //time_point startTime = high_resolution_clock::now();
    // Knoten hinzufügen
	addNodesToGraph(graph, gData, points);

    //time_point timeAfterNodes = high_resolution_clock::now();
    //printf("\tZeit für Nodes anlegen: %ld µSec\n", duration_cast<microseconds>(timeAfterNodes - startTime).count());


	// Kanten hinzufügen
	addArcsToGraph(graph, gData, potRad, points, distMatrix);

    //time_point timeAfterArcs = high_resolution_clock::now();
    //printf("\tZeit für Arcs anlegen: %ld µSec\n", duration_cast<microseconds>(timeAfterArcs - timeAfterNodes).count());

	// Kapazitäten hinzufügen
	addCapacitiesToGraph(capacity, gData);

    //time_point timeAfterCap = high_resolution_clock::now();
    //printf("\tZeit für Capaz anlegen: %ld µSec\n", duration_cast<microseconds>(timeAfterCap - timeAfterArcs).count());

}



void graphFlow::addNodesToGraph(Graph& graph, GraphData& gData, vector<ColoredPoint>* points){

    // Anzahl aller Punkte
    int n = (int) points->size();

    // Rote Knoten hinzufügen (Krit Feature = 0)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == RED){
            gData.redNodes.push_back(graph.addNode());
        }
    }
    //printf("Rote Knoten hinzugefügt\n");

    // Blaue Knoten hinzufügen (Krit Feature = 1)
    for (int i = 0; i < n; i++){
        if (points->at(i).getColor() == BLUE){
            gData.blueNodes.push_back(graph.addNode());
        }
    }
    //printf("Blaue Knoten hinzugefügt\n");

    // Quelle und Senke hinzufügen
    gData.s = graph.addNode();
    gData.t = graph.addNode();
    //printf("Quelle und Senke hinzugefügt\n");

    return; 
}



void graphFlow::addArcsToGraph(Graph& graph, GraphData& gData, double potRad, vector<ColoredPoint>* points, vector<vector<double>>& distMatrix){

    //time_point startTime = high_resolution_clock::now();

    // Anzahl an Knoten herausfinden
    //int n = (int) points->size();
    int nRed = (int) gData.redNodes.size();
    int nBlue = (int) gData.blueNodes.size();

    //time_point timeAfterCount = high_resolution_clock::now();
    //printf("\t\tZeit für Anzahl holen: %ld µSec\n", duration_cast<microseconds>(timeAfterCount - startTime).count());


    // Kanten von s zu allen Roten Knoten
    for (int i = 0; i < nRed; i++){
        gData.sourceArcs.push_back(graph.addArc(gData.s, gData.redNodes.at(i)));
    }

    //time_point timeAfterSource = high_resolution_clock::now();
    //printf("\t\tZeit für Source-Arcs: %ld µSec\n", duration_cast<microseconds>(timeAfterSource - timeAfterCount).count());



    // Kanten von Blau zu t
    for (int i = 0; i < nBlue; i++){
        gData.targetArcs.push_back(graph.addArc(gData.blueNodes.at(i), gData.t));
    }

    //time_point timeAfterTarget = high_resolution_clock::now();
    //printf("\t\tZeit für Target-Arcs: %ld µSec\n", duration_cast<microseconds>(timeAfterTarget - timeAfterSource).count());





    // Kanten von Rot nach Blau, abhänging von ihrem Abstand (potRad)
    // Punkte in Farben Aufteilen
    vector<ColoredPoint>* redPoints = ColoredPoint::getPointsOfColor(points, RED);
	vector<ColoredPoint>* bluePoints = ColoredPoint::getPointsOfColor(points, BLUE);

    //time_point timeAfterFilter = high_resolution_clock::now();
    //printf("\t\tZeit für Colorfilter: %ld µSec\n", duration_cast<microseconds>(timeAfterFilter - timeAfterTarget).count());



    // Kurzer Sanity Check
    if (nRed != (int) redPoints->size() || nBlue != (int) bluePoints->size()){
        printf("ERROR: Fehler bei Grapherstellung!\n");
        printf("Anzahl roter Knoten im Graph %d; \t Anzahl roter Punkte %ld\n", nRed, redPoints->size());
        printf("Anzahl blauer Knoten im Graph %d; \t Anzahl blauer Punkte %ld\n", nBlue, bluePoints->size());
    }
    

    //time_point timeAfterSanaty = high_resolution_clock::now();
    //printf("\t\tZeit für Sanaty-Check: %ld µSec\n", duration_cast<microseconds>(timeAfterSanaty - timeAfterFilter).count());


    //time_point timeAfterTillMain = high_resolution_clock::now();
    //printf("Zeit für bis Main-Arcs: %ld µSec\n", duration_cast<microseconds>(timeAfterTillMain - startTime).count());

    // Alle roten Punkte durchgehen
    for (int redIndex = 0; redIndex < nRed; redIndex++){

        //time_point forTimer = high_resolution_clock::now();

        // Alle blauen Punkte durchgehen
        for (int blueIndex = 0; blueIndex < nBlue; blueIndex++){
            // Schauen ob das eine Passende Kante ist
            // Neue Variante
            if(distMatrix[redIndex][blueIndex] < potRad){
                gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(redIndex), gData.blueNodes.at(blueIndex)));
            }


            /* Alte Variante
            if (redPoints->at(redIndex).distTo(bluePoints->at(blueIndex)) < potRad){
                // Kante Hinzufügen
                gData.mainArcs.push_back(graph.addArc(gData.redNodes.at(redIndex), gData.blueNodes.at(blueIndex)));
            } */
        }

        //time_point afterForTimer = high_resolution_clock::now();
        //printf("Zeit Äußere-Forschleife: %ld µSec\n", duration_cast<microseconds>(afterForTimer - forTimer).count());    
    }
    //time_point timeAfterMainArcs = high_resolution_clock::now();
    //printf("\t\tZeit für nach Main-Arcs: %ld µSec\n", duration_cast<microseconds>(timeAfterMainArcs - timeAfterSanaty).count());
    //printf("\t\t --> Zeit für nach Main-Arcs pro Roter Punkt: %ld µSec\n", 
    //duration_cast<microseconds>(timeAfterMainArcs - timeAfterSanaty).count() / nRed);


    //time_point timeAfterMainArcs = high_resolution_clock::now();
    //printf("Zeit für Main-Nodes: %ld µSec\n", duration_cast<microseconds>(timeAfterMainArcs - timeAfterSanaty).count());


    
    // Gefilterte Punkte wieder frei geben
    delete redPoints;
    delete bluePoints;

    return;
}



void graphFlow::addCapacitiesToGraph(CapacityMap& capacityMap, GraphData& gData){
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



Flow* graphFlow::calculateFlow(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Preflow-Object erstellen
    Flow* preflow = new Flow(graph, capacityMap, gData.s, gData.t);

    // Flussalgorithmus ausführen
    preflow->run();

    return preflow;
}


int graphFlow::getMaxFlow(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
    // Flussalgorithmus laufen lassen
    Flow* flow = calculateFlow(graph, capacityMap, gData);

    // Wert abspeichern
    double flowValue = flow->flowValue();

    // Speicher wieder freigeben
    delete(flow);

    // Wert zurück geben
    return flowValue;
}



int graphFlow::getFlowOfArc(const Flow& flow, const Arc arc){
    int flowValue = flow.flow(arc);
    return flowValue;
}












// ==== Debugging ==== //
void graphFlow::printGraph(const Graph& graph, const GraphData& gData){
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

void graphFlow::printGraphCapacity(const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
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

void graphFlow::printFlow(const Flow& preflow, const Graph& graph, const CapacityMap& capacityMap, const GraphData& gData){
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