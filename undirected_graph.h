#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stdexcept>

using namespace std;

//Runtime established invalid edge error - designed to check for duplicate edges
struct InvalidEdgeError : public std::runtime_error {
	
	InvalidEdgeError(const char* what) : std::runtime_error(what) {}
};

//Node struct, basis for all vertices of the graph
struct Node {
	char val;
	vector<Node*> adj;
	Node() : val(0) {}
	Node(char v) : val(v) {}
	bool operator==(const Node& n) const {
		return (this->val == n.val);
	}
	int degree() const {
		return adj.size();
	}
};

//Edge struct, basis for all edges of the graph
struct Edge {
	int weight; 
	Node* ends[2];
	Edge() : weight(0) {}
	Edge(Node& a, Node& b);
	Edge(Node& a, Node& b, int w);
	bool operator==(const Edge& e) const 
	{
		return (e.ends[0]->val == this->ends[0]->val && e.ends[1]->val == this->ends[1]->val) ||
				(e.ends[0]->val == this->ends[1]->val && e.ends[1]->val == this->ends[0]->val);
	}
	bool getWeight() { return weight; }
};

//Undirected graph class, contains all member variables & methods
class undirected_graph {
	
	private:
		vector<Node*> Vertices;
		vector<Edge> Edges;
		void v_check();
		void e_check();
	
	public: 
		undirected_graph() {}
		
		undirected_graph(vector<Node*>& v) { 
			Vertices = v;
			v_check();
		}
		
		undirected_graph(vector<Edge>& e) { 
			Edges = e;
			e_check();
		}
		
		undirected_graph(vector<Node*>& v, vector<Edge>& e) {
			Vertices = v;
			v_check();
			Edges = e;
			e_check();
		}
		
		void push_vertex(Node& n) { 
			Vertices.push_back(&n); 
			v_check();
		}
		
		void push_edge(Edge& e) { 
			Edges.push_back(e); 
			e_check();
		}
		
		vector<Node*> getVertices() const { return Vertices; }
		vector<Edge> getEdges() const { return Edges; }
		void v_print();
		void e_print();
		friend ostream& operator<<(ostream& o, const undirected_graph& u);
		bool isUnweighted();
	
};

//Custom hash function for a <char, char> array
struct customEdgeHash
{
  size_t operator()(const pair<char, char> &x) const
  {
    return x.first ^ x.second;
  }
};
