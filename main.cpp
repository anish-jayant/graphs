#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

//include other headers as needed
//#include "undirected_graph.h"
#include "graph_algo.h"

using namespace std;

int main () {
	
	try {
		//nodes
		Node n[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
		
		//enter some duplicate edges
		Edge ed[13] = {Edge(n[0], n[1], 7), Edge(n[0], n[2], 1), Edge(n[1], n[2], 2), 
						Edge(n[2], n[3], 1), Edge(n[1], n[3], 11), Edge(n[2], n[4], 9),
						Edge(n[3], n[4], 5), Edge(n[4], n[5], 8), Edge(n[4], n[6], 10), 
						Edge(n[3], n[7], 6), Edge(n[5], n[7], 6), Edge(n[6], n[7], 4), Edge(n[5], n[6], 3)};
		
		//push back all verts & edges to vectors
		vector<Node*> v;
		vector<Edge> e;
		for (int i = 0; i < 8; i++)
		{
			v.push_back(&(n[i]));
		}
		for (int j = 0; j < 13; j++)
		{
			e.push_back(ed[j]);
		}

		//initialize graph using vectors, print edges and vertices
		undirected_graph u(v, e);
		//u.v_print(); u.e_print();
		breadth_layers(u, n[0]);
	} 
	catch(InvalidEdgeError& e) {
		//catch potentially invalid edges
		cout << e.what() << endl;
	}
	

	
	return 0;
}
