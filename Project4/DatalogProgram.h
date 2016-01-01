/*
 * DatalogProgram.h
 *
 *  Created on: Jul 8, 2014
 *      Author: aconstan
 */

#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <set>

using namespace std;

class DatalogProgram
{
private:

	vector<Predicate> S;
	vector<Predicate> F;
	vector<Predicate> Q;
	vector<Rule> R;
	set<string> domain;

public:
	DatalogProgram();
	virtual ~DatalogProgram();

	//=====================================================================

	vector<Predicate> getSchemes();
	int getSizeS();

	vector<Predicate> getFacts();
	int getSizeF();

	vector<Predicate> getQueries();
	int getSizeQ();

	vector<Rule> getRules();
	int getSizeR();

	set<string> getDomain();

	//======================================================================

	void newSchemes(vector<Predicate> list);

	void newFacts(vector<Predicate> list);

	void newQueries(vector<Predicate> list);

	void newRules(vector<Rule> list);

	void newDomain(set<string> list);

	//======================================================================

	void printSVec();

	void printFVec();

	void printQVec();

	void printRuleVec();

	void printSet();

	//======================================================================

	Predicate accPredS(int n);

	Predicate accPredF(int n);

	Predicate accPredQ(int n);

	Predicate accHeadR(int n);

	Predicate accTailR(int n, int m);
};

#endif /* DATALOGPROGRAM_H_ */
