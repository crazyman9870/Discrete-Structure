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

#include <iostream>
#include <string>
#include <vector>
#include <map>

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
	Database mainFxn(DatalogProgram& prog, ostream& output)
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

		bool changed = true;
		int counter = 0;
		/*

		while (counter < nrules)
		{
			data.beginTestingR(Rules[counter], changed);
			counter++;
		}
		*/
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

		return data;
	}

	//========================================================================

};

#endif /* INTERPRETER_H_ */
