/*
 * Interpreter.h
 *
 *  Created on: Jul 21, 2014
 *      Author: aconstan
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

using namespace std;

#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Predicate.h"
#include "Rule.h"
#include "Graph.h"
#include "Node.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

class Interpreter
{
private:

	Tuple curT;
	Scheme curS;
	Relation curR;
	Database data;

	int nschemes;
	int nfacts;
	int nrules;
	int nqueries;

	int check;

	map<string, set<string> > Hmap;
	Graph graph;
	map<string, Node> Nmap;


public:
	Interpreter()
	{
		nschemes = 0;
		nfacts = 0;
		nrules = 0;
		nqueries = 0;
		check = 0;
	}
	virtual ~Interpreter()
	{

	}
	//========================================================================
	Database mainFxn(DatalogProgram& prog, ofstream& output)
	{
		nschemes = prog.getSizeS(); //gets the number of predicates in the Schemes
		nfacts = prog.getSizeF(); //gets the number of predicates in the Facts
		nrules = prog.getSizeR(); //gets the number of rule objects in Rules
		nqueries = prog.getSizeQ(); //gets the number of predicates in the Queries

		vector<Predicate> Queries = prog.getQueries();
		vector<Rule> Rules = prog.getRules();

		data.dataFxn(prog);

		//data.seeMap();
		//SHOWS THAT THE DATABASE WAS CORRECTLY UPDATED

		createHmap(Rules);

		//cout << "\nPRINTING HMAP\n\n";
		//seeHmap();

		createGraphQ(Queries);
		createGraphR(Rules);

		cout << "\nDependency Graph\n";

		//graph.seeGraph();
		graph.print(output);


		for(int i = 0; i < (int)Queries.size(); i++)
		{
			output << Queries[i].toString() + "?\n\n";
			string access = "Q" + int_to_string(i+1);
			cout << "\nACCESS POINT = " << access << "\n\n";

			graph.postorderNum(access, output);
			bool backwards_edge = graph.backwardE(access, output);

			//cout << "\nDONE WITH BACKWARDS\n\nBOOL = ";

			int converged = 0;
			vector<int> rule_eval_order = graph.getEdgeListPos();
			cout << "\nRULE EVAL ORDER = " << rule_eval_order.size() << "\n" << endl;

			vector<Rule> new_rule_list;
			for(int j = 0; j < (int)rule_eval_order.size(); j++)
			{
				cout << "RULE EVAL NUMBER I -1\t" << rule_eval_order[j]-1 << "\n" << endl;
				new_rule_list.push_back(Rules[rule_eval_order[j]-1]);
			}

			printRuleVec(new_rule_list);

			if(backwards_edge == true)
			{
				cout << "TRUE\n\n";
				bool changed = true;
				check = 0;
				//int counter = 0;




				while (changed == true)
				{
					//cout << "\nBEGIN\n" << endl;
					int temp = check;
					for(int j = 0; j < (int)new_rule_list.size(); j++)
					{
						cout << "\nCHECK = " << check << "\n\n";
						cout << "\nJ = " << j << "\n" << endl;
						cout << "\nRules.size = " << Rules.size() << "\n" << endl;
						data.beginTestingR(new_rule_list[j], check);
					}
					//cout << "\nEND\n" << endl;

					if(check == temp)
					{
						changed = false;
					}



					converged++;
					//data.seeMap();
				}


			}
			else
			{
				cout << "FALSE\n\n";

				cout << "\nRULE EVAL ORDER = " << rule_eval_order.size() << "\n" << endl;
				for(int j = 0; j < (int)new_rule_list.size(); j++)
				{
					data.beginTestingR(new_rule_list[j], check);
				}
				converged++;

				//data.seeMap();


			}

			graph.edgeListClear();
			cout << "\nCONVERGED AFTER EVALUATING RULES = " << converged << "\n\n";
			output << "  Rule Evaluation\n";
			printRules(output, converged, Rules, rule_eval_order);
			cout << "\nHERE\n\n";

			data.beginTestingQ(Queries[i]);
			data.printOutput(output);
			data.resetFinalString();
			data.seeMap();

		}

		/*
		bool changed = true;
		int counter = 0;

		int converged = 0;
		while (changed == true)
		{
			//cout << "\nBEGIN\n" << endl;
			int temp = check;
			for(int i = 0; i < (int)Rules.size(); i++)
			{
				data.beginTestingR(Rules[i], check);
			}
			//cout << "\nEND\n" << endl;

			if(check == temp)
			{
				changed = false;
			}



			converged++;
		}
		//tests the rules

		counter = 0;
		while (counter < nqueries)
		{
			data.beginTestingQ(Queries[counter]);
			counter++;
		}
		//tests the queries

		output << "Converged after " << converged << " passes through the Rules." << endl;


		data.printToString();
		data.printOutput(output);
		*/

		return data;
	}
	//========================================================================
	void createHmap(vector<Rule>& Rules)
	{
		for(int i = 0; i < (int)nrules; i++)
		{
			string key = Rules[i].head.name;
			addKeyHmap(key);

			string value = "R" + int_to_string(i+1);
			addValueHmap(key,value);
		}
	}

	void createGraphQ(vector<Predicate>& Queries)
	{
		for(int i = 0; i < (int)nqueries; i++)
		{
			string key = "Q" + int_to_string(i+1);
			graph.addKeyGraph(key);

			string access = Queries[i].name;
			Node node;
			if(Hmap.count(access) > 0)
			{
				set<string>::iterator it;
				for(it = Hmap.at(access).begin(); it != Hmap.at(access).end(); ++it)
				{
					string str = (*it);
					node.addToAdj(str);
				}
			}
			graph.addNodeGraph(key, node);
			//set<string> nset = Hmap.at(access);
		}
	}

	void createGraphR(vector<Rule>& Rules)
	{
		for(int i = 0; i < (int)nrules; i++)
		{
			string key = "R" + int_to_string(i+1);
			graph.addKeyGraph(key);
			Node node;
			for(int j = 0; j < (int)Rules[i].tail.size(); j++)
			{
				string access = Rules[i].tail[j].name;

				if(Hmap.count(access) > 0)
				{
					set<string>::iterator it;
					for(it = Hmap.at(access).begin(); it != Hmap.at(access).end(); ++it)
					{
						string str = (*it);
						node.addToAdj(str);
					}

				}
			}
			graph.addNodeGraph(key, node);
		}
	}

	void createNodeR(Node& node, vector<Rule>& Rules, string& access)
	{

	}
	//========================================================================
	void addKeyHmap(string key)
	{
		set<string> empty;
		Hmap.insert(pair<string,set<string> >(key,empty));
	}

	void addValueHmap(string key, string str)
	{
		Hmap.at(key).insert(str);
	}

	void seeHmap()
	{
		for (map<string,set<string> >::iterator it = Hmap.begin(); it != Hmap.end(); ++it)
		{
			string key = it->first;
			cout << "FIRST = " << it->first << "\n======================\nSECOND" << endl;
			for(set<string>::iterator it2 = Hmap.at(key).begin(); it2 != Hmap.at(key).end(); ++it2)
			{
				cout << (*it2) << endl;
			}
			cout << "\n======================\n" << endl;
		}

	}

	string int_to_string(int n)
	{
		stringstream ss;
		ss << n;
		string str = ss.str();
		return str;
	}
	//========================================================================
	void printRules(ofstream& output, int& converged, vector<Rule>& Rules, vector<int>& rule_eval_order)
	{
		if ((int)rule_eval_order.size() > 0)
		{
			for(int k = 0; k < converged; k++)
			{
				for(int i = 0; i < (int)rule_eval_order.size(); i++)
				{
					output << "    " << Rules[rule_eval_order[i]-1].toString() << "\n";
				}

			}
		}
		output << "\n";
	}
	void evalRules(vector<int>& rule_eval_order, vector<Rule>& Rules)
	{
		if((int)rule_eval_order.size() > 0)
		{
			if((int)Rules.size() == (int)rule_eval_order.size())
			{
				for(int i = 0; i < (int)rule_eval_order.size(); i++)
				{
					data.beginTestingR(Rules[rule_eval_order[i]-1], check);
				}
			}
			else
			{
				for(int i = 0; i < (int)Rules.size(); i++)
				{
					data.beginTestingR(Rules[i], check);
				}
			}

		}
	}
	//========================================================================
	void printRuleVec(vector<Rule> list)
	{
		for (int i = 0; i < (int)list.size(); i++)
		{
			cout << (i+1) << ":Head\t" << list[i].head.name << endl;
				for (int k = 0; k < (int)list[i].head.parameters.size(); k++)
				{
					cout << "\t" << (k+1) << ":\t" << list[i].head.parameters[k].value;
					cout << endl;
				}
			for (int j = 0; j < (int)list[i].tail.size(); j++)
			{
				cout << "\t\t" << (j+1) << ":\t" << list[i].tail[j].name << endl;
				for (int k = 0; k < (int)list[i].tail[j].parameters.size(); k++)
				{
					cout << "\t\t\t" << (k+1) << ":\t" << list[i].tail[j].parameters[k].value << endl;
				}
			}
		}
	}
};

#endif /* INTERPRETER_H_ */
