#include <iostream>
#include <vector>
#include <unordered_set>

#include "undirected_graph.h"

using namespace std;

//Breadth-first search of a graph beginning at node n
vector<vector<Node*>> bfs(const undirected_graph& u, Node& n);