// Copied and edited from https://gist.github.com/huanyud/45f98d8bf8d6df66d3e7ab3e9a85af90

#include "Lemon-Libary/lemon-1.3.1-build/lgf_writer.h"
#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"


#include "Lemon-Libary/lemon-1.3.1-build//preflow.h"

using namespace lemon;
typedef ListDigraph Graph;
typedef int LimitValueType;
typedef Graph::Node Node;
typedef Graph::Arc Arc;
//typedef ListDigraph::ArcMap CapacityMap;




void flowPreflow()
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

	std::cout << "maximum flow by preflow: " << preflow.flowValue() << std::endl;

	// print graph details
	digraphWriter(g).                 			 // write g to the standard output
			arcMap("cap", capacity).        	 // write 'cost' for for arcs
			arcMap("flow", preflow.flowMap()).   // write 'flow' for for arcs
			node("source", s).            		 // write s to 'source'
			node("target", t).            		 // write t to 'target'
			run();

}

int main(){
    flowPreflow();
    return 0;
}