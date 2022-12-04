#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "graph_algo.h"

using namespace std;

/**
 *	@brief	Generates layers of a graph using a breadth-first search
 *			beginning from a given vertex via adjacency list provided 
 *			in the class. 
 *			Time Comp. O(|V|+|E|)
 */
vector<vector<Node*>> breadth_layers(const undirected_graph& u, Node& n) {
	vector<vector<Node*>> result;
	const vector<Node*> v = u.getVertices();
	unordered_set<Node*> unexplored; 
	for (int i = 0; i < v.size(); i++) {
		unexplored.insert(v[i]);
	}
	queue<Node*> q;
	q.push(&n);			
	unexplored.erase(unexplored.find(&n));
	int depth = 0;
	while (!q.empty())
	{
		int size = q.size();
		vector<Node*> layer;
		for (int i = 0; i < size; i++) {
			Node* temp = q.front(); q.pop(); 
			layer.push_back(temp);
			vector<Node*> adjacent = temp->adj;
			auto it = adjacent.begin();
			while (it != adjacent.end())
			{
				if (unexplored.find(*it) != unexplored.end())
				{
					q.push(*it);
					unexplored.erase(unexplored.find(*it));
				}
				it++;
			}
		}
		//cout << size << endl;
		result.push_back(layer);
		depth++;
	}

	//cout << "Depth: " << depth << endl;
	unexplored.clear();
	return result;
}

/**
 *	@brief	Returns a boolean, True if u is bipartate, false otherwise
 *			checks by assigning colors according to BFS layering, complexity follows
 *			Time Comp. O(|V|+|E|)
 */
bool isBipartite(const undirected_graph& u)
{
	//Use the bfs layering to assign colorings
	vector<Node*> v = u.getVertices();
	vector<vector<Node*>> layers = breadth_layers(u, *(v[0]));
	unordered_map<char, int> col;
	int color = 0;
	for (int i = 0; i < layers.size(); i++)
	{
		for (int j = 0; j < layers[i].size(); j++)
		{
			col.insert({layers[i][j]->val, color});
		}
		color = 1-color;
	}
	
	//re-run bfs and make sure that there are no same-color connections
	unordered_set<Node*> unexplored; 
	for (int i = 0; i < v.size(); i++) {
		unexplored.insert(v[i]);
	}
	queue<Node*> q;
	q.push(v[0]);			
	unexplored.erase(unexplored.find(v[0]));
	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0; i < size; i++) {
			Node* temp = q.front(); q.pop(); 
			vector<Node*> adjacent = temp->adj;
			auto it = adjacent.begin();
			while (it != adjacent.end())
			{
				if (col[(*it)->val] == col[temp->val])
				{
					unexplored.clear();
					return false;
				}
				if (unexplored.find(*it) != unexplored.end())
				{
					q.push(*it);
					unexplored.erase(unexplored.find(*it));
				}
				it++;
			}
		}
	}
	unexplored.clear();
	return true;
}
/**
 *	@brief	Finds and returns all disjoint subgraphs. Any pair of disjoint 
 *			subgraphs shares no vertices or edges, and together, the subgraphs
 *			recompose the original graph. 
 */
vector<undirected_graph> disjoints(const undirected_graph& u) {
	//initialize and populate variables
	vector<undirected_graph> result;
	vector<Node*> v = u.getVertices();
	unordered_set<Node*> unexplored; 
	for (int i = 0; i < v.size(); i++) {
		unexplored.insert(v[i]);
	}
	
	//repeatedly run bfs while there are still vertices unexplored
	while (unexplored.size() > 0) {
		vector<Node*> curv;
		vector<Edge> cure;
		Node* start = *(unexplored.begin());
		queue<Node*> q;
		q.push(start);
		unexplored.erase(unexplored.find(start));
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; i++)
			{
				Node* temp = q.front(); q.pop();
				vector<Node*> adj = temp->adj;
				auto it = adj.begin();
				while (it != adj.end())
				{
					if (unexplored.find(*it) != unexplored.end())
					{
						q.push(*it);
						unexplored.erase(unexplored.find(*it));
					}
					curv.push_back(*it);
					cure.push_back(Edge(temp, *it));
					it++;
				}
				
			}
		}
		undirected_graph u(curv, cure);
		//cout << u.getEdges().size() << endl;
		result.push_back(u);
	}
	return result;
}