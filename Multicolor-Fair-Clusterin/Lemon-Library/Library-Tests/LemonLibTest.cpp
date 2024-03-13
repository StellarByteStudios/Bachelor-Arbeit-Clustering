// Complile with g++ -o LibTest LemonLibTest.cpp -lemon
//g++ -Wall -g -o LibTest LemonLibTest.cpp $(LINKLIB)

#include <iostream>
#include <lemon/list_graph.h>
//#include "Lemon-Libary/lemon-1.3.1-build/list_graph.h"
using namespace lemon;
using namespace std;
int main()
{
  ListDigraph g;
  ListDigraph::Node u = g.addNode();
  ListDigraph::Node v = g.addNode();
  ListDigraph::Node x = g.addNode();
  ListDigraph::Arc  a = g.addArc(u, v);
  ListDigraph::Arc  b = g.addArc(u, x);
  ListDigraph::Arc  c = g.addArc(x, v);
  cout << "Hello World! This is LEMON library here." << endl;
  cout << "We have a directed graph with " << countNodes(g) << " nodes "
       << "and " << countArcs(g) << " arc." << endl;
  return 0;
}