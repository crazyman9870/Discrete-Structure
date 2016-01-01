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

	int getSchemeSize()
	{
		return atributes.getSize();
	}

	vector<string> getSchemeVec()
	{
		return atributes.getAtributes();
	}

	set<Tuple> getTuples()
	{
		return Tset;
	}

	int getSetSize()
	{
		return Tset.size();
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

	void changeSet(set<Tuple> t)
	{
		Tset = t;
	}

	void addToSet(set<Tuple> t)
	{
		for(set<Tuple>::iterator it = t.begin(); it != t.end(); ++it)
		{
			Tset.insert((*it));
		}
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

	void seeScheme()
	{
		atributes.print();
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
	void join(const vector<Predicate>& list, string rname2)
	{

	}

	vector<string> findMatchedValues(vector<int> pos)
	{
		vector<string> list;

		for(set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			for(int i = 0; i < (int)pos.size(); i++)
			{
				int temp = (i + 2);
				if (temp % 2 == 0)
				{
					list.push_back((*it)[pos[i]]);
				}
			}
		}

		return list;
	}
	void comparison(vector<int> pos, vector<string> values, bool& joinable, Relation& r1)
	{


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

		//seeSet();

		for (set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			Tuple t = (*it);
			//cout << "\nLOOP1\n";
			//cout << "\nHERE14\n" << endl;
			//cout << "\nPREV\t" << prevpos << "\tCURPOS\t" << curpos << "\n" << endl;
			//cout << "\n" << (*it).size() << endl;

			if (t[curpos] == t[prevpos])
			{
				//cout << "\nIF1\n";
				//cout << "Found a Tuple with the value to be found" << endl;
				matched = true;
			}
			else
			{
				//cout << "\nELSE1\n";
				//cout << "Found a Tuple whose value does not match" << endl;
				matched = false;
			}
			//cout << "\nHERE15\n" << endl;
			if (matched == true)
			{
				//cout << "\nIF2\n";
				//cout << "\nMATCHED = TRUE" << endl;
				Tset2.insert(t);
				//cout << "\nHERE16\n" << endl;
			}
			else
			{
				//cout << "\nELSE2\n";
				//cout << "\nMATCHED = FALSE" << endl;
			}
		}

		Tset = Tset2;
		if (Tset.size() == 0)
		{
			empty = true;
		}
	}

	void select3(int curpos, int prevpos, bool& empty)
	{
		matched = false;
		set<Tuple> Tset2;

		//seeSet();

		for (set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			Tuple t = (*it);
			//cout << "\nLOOP1\n";
			//cout << "\nHERE14\n" << endl;
			//cout << "\nPREV\t" << prevpos << "\tCURPOS\t" << curpos << "\n" << endl;
			//cout << "\n" << t.size() << endl;
			if ((int)t.size() >= curpos+1)
			{
				if (t[curpos] == t[prevpos])
				{
					//cout << "\nIF1\n";
					//cout << "Found a Tuple with the value to be found" << endl;
					matched = true;
				}
				else
				{
					//cout << "\nELSE1\n";
					//cout << "Found a Tuple whose value does not match" << endl;
					matched = false;
				}
				//cout << "\nHERE15\n" << endl;
				if (matched == true)
				{
					//cout << "\nIF2\n";
					//cout << "\nMATCHED = TRUE" << endl;
					Tset2.insert(t);
					//cout << "\nHERE16\n" << endl;
				}
				else
				{
					//cout << "\nELSE2\n";
					//cout << "\nMATCHED = FALSE" << endl;
				}
			}
		}

		Tset = Tset2;
		if (Tset.size() == 0)
		{
			empty = true;
		}
	}



	void project(vector<int> indicies, Predicate& p, vector<string>& names)
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

	void prepRename(vector<string>& names, Predicate& p, int& duplicate)
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

	void project2(vector<int>& indicies)
	{
		Tuple nothing;

		//finalT = Tset;
		//seeFSet();
		//seeEntireRelation();

		for (set<Tuple>::iterator it = Tset.begin(); it != Tset.end(); ++it)
		{
			for (int i = 0; i < (int)indicies.size(); i++)
			{
				Tuple t1 = (*it);
				curT.push_back(t1[indicies[i]]);
			}
			/*
			for(int j = 0; j < (int)curT.size(); j++)
			{
				cout << "\nj" << j << ":\t" << curT[j] << endl;
			}
			*/
			finalT.insert(curT);
			curT = nothing;
		}
		Tset = finalT;
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

	//========================================================================
	Relation join(Relation& r2)
	{


		set<Tuple> new_guy = r2.getTuples();
		vector<int> v1;
		vector<int> v2;

		//seeScheme();
		//r2.seeScheme();
		atributes.fill(r2.getScheme().getAtributes(), v1, v2);


		atributes.createNewScheme(r2.getScheme());
		Relation r3;
		r3.addScheme(atributes);

		/*
		for(int i = 0; i < (int)v1.size(); i++)
		{
			cout << "V1 = " << v1[i] << "\tV2 = " << v2[i] << endl;
		}
		*/

		//seeSet();
		//r2.seeSet();

		join2(r2, v1, v2, r3);

		return r3;
	}

	void join2(Relation& r2, vector<int>& v1, vector<int>& v2, Relation& r3)
	{
		set<Tuple>::iterator it;
		set<Tuple>::iterator it2;

		//for(it = Tset.begin(); it != Tset.end(); ++it)
		for(Tuple tu1:Tset)
		{
			//Tuple tu1 = (*it);
			//for(it2 = r2.getTuples().begin(); it2 != r2.getTuples().end(); ++it2)
			for(Tuple tu2:r2.getTuples())
			{
				//Tuple tu2 = (*it2);
				Tuple tu3;
				bool happy = tu1.joinTuples(tu2, v1, v2, tu3);
				if(happy == true)
				{
					//cout << "ADDED" << endl;
					r3.addTuple(tu3);
				}
				else
				{
					//cout << "NOT ADDED" << endl;
				}
			}
		}
	}




};

#endif /* RELATION_H_ */
