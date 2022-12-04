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
		Edge ed[13] = {Edge(&n[0], &n[1], 7), Edge(&n[0], &n[2], 1), Edge(&n[1], &n[2], 2), 
						Edge(&n[2], &n[3], 1), Edge(&n[1], &n[3], 11), Edge(&n[2], &n[4], 9),
						Edge(&n[3], &n[4], 5), Edge(&n[4], &n[5], 8), Edge(&n[4], &n[6], 10), 
						Edge(&n[3], &n[7], 6), Edge(&n[5], &n[7], 6), Edge(&n[6], &n[7], 4), Edge(&n[5], &n[6], 3)};
		
		//push back all verts & edges to vectors
		cout << "----------------------------GRAPH 1----------------------------" << endl;
		cout << endl;
		vector<Node*> v;
		vector<Edge> e;
		for (int j = 0; j < 13; j++)
		{
			e.push_back(ed[j]);
			if (j < 8) 
			{
				v.push_back(&n[j]);
			}
		}

		//initialize graph using vectors, print edges and vertices
		undirected_graph u(v, e);
		cout << u;
		cout << "Is bipartite?: " << boolalpha << isBipartite(u) << endl;
		vector<undirected_graph> subgraphs = disjoints(u);
		cout << "Number of disjoint subgraphs: " << subgraphs.size() << endl;
		cout << endl;
		
		cout << "----------------------------GRAPH 2----------------------------" << endl;
		
		cout << endl;
		vector<Node*> v2;
		vector<Edge> e2;
		Node n2[4] = {'a', 'b', 'c', 'd'};
		Edge ed2[3] = {Edge(&n2[0], &n2[1]), Edge(&n2[2], &n2[3]), Edge(&n2[3], &n2[2])};
		for(int i = 0; i < 4; i++)
		{
			v2.push_back(&(n2[i]));
			if (i < 3)
			{
				e2.push_back(ed2[i]);
			}
		}
		undirected_graph u2(v2, e2);
		cout << u2;
		cout << "Is bipartite?: " << boolalpha << isBipartite(u2) << endl;
		vector<undirected_graph> subgraphs2 = disjoints(u2);
		cout << "Number of disjoint subgraphs: " << subgraphs2.size();
	} 
	catch(InvalidEdgeError& e) {
		//catch potentially invalid edges
		cout << e.what() << endl;
	}
	

	
	return 0;
}
