#include <iostream>
#include <vector>
#include <unordered_set>

#include "undirected_graph.h"

using namespace std;

//Breadth-first search of a graph beginning at node n
vector<vector<Node*>> breadth_layers(const undirected_graph& u, Node& n);

//Is a graph bipartate (two-colorable)
bool isBipartate(const undirected_graph& u);
