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
#include "Parameter.h"
#include "Rule.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

class Database
{
private:

	map<string, Relation> Rmap;

	int nschemes;
	int nfacts;
	int nrules;
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
		nrules = 0;
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
	map<string, Relation> dataFxn(DatalogProgram& prog)
	{
		nschemes = prog.getSizeS(); //gets the number of predicates in the Schemes
		nfacts = prog.getSizeF(); //gets the number of predicates in the Facts
		nrules = prog.getSizeR(); //gets the number of rule objects in the Rules
		nqueries = prog.getSizeQ(); //gets the number of predicates in the Queries

		createRelations(nschemes, prog);



		return Rmap;
	}

	void createRelations(int num, DatalogProgram& prog)
	{
		int counter = 0;
		while (counter < nschemes)
		{
			handleRelations(prog, counter);
			counter++;
		}
	}

	void handleRelations(DatalogProgram& prog, int n)
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

	void handleScheme(const DatalogProgram& prog, Predicate pred)
	{
		for(int i = 0; i < (int)pred.parameters.size(); i++)
		{
			curS.addAtribute(pred.parameters[i].value);
		}

		//curS.print();
	}

	void handleTuples(DatalogProgram& prog)
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
				createTuple(p);
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

	void createTuple(const Predicate& p)
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
	void beginTestingR(Rule& r, int& check)
	{
		//cout << "\nEnter\n" << endl;

 		string hname = r.head.name;

		Relation head = Rmap.at(hname);
		//head.seeEntireRelation();

		handleJoin(r);

		vector<string> column;
		createCol(r.head.parameters, column);

		/*
		cout << "\nPRINTING COLUMNS TO BE PROJECTED\n" << endl;
		for (int i = 0; i < (int)column.size(); i++)
		{
			cout << i << ":\t" << column[i] << endl;
		}
		cout << "\n\n";
		*/

		handleProjectRule(column);
		int check_size1 = Rmap.at(hname).getSetSize();
		Rmap.at(hname).addToSet(curR.getTuples());
		int check_size2 = Rmap.at(hname).getSetSize();

		if (check_size2 > check_size1)
		{
			check++;
		}

		Relation empty_rel;
		curR = empty_rel;

		//cout << "\nExit\n" << endl;
	}



	void unionize()
	{

	}

	void handleJoin(Rule& r)
	{
		createCombScheme(r);

		//bool empty = false;

		curR.addScheme(curS);

		//cout << "\n";
		//curS.print(); //These two lines are to verify that the correct scheme was made
		//cout << "\n";
		curS.clear();

		if (r.tail.size() > 1)
		{	//cout << "\nHAPPY\n" << endl;
			//joiner(r,r.tail);
			curR = joiner2(r.tail);
			//cout << "\nSAD\n" << endl;
		}
		else if (r.tail.size() == 1)
		{
			Predicate p = r.tail[0];
			bool empty = false;
			Relation z = Rmap.at(p.name);
			curR.addToSet(z.getTuples());
			handleSelect(p, empty);
		}
		//curR.seeEntireRelation();



	}

	void createSchemeR(Rule& r, int k)
	{
		for(int i = 0; i < (int)r.tail[k].parameters.size(); i++)
		{
			curS.addAtribute(r.tail[k].parameters[i].value);
		}
	}

	void createSchemeR2(vector<Predicate> tail, int k)
	{
		for(int i = 0; i < (int)tail[k].parameters.size(); i++)
		{
			curS.addAtribute(tail[k].parameters[i].value);
		}
	}

	void createCombScheme(Rule& r)
	{
		for(int i = 0; i < (int)r.tail.size(); i++)
		{
			for(int j = 0; j < (int)r.tail[i].parameters.size(); j++)
			{
				//bool dbl = checkSchemeDbl(r.tail[i].parameters[j].value);
				/*if(dbl == false)
				{
					curS.addAtribute(r.tail[i].parameters[j].value);
				}*/
				curS.addAtribute(r.tail[i].parameters[j].value);
			}
		}
	}

