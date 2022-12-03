#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include "undirected_graph.h"

using namespace std;

const char* loop_error_msg = "No single-vertex loops in an undirected graph";


/**
 *	@brief	Deletes duplicate vertices, sorted by 
 *			node character type (see operator==) for node class
 *			O(|V|)
*/
void undirected_graph::v_check() {
	unordered_set<char> myset;
	auto it = Vertices.begin();
	while (it != Vertices.end())
	{
		myset.insert((*it)->val);
		it++;
	}

	auto og = myset.size();
	int skip = 0;
	for (int i = 0; i < Vertices.size(); i++)
	{
		auto it = myset.find(Vertices[i]->val);
		if (it != myset.end())
		{
			myset.erase(it);
			Vertices[i-skip] = Vertices[i];
			if (myset.size() == 0) break;
			
		}
		else
		{
			skip++;
		}
	}
	Vertices.resize(og);
	
}

/**
 *	@brief	Deletes duplicate edges, assumes undirected property
 *			Remember that, in an undirected graph, a->b is equiv. to b->a
 *			(see operator== edges struct)
 *			Time Comp. O(|E|), Space Comp. O(|E|)
*/
void undirected_graph::e_check() {
	unordered_set<pair<char, char>, customEdgeHash> myset;
	auto it = Edges.begin();
	while (it != Edges.end())
	{
		if (myset.find(make_pair(it->ends[0]->val, it->ends[1]->val)) == myset.end() 
			&& myset.find(make_pair(it->ends[1]->val, it->ends[0]->val)) == myset.end())
		{
			myset.insert(make_pair(it->ends[0]->val, it->ends[1]->val));
		}
		it++;
	}

	auto og = myset.size();
	int skip = 0;
	for (int i = 0; i < Edges.size(); i++)
	{
		Node* a = Edges[i].ends[0];
		Node* b = Edges[i].ends[1];
		auto ait = myset.find(make_pair(a->val, b->val));
		if (ait != myset.end())
		{
			//cout << a << ", " << a->val << endl;
			(a->adj).push_back(b);
			(b->adj).push_back(a);
			//cout << a->degree() << endl;
			myset.erase(ait);
			Edges[i-skip] = Edges[i];
			if (myset.size() == 0) break;
			
		}
		else
		{
			skip++;
		}
	}
	Edges.resize(og);
	
}

/**
 *	@brief	Print all of the vertices present in the graph, deletes duplicates
 *			prior.
 *			Time Comp. O(|V|), Space Comp. O(|V|) 
*/
void undirected_graph::v_print() {
	auto it = Vertices.begin();
	cout << "(Node, Degree) list: ";
	while (it != Vertices.end())
	{
		cout << '(' << (*it)->val << ", " << (*it)->degree() << ")";
		it++;
	}
	cout << endl;
	
	
}

/**
 *	@brief	Print all of the edges present in the graph, deletes duplicates
 *			prior.
 *			Time Comp. O(|E|), Space Comp. O(|E|) 
*/
void undirected_graph::e_print() {
	auto it = Edges.begin();
	cout << "Edges list: ";
	while (it != Edges.end())
	{
		cout << "(" << ((*it).ends[0])->val << "<=>" << ((*it).ends[1])->val << ")";
		it++;
	}
	cout << endl;
}

/**
 *	@brief	Checks if the graph is unwieghted & undirected
 *			by checking that every substituent edge has weight 0
 *			O(|E|)
 */
bool undirected_graph::isUnweighted() {
	auto it = Edges.begin();
	while (it != Edges.end())
	{
		if (it->weight != 0)
		{
			return false;
		}
	}
	return true;
	
	
}

/**
 *	@brief	Constructor for Edge class, has safeguards to check that
 *			user has not mistakenly entered a single-vertex loop_error_msg
 *			but assumes that both a and b are in Vertices
 *			O(1)
 */
Edge::Edge(Node& a, Node& b) {
	if (a.val == b.val) {
		throw InvalidEdgeError(loop_error_msg);
	}
	ends[0] = &a;
	ends[1] = &b;
	weight = 0;
}

/**
 *	@brief	Identical to past constructor, accepts weight value_comp
 *			O(1)
 */
Edge::Edge(Node& a, Node& b, int w) {
	if (a.val == b.val) {
		throw InvalidEdgeError(loop_error_msg);
	}
	ends[0] = &a;
	ends[1] = &b;
	weight = w;
}
