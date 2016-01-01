/*
 * Relation.h
 *
 *  Created on: Jul 21, 2014
 *      Author: aconstan
 */

#ifndef RELATION_H_
#define RELATION_H_

using namespace std;

#include "Tuple.h"
#include "Scheme.h"

#include <set>
#include <string>
#include <vector>

class Relation
{
private:

	set<Tuple> Tset;
	Scheme atributes;
	string name;
	bool matched;

	Tuple curT;
	set<Tuple> finalT;

public:
	Relation()
	{
		matched = false;
	}
	virtual ~Relation()
	{

	}
//============================================================================
	string getName()
	{
		return name;
	}

	Scheme getScheme()
	{
		return atributes;
	}

	set<Tuple> getTuples()
	{
		return Tset;
	}


	void nameRelation(string str)
	{
		name = str;
	}

	void addScheme(Scheme S)
	{
		atributes = S;
	}

	void addTuple(Tuple t)
	{
		Tset.insert(t);
	}
//============================================================================
	bool check(string predname)
	{
		if(name == predname)
		{
			matched = true;
		}
		else
		{
			matched = false;
		}
		return matched;
	}

	void seeSet()
	{
		cout << "PRINTING SET OF TUPLES" << endl;
		int num = 1;

		for (set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			cout << "\n" << num << " thing in the set\n" << endl;
			num++;
			for (int i = 0; i < (int)(*it).size(); i++)
			{
				cout << i << ":\t" << (*it)[i] << endl;
			}
		}
	}

	void seeFSet()
	{
		cout << "PRINTING SET OF TUPLES" << endl;
		int num = 1;

		for (set<Tuple>::iterator it = finalT.begin(); it != finalT.end(); ++it)
		{
			cout << "\n" << num << " thing in the set\n" << endl;
			num++;
			for (int i = 0; i < (int)(*it).size(); i++)
			{
				cout << i << ":\t" << (*it)[i] << endl;
			}
		}
	}

	void seeEntireRelation()
	{
		cout << "\nNAME =\t" << name << endl;

		cout << endl;
		atributes.print();

		cout << endl;
		seeSet();

	}
//============================================================================
	void select(int pos, string value, bool& empty)
	{
		matched = false;
		set<Tuple> Tset2;
		for (set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			if ((*it)[pos] == value)
			{
				//cout << "Found a Tuple with the value to be found" << endl;
				matched = true;
			}
			else
			{
				//cout << "Found a Tuple whose value does not match" << endl;
				matched = false;
			}

			if (matched == true)
			{
				//cout << "\nMATCHED = TRUE" << endl;
				Tset2.insert(*it);
			}
			else
			{
				//cout << "\nMATCHED = FALSE" << endl;
			}
		}

		Tset = Tset2;
		if (Tset.size() == 0)
		{
			empty = true;
		}
	}

	void select2(int curpos, int prevpos, bool& empty)
	{
		matched = false;
		set<Tuple> Tset2;
		for (set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			if ((*it)[curpos] == (*it)[prevpos])
			{
				//cout << "Found a Tuple with the value to be found" << endl;
				matched = true;
			}
			else
			{
				//cout << "Found a Tuple whose value does not match" << endl;
				matched = false;
			}

			if (matched == true)
			{
				//cout << "\nMATCHED = TRUE" << endl;
				Tset2.insert(*it);
			}
			else
			{
				//cout << "\nMATCHED = FALSE" << endl;
			}
		}

		Tset = Tset2;
		if (Tset.size() == 0)
		{
			empty = true;
		}
	}

	void project(vector<int> indicies, Predicate p, vector<string>& names)
	{
		Tuple nothing;
		int duplicate = -1;
		prepRename(names, p, duplicate);
		string a = ""; //This keeps track of the duplicate
		if(duplicate != -1)
		{
			a = names[duplicate];
		}

		for (set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			for (int i = 0; i < (int)indicies.size(); i++)
			{

				if (i == duplicate)
				{
					curT.push_back(a);
					curT.push_back((*it).at(indicies[i]));
					i++;
					/*
					curT.push_back(a);
					curT.push_back((*it).at(indicies[i]));
					i += 2;
					*/
				}
				else
				{
					curT.push_back(names[i]);
					curT.push_back((*it).at(indicies[i]));
				}
			}
			finalT.insert(curT);
			curT = nothing;
		}

		/*
		for (int i = 0; i < (int)curT.size(); i++)
		{
			cout << curT[i] << endl;
		}
		*/
		/*
		for (int i = 0; i < (int)indicies.size(); i++)
		{
			cout << "INDICI" << i << ":\t" << indicies[i] << endl;
		}
		*/
		//seeSet();
	}

	void prepRename(vector<string>& names, Predicate p, int& duplicate)
	{

		for (int i = 0; i < (int)p.parameters.size(); i++)
		{
			if(p.parameters[i].is_string == false)
			{
				int found = search(names, p.parameters[i].value);
				//cout << p.parameters[i].value << endl;
				if(found == -1)
				{
					names.push_back(p.parameters[i].value);
				}
				else
				{
					duplicate = found;
				}
				//cout << "\nEND\n" << endl;
			}

		}

		//THIS SHOWS THAT LIST OF NAMES IS ONLY THE VARIABLES
		/*
		for (int i = 0; i < (int)names.size(); i++)
		{
			cout << i << ":\t" << names[i] << endl;
		}
		*/
	}

	void rename(vector<string> names)
	{

	}

	int search(vector<string> list, string name)
	{
		for (int i = 0; i < (int)list.size(); i++)
		{
			if (name == list[i])
			{
				return i;
			}
		}
		return -1;
	}

	string pojectToString()
	{
		//seeFSet();
		string str = "";
		for (set<Tuple>::iterator it = finalT.begin(); it != finalT.end(); ++it)
		{
			str += "  ";
			for (int i = 0; i < (int)(*it).size(); i++)
			{

				int n = ((*it).size() - 1);
				if ((i + 2) % 2 == 1)
				{
					if (i != n)
					{
						str += "\'" + (*it)[i] + "\'";
						str += ", ";
					}
					else
					{
						str += "\'" + (*it)[i] + "\'";
						str += "\n";
					}
				}
				else
				{
					str += (*it)[i] + "=";
				}
			}

		}
		return str;
	}


};

#endif /* RELATION_H_ */
