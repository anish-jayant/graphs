#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include "graph_algo.h"

using namespace std;

vector<vector<Node*>> depth_layers(const undirected_graph& u, Node& n) {
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
		cout << size << endl;
		result.push_back(layer);
		depth++;
	}

	cout << "Depth: " << depth << endl;
	
	return result;
}