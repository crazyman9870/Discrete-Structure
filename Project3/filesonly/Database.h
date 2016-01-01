/*
 * Database.h
 *
 *  Created on: Jul 21, 2014
 *      Author: aconstan
 */

#ifndef DATABASE_H_
#define DATABASE_H_

using namespace std;

#include "DatalogProgram.h"
#include "Relation.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Predicate.h"
#include "Rule.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

class Database
{
private:

	map<string, Relation> Rmap;

	int nschemes;
	int nfacts;
	int nqueries;

	Tuple curT;
	Scheme curS;
	Relation curR;

	string final_output;

public:
	Database()
	{
		nschemes = 0;
		nfacts = 0;
		nqueries = 0;
		final_output = "";
	}
	virtual ~Database()
	{

	}
	//========================================================================
	void addRelation(string key, Relation R)
	{
		Rmap.insert(pair<string,Relation>(key, R));
	}

	map<string, Relation> getMap()
		{
			return Rmap;
		}

	void printToString()
	{
		cout << final_output;
	}

	void printOutput(ostream& output)
	{
		output << final_output;
	}
	//========================================================================
	map<string, Relation> dataFxn(DatalogProgram prog)
	{
		nschemes = prog.getSizeS(); //gets the number of predicates in the Schemes
		nfacts = prog.getSizeF(); //gets the number of predicates in the Facts
		nqueries = prog.getSizeQ(); //gets the number of predicates in the Queries

		createRelations(nschemes, prog);



		return Rmap;
	}

	void createRelations(int num, DatalogProgram prog)
	{
		int counter = 0;
		while (counter < nschemes)
		{
			handleRelations(prog, counter);
			counter++;
		}
	}

	void handleRelations(DatalogProgram prog, int n)
	{
		Predicate p = prog.accPredS(n);
		string curname = p.name;

		curR.nameRelation(curname);

		handleScheme(prog, p);

		curR.addScheme(curS);
		curS.clear();

		handleTuples(prog);

		//curR.seeSet();
		//THIS IS TO SEE WHAT THE CURRENT SET OF TUPLES IS IN curR
		//curR.seeEntireRelation();
		//PRINTS OUT EVERYTHING IN THE RELATION (UPDATES CORRECTLY)

		addRelation(curR.getName(), curR);

		clearRelation();

	}

	void handleScheme(DatalogProgram prog, Predicate pred)
	{
		for(int i = 0; i < (int)pred.parameters.size(); i++)
		{
			curS.addAtribute(pred.parameters[i].value);
		}

		//curS.print();
	}

	void handleTuples(DatalogProgram prog)
	{
		bool match = false;
		for(int i = 0; i < nfacts; i++)
		{
			//cout << "i = " << i << endl;
			Predicate p = prog.accPredF(i);
			match = curR.check(p.name);
			//cout << "TRUE OR FALSE" << endl;

			if (match == true)
			{
				//cout << "true" << endl;
				createTuple(prog, p);
				curR.addTuple(curT);
				clearTuple();
				//cout << "\nCLEARED" << endl;
			}
			else
			{
				//cout << "false" << endl;
			}
		}
		//cout << "\nDONE WITH RELATION\n\n" << endl;
	}

	void createTuple(DatalogProgram prog, Predicate p)
	{
		int psize = p.parameters.size();
		for (int i = 0; i < psize; i++)
		{
			curT.push_back(p.parameters[i].value);
		}

		/*
		for (int i = 0; i < (int)curT.size(); i++)
		{
			cout << i << ":\t" << curT[i] << endl;
		}
		*/
	}

	void clearTuple()
	{
		int tsize = curT.size();
		for (int i = 0; i < tsize; i++)
		{
			curT.pop_back();
		}
	}

	void clearRelation()
	{
		Relation R;
		curR = R;
	}
//============================================================================
	void seeMap()
	{
		for (std::map<string,Relation>::iterator it = Rmap.begin(); it != Rmap.end(); ++it)
		    {
				cout << it->first << endl;
				Relation R = it->second;
				R.seeEntireRelation();

		    }
	}
//============================================================================
	void beginTestingQ(Predicate p)
	{
		string pname = p.name;
		bool empty = false;

		curR = Rmap.at(pname);
		//cout << "curR before modification" << endl;
		//curR.seeEntireRelation();

		handleSelect(p, empty);

		//cout << "\n\ncurR after the modification" << endl;
		//curR.seeEntireRelation();
		/*
		if (empty == true)
		{
			cout << "TRUE" << endl;
		}
		else
		{
			cout << "FALSE" << endl;
		}
		*/

		final_output = newRelation(final_output, p, empty);

		handleProject(p);

		final_output = relationProject(final_output, empty);

		//final_output = relationProject(final_output, )
	}

	void handleSelect(Predicate p, bool& empty)
	{
		for (int i = 0; i < (int)p.parameters.size(); i++)
		{
			if (p.parameters[i].is_string == true)
			{
				curR.select(i, p.parameters[i].value, empty);
			}
			else
			{
				int dcolumn;
				for (int j = 0; j < i; j++)
				{
					dcolumn = checkdup(p, i , j);
					if (dcolumn != -1)
					{
						curR.select2(i, j, empty);
					}
				}
			}
		}
	}

	int checkdup(Predicate p, int curpos, int prevpos)
	{
		if (p.parameters[curpos].value == p.parameters[prevpos].value)
		{
			return prevpos;
		}
		return -1;
	}

	void handleProject(Predicate p)
	{
		vector<int> indicies;
		vector<string> names;
		for (int i = 0; i < (int)p.parameters.size(); i++)
		{
			if (p.parameters[i].is_string == false)
			{
				indicies.push_back(i);
			}
		}

		if (indicies.size() > 0)
		{
			curR.project(indicies, p, names);
		}
	}

	void handleRename(Predicate p)
	{

	}

	string int_to_string(int n)
	{
		ostringstream strm;
		strm << n;
		return strm.str();
	}
	//========================================================================
	string newRelation(string final, Predicate p, bool empty)
	{
		string str = p.toString() + "?";

		set<Tuple> T = curR.getTuples();

		if(empty == true || T.size() == 0)
		{
			str += " No\n";
		}
		else
		{
			str += " Yes(" + int_to_string(T.size()) + ")\n";
		}

		final += str;
		return final;
	}

	string relationProject(string final, bool empty)
	{
		string str = "";

		if(empty == true)
		{
			return final;
		}

		str = curR.pojectToString();
		final += str;
		return final;
	}
};

#endif /* DATABASE_H_ */
