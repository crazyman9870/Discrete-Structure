/*
 * Graph.h
 *
 *  Created on: Aug 8, 2014
 *      Author: aconstan
 */

#ifndef GRAPH_H_
#define GRAPH_H_

using namespace std;

#include "Node.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>


class Graph
{
private:
	map<string, Node> graph;
	int PON; //This is the post order number that increments and is assigned to the nodes
	vector<string> edge_list;
	map<string, set<string> > backward_edges;

public:
	Graph()
	{
		PON = 1;
	}
	virtual ~Graph()
	{

	}
	//========================================================================
	vector<string> getEdgeList()
	{
		return edge_list;
	}
	vector<int> getEdgeListPos()
	{
		vector<int> temp;

		for(int i = 0; i < (int)edge_list.size(); i++)
		{
			temp.push_back(str_to_int(edge_list[i]));
		}

		cout << "\nEDGE LIST SIZE = " << edge_list.size() << "\n\n";
		cout << "\nTEMP LIST SIZE = " << temp.size() << "\n\n";
		cout << "\nPrinting temp vector\n\n";
		for(int i = 0; i < (int)temp.size(); i++)
		{
			cout << temp[i] << "\n\n";
		}
		return temp;
	}
	int str_to_int(string s)
	{
		istringstream strm;
		strm.str(s.substr(1));
		int n = 0;
		strm >> n;
		return n;
	}
	void edgeListClear()
	{
		vector<string> empty;
		edge_list = empty;
	}
	//========================================================================
	int getPON()
	{
		return PON;
	}
	void incrementPON()
	{
		PON++;
	}
	void resetPON()
	{
		PON = 1;
	}
	//========================================================================
	map<string, Node> getGraph()
	{
		return graph;
	}
	void addKeyGraph(string key)
	{
		Node empty;
		graph.insert(pair<string,Node>(key,empty));
	}
	void addNodeGraph(string key, Node node)
	{
		graph[key] = node;
	}
	void seeEverything()
	{
		for (map<string,Node>::iterator it = graph.begin(); it != graph.end(); ++it)
		{
			string key = it->first;
			cout << "  " << it->first << ":";
			it->second.seeSet();
			cout << "\n";

			cout << "\npostnum = ";
			cout << it->second.getPostnum();
			cout << "\n";
		}
		cout << "\n";

	}
	void seeGraph()
	{
		for (map<string,Node>::iterator it = graph.begin(); it != graph.end(); ++it)
		{
			string key = it->first;
			cout << "  " << it->first << ":";
			it->second.seeSet();
			cout << "\n";
		}
		cout << "\n";
	}
	void unmarkbool()
	{
		for (map<string, Node>::iterator it = graph.begin(); it != graph.end(); it++)
		{
			it->second.unmark();
		}
	}
	void unmarkpost()
	{
		for (map<string, Node>::iterator it = graph.begin(); it != graph.end(); it++)
		{
			it->second.postnumClear();
		}
	}
	//========================================================================
	void print(ofstream& output)
	{
		output << "Dependency Graph\n";
		for (map<string,Node>::iterator it = graph.begin(); it != graph.end(); ++it)
		{
			string key = it->first;
			output << "  " << it->first << ":";
			it->second.printSet(output);
			output << "\n";
		}
		output << "\n";
	}
	void printPON(ofstream& output)
	{
		output << "  Postorder Numbers\n";
		for (map<string,Node>::iterator it = graph.begin(); it != graph.end(); ++it)
		{
			if(it->second.getPostnum() > 0)
			{
				string key = it->first;
				output << "    " << it->first << ": ";
				output << it->second.getPostnum();
				output << "\n";
			}
		}
		output << "\n";

	}
	void printRuleEvalOrder(ofstream& output)
	{
		output << "  Rule Evaluation Order\n";
		for(int i = 0; i < (int)edge_list.size(); i++)
		{
			output << "    " << edge_list[i] << "\n";
		}
		output << "\n";
	}
	void printBWE(ofstream& output)
	{
		output << "  Backward Edges\n";
		for (map<string,set<string> >::iterator it = backward_edges.begin(); it != backward_edges.end(); ++it)
		{
			if(!it->second.empty())
			{
				output << "    " << it->first << ":";
				set<string>::iterator it2;
				for(it2 = it->second.begin(); it2 != it->second.end(); ++it2)
				{
					output << " " << (*it2);
				}
				output << "\n";
			}
		}
		output << "\n";
	}
	//========================================================================
	void postorderNum(string& key, ofstream& output)
	{
		//cout << "\nSTARTING FROM THE TOP\n\nKEY = " << key << endl;
		dfs(graph[key]);

		/*
		int size = edge_list.size();
		vector<string> temp;
		for(int i = 0; i < size; i++)
		{
			temp.push_back(edge_list[size-(i+1)]);
			edge_list.pop_back();
		}
		edge_list = temp;
		*/

		//edgeListClear();
		//seeEverything();
		printPON(output);
		printRuleEvalOrder(output);
		resetPON();
		unmarkbool();
	}

	void dfs(Node& x)
	{
		x.mark();
		set<string>::iterator it;

		//for(it = x.getAdj().begin(); it != x.getAdj().end(); ++it)
		for(string key:x.getAdj())
		{
			//string key = (*it);
			//cout << "\nKEY = " << key << "\n\n";

			/*
			bool marked = graph[key].getMarker();
			cout << "\nIS IT MARKED ?????\tANSWER = ";
			if (marked == true)
				cout << "TRUE\n\n";
			else
				cout << "FALSE\n\n";
			*/
			if(graph[key].getMarker() == false)
			{

				//cout << "\nNOW DFS ON NODE = " << key << endl;
				dfs(graph[key]);
				edge_list.push_back(key);
			}
		}

		x.changePostnum(PON);
		PON++;
	}

	bool backwardE(string& key, ofstream& output)
	{
		//cout << "\nCHECKING BACKWARDS EDGES\n\nKEY = " << key << endl;
		bool backwards = false;
		for(int i = 0; i < (int)edge_list.size(); i++)
		{
			string check = edge_list[i];
			set<string> empty;
			backward_edges.insert(pair<string, set<string> >(check,empty));
			int pnum1 = graph[check].getPostnum();

			for(string against:graph[check].getAdj())
			{
				int pnum2 = graph[against].getPostnum();
				if(pnum1 <= pnum2)
				{
					backwards = true;
					backward_edges.at(check).insert(against);
				}
			}
		}

		printBWE(output);
		map<string,set<string> > no_map;
		backward_edges = no_map;

		unmarkpost();


		return backwards;

		/*
		isCyclic()

		   run dfsForest()

		   for each edge x->y (for each node and for each adjacent node)
		      if x.postorder <= y.postorder
		         return true
		      end if
		   end for

		   return false

		end isCyclic
		*/
	}

};

#endif /* GRAPH_H_ */