	void createCombScheme2(Rule& r, int k)
	{
		for(int j = 0; j <= k; j++)
		{
			for (int i = 0; i < (int)r.tail[j].parameters.size(); i++)
			{
				curS.addAtribute(r.tail[j].parameters[i].value);
			}
		}
	}

	bool checkSchemeDbl(string a)
	{
		vector<string> list = curS.getAtributes();
		bool dbl = false;
		for (int i = 0; i < (int)list.size(); i++)
		{
			if (a == list[i])
			{
				dbl = true;
				return dbl;
			}
		}
		return dbl;
	}

	void createCol(vector<Parameter>& plist, vector<string>& column)
	{
		for (int i = 0; i < (int)plist.size(); i++)
		{
			column.push_back(plist[i].value);
		}
	}


	Relation joiner2(vector<Predicate> list)
	{
		Relation r1 = Rmap.at(list[0].name);
		bool empty;
		handleSelect2(r1, list[0], empty);
		createSchemeR2(list, 0);
		r1.addScheme(curS);
		curS.clear();
		//r1.seeScheme();

		for (int i = 1; i < (int)list.size(); i++)
		{
			Relation r2 = Rmap.at(list[i].name);
			handleSelect2(r2, list[i], empty);
			createSchemeR2(list, i);
			r2.addScheme(curS);
			curS.clear();
			//r2.seeScheme();

			Relation r3 = r1.join(r2);
			//cout << "MOTHER TRUCKER" << endl;
			//r3.seeEntireRelation();


			r1 = r3;
			//r1.seeScheme();
		}
		return r1;
	}







	/*
	void joiner(Rule& r, vector<Predicate>& list)
	{
		Relation r1 = Rmap.at(list[0].name);
		set<Tuple> t1 = r1.getTuples();
		createSchemeR(r, 0);
		r1.addScheme(curS);
		curS.clear();

		for (int i = 1; i < (int)list.size(); i++)
		{
			//cout << "\nPASS\n\n";
			Relation r2 = Rmap.at(list[i].name);
			set<Tuple> t2 = r2.getTuples();
			createSchemeR(r, i);
			r2.addScheme(curS);
			curS.clear();
			//r1.seeEntireRelation();
			//r2.seeEntireRelation();
			vector<int> v1;
			vector<int> v2;
			findPositions(r1, r2, v1, v2);


			for (int g = 0; g < (int)v1.size(); g++)
			{
				cout << "\nv1\tv2\n" << v1[g] << "\t" << v2[g] << "\n\n";
			}



			//cout << "\nENTER COMBINED\n\n";
			t1 = combined(r1, t1, t2, v1, v2);
			r1.changeSet(t1);
			//cout << "\nEXIT COMBINED\n\n";

			createCombScheme2(r, i);
			//curS.print();
			r1.addScheme(curS);
			//cout << "\n";
			//r1.seeScheme(); //These two lines are to verify that the correct scheme was made
			//cout << "\n";
			curS.clear();

		}

		//r1.seeEntireRelation();
		Predicate p;
		bool empty = false;
		createParams(p, curR.getScheme());
		curR.changeSet(r1.getTuples());
		//curR.seeScheme();
		//cout << "\nENTER SELECT\n\n";
		handleSelect2(p, empty);		//cout << "\nDONE\n\n";
		//curR.seeEntireRelation();
	}
	*/

	void findPositions(Relation& r1, Relation& r2, vector<int>& v1, vector<int>& v2)
	{
		/*
		Scheme s1 = r1.getScheme();
		s1.print();
		Scheme s2 = r2.getScheme();
		s2.print();
		*/

		vector<string> a1 = r1.getSchemeVec();
		vector<string> a2 = r2.getSchemeVec();

		for (int i = 0; i < (int)a1.size(); i++)
		{
			//cout << a1[i] << endl;
			for (int j = 0; j < (int)a2.size(); j++)
			{
				//cout << a2[j] << endl;
				if (a1[i] == a2[j])
				{
					//cout << "I=" << i << endl;
					//cout << "J=" << j << endl;
					v1.push_back(i);
					v2.push_back(j);
					return;
				}
			}
		}
	}

