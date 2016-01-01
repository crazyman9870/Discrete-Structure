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
	int nqueries;


public:
	Interpreter()
	{
		nschemes = 0;
		nfacts = 0;
		nqueries = 0;
	}
	virtual ~Interpreter()
	{

	}
	//========================================================================
	Database mainFxn(DatalogProgram prog, ostream& output)
	{
		nschemes = prog.getSizeS(); //gets the number of predicates in the Schemes
		nfacts = prog.getSizeF(); //gets the number of predicates in the Facts
		nqueries = prog.getSizeQ(); //gets the number of predicates in the Queries

		vector<Predicate> Queries = prog.getQueries();

		data.dataFxn(prog);

		//data.seeMap();
		//SHOWS THAT THE DATABASE WAS CORRECTLY UPDATED

		int counter = 0;
		while (counter < nqueries)
		{
			data.beginTestingQ(Queries[counter]);
			counter++;
		}

		//data.printToString();
		data.printOutput(output);

		return data;
	}

	//========================================================================

};

#endif /* INTERPRETER_H_ */
