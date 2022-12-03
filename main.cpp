#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include "undirected_graph.h"

using namespace std;

int main () {
	
	try {
		//nodes
		Node a('1'); Node b('2'); Node c('3'); Node d('4');
		
		//enter some duplicate edges
		Edge e1(a, b); Edge e2(b, c); Edge e3(c, a);
		Edge e4(a, c); Edge e5(c, b); Edge e6(a, d);
		
		//push back all verts & edges to vectors
		vector<Node> v;
		vector<Edge> e;
		v.push_back(a); v.push_back(b); v.push_back(c); v.push_back(d);
		
		e.push_back(e1); e.push_back(e2); e.push_back(e3); 
		e.push_back(e4); e.push_back(e5); e.push_back(e6);
		
		//initialize graph using vectors, print edges and vertices
		undirected_graph u(v, e);
		u.v_print(); u.e_print();
	} 
	catch(InvalidEdgeError& e) {
		//catch potentially invalid edges
		cout << e.what() << endl;
	}
	
	return 0;
}