	void createParams(Predicate& p, Scheme s)
	{
		vector<string> v1 = s.getAtributes();
		for (int i = 0; i < (int)v1.size(); i++)
		{
			Parameter par;
			par.value = v1[i];
			par.is_string = false;
			p.parameters.push_back(par);
		}
	}



	set<Tuple> combined(/*Relation& r1,*/ set<Tuple> t1, set<Tuple> t2, vector<int> v1, vector<int> v2)
	{
		set<Tuple> t3;


		for(set<Tuple>::iterator it = t1.begin(); it != t1.end(); ++it)
		{
			Tuple tu1 = (*it);//cout << "\nSTART LOOP 1\n" << endl;
			for(set<Tuple>::iterator it2 = t2.begin(); it2 != t2.end(); ++it2)
			{
				//cout << "\nSTART LOOP 2\n" << endl;

				//Tuple tu2 = (*it2);
				bool dbl;
				if (v1.size() > 0)
				{
					//cout << "\nSTART IF 1\n" << endl;
					int pos1 = v1[0];
					int pos2 = v2[0];
					dbl = canJoin((*it), (*it2), pos1, pos2);
				}
				else
				{
					dbl = true;
				}
				if (dbl == true)
				{
					//cout << "\nSTART IF 2\n" << endl;

					for(int i = 0; i < (int)(*it2).size(); i++)
					{
						//cout << "\nSTART LOOP 3\n" << endl;

						tu1.push_back((*it2)[i]);
					}

					//tu1.insert(tu1.end(), tu2.begin(), tu2.end());
				}
				curT = tu1;

				t3.insert(curT);
				curT.clear();
				tu1 = (*it);

			}
			//cout << "\nEND LOOP 1\n" << endl;
		}
		t1 = t3;
		return t1;
		//r1.changeSet(t1);

	}



