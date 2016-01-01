/*
 * Node.h
 *
 *  Created on: Aug 8, 2014
 *      Author: aconstan
 */

#ifndef NODE_H_
#define NODE_H_

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>

class Node
{
private:

	set<string> adj; //This is the same as an adjacency list
	bool marker;
	int postnum; //This is the post order number of the node


public:
	Node()
	{
		marker = false;
		postnum = 0;
	}
	virtual ~Node()
	{

	}
	//========================================================================
	int getPostnum()
	{
		return postnum;
	}
	void changePostnum(int n)
	{
		postnum = n;
	}
	void postnumClear()
	{
		postnum = 0;
	}
	//========================================================================
	bool getMarker()
	{
		return marker;
	}
	void mark()
	{
		marker = true;
	}
	void unmark()
	{
		marker = false;
	}
	//========================================================================
	set<string> getAdj()
	{
		return adj;
	}
	void addToAdj(string s)
	{
		adj.insert(s);
	}
	void adjClear()
	{
		set<string> empty;
		adj = empty;
	}
	int setSize()
	{
		return adj.size();
	}
	void seeSet()
	{
		set<string>::iterator it;
		for(it = adj.begin(); it != adj.end(); ++it)
		{
			cout << " " << (*it);
		}
	}
	void printSet(ofstream& output)
	{
		set<string>::iterator it;
		for(it = adj.begin(); it != adj.end(); ++it)
		{
			output << " "<< (*it);
		}
	}
	//========================================================================

};

#endif /* NODE_H_ */