	bool canJoin(const Tuple& tu1, const Tuple& tu2, int pos1, int pos2)
	{

		if ((int)tu1.size() >= pos1+1 && (int)tu2.size() >= pos2+1)
		{
			if(tu1[pos1] == tu2[pos2])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	void handleProjectRule(vector<string>& column)
	{
		Scheme schem = curR.getScheme();
		vector<string> list = schem.getAtributes();
		vector<int> indicies;
		findIndicies(column, list, indicies);

		/*
		cout << "\nPRINTING INDICIES TO BE PROJECTED\n" << endl;
		for (int i = 0; i < (int)indicies.size(); i++)
		{
			cout << i << ":\t" << indicies[i] << endl;
		}
		cout << "\n\n";
		*/

		if (indicies.size() > 0)
		{
			//curR.seeSet();
			//cout << "\n=================================================\n" << endl;
			curR.project2(indicies);
			//curR.seeSet();
			//cout << "\n=================================================\n" << endl;
			//cin.get();
		}

		//curR.seeSet();

	}

	void findIndicies(vector<string>& column, vector<string>& list, vector<int>& indicies)
	{
		for(int i = 0; i < (int)column.size(); i++)
		{
			//cout << "\n\n" << i << ":\t" << column[i] << endl;
			int pos = columnPos(column[i], list, indicies);
			indicies.push_back(pos);

		}
	}
	int columnPos(string i, vector<string>& list, vector<int>& indicies)
	{
		for(int j = 0; j < (int)list.size(); j++)
		{
			//cout << "\n" << j << ":\t" << list[j];
			if (i == list[j])
			{

				return j;
			}
		}
		return -1;
	}

	/*
	void checkJoinable3(const vector<Predicate>& list)
	{
		bool joinable = true;
		Relation r1 = Rmap.at(list[0].name);
		Scheme s1 = r1.getScheme();
		//r1.seeSet();
		//s1.print();
		//cout << "\n";

		int counter = 1;
		while(counter < (int)list.size())
		{
			Relation r2 = Rmap.at(list[counter].name);
			Scheme s2 = r2.getScheme();
			//s2.print();
			//cout << "\n\n";
			vector<int> matchedColumns = findMatchedColumn(s1,s2);
			for(int i = 0; i < (int)matchedColumns.size(); i++)
			{
				cout << i << ":\t" << matchedColumns[i] << endl;
			}
			cout << "\n\n";

			vector<string> matchedValues = r1.findMatchedValues(matchedColumns);
			for(int i = 0; i < (int)matchedValues.size(); i++)
			{
				cout << i << ":\t" << matchedValues[i] << endl;
			}
			cout << "\n\n";


			r2.comparison(matchedColumns, matchedValues, joinable, r1);

			if(joinable == true)
			{
				cout << "TRUE" << endl;
				for (int i = 1; i < (int)list.size(); i++)
				{
					string rname2 = list[i].name;
					curR.join(list, rname2);
				}
			}
			else
			{
				cout << "FALSE" << endl;
			}

			counter++;
		}
	}

	vector<int> findMatchedColumn(Scheme& s1, Scheme& s2)
	{
		vector<int> list;

		vector<string> a1 = s1.getAtributes();
		vector<string> a2 = s2.getAtributes();
		for(int i = 0; i < (int)a1.size(); i++)
		{
			for(int j = 0; j < (int)a2.size(); j++)
			{
				if(a1[i] == a2[j])
				{
					list.push_back(i);
					list.push_back(j);
				}
			}
		}
		return list;
	}
*/


//============================================================================
	void beginTestingQ(Predicate& p)
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

		newRelation(final_output, p, empty);

		handleProject(p);

		relationProject(final_output, empty);

		curT.clear();
		Relation vacant;
		curR = vacant;
		curS.clear();
		//final_output = relationProject(final_output, )
	}

	void handleSelect(Predicate& p, bool& empty)
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
						//cout << "\nHERE2\n\n";
						curR.select2(i, j, empty);
						//cout << "\nHERE3\n\n";
					}
				}
			}
		}
	}

	void handleSelect2(Relation& r, Predicate& p, bool& empty)
	{
		for (int i = 0; i < (int)p.parameters.size(); i++)
		{
			if (p.parameters[i].is_string == true)
			{
				r.select(i, p.parameters[i].value, empty);
			}
			else
			{
				int dcolumn;
				for (int j = 0; j < i; j++)
				{

					dcolumn = checkdup(p, i , j);

					if (dcolumn != -1)
					{
						//cout << "\nHERE12\n" << endl;
						r.select2(i, j, empty);
						//cout << "\nHERE13\n" << endl;
					}
				}
			}
		}
	}

	int checkdup(const Predicate& p, int curpos, int prevpos)
	{
		if (p.parameters[curpos].value == p.parameters[prevpos].value)
		{
			return prevpos;
		}
		return -1;
	}

	void handleProject(Predicate& p)
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
	string int_to_string(int n)
	{
		ostringstream strm;
		strm << n;
		return strm.str();
	}
	//========================================================================
	void newRelation(string& final, Predicate p, bool& empty)
	{
		string str = p.toString() + "?";

		int size = curR.getSetSize();

		if(empty == true || size == 0)
		{
			str += " No\n\n";
		}
		else
		{
			str += " Yes(" + int_to_string(size) + ")\n";
		}
		final += str;
	}

	void relationProject(string& final, bool& empty)
	{
		string str = "";

		if(empty == true)
		{
			return;
		}

		str = curR.pojectToString();
		final += str + "\n";
	}
	void resetFinalString()
	{
		string str = "";
		final_output = str;
	}
};

#endif /* DATABASE_H_ */
