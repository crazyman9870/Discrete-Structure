/*
 * Parser.h
 *
 *  Created on: Jul 8, 2014
 *      Author: aconstan
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include "DatalogProgram.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <set>
#include <sstream>

using namespace std;

class Parser
{
private:

	vector<Token> tlist;
	Token curT;
	Predicate curPre;
	Parameter curPar;
	Rule curR;
	int pos;

	vector<Parameter> curList;
	set<string> domain;

	vector<Predicate> S;
	vector<Predicate> F;
	vector<Predicate> Q;
	vector<Rule> R;

	string final;

public:
	Parser(vector<Token> vector_in);
	virtual ~Parser();

	//=====================================================================

	void print(ofstream& output);

	void printSet();

	void printPreVec(vector<Predicate> list);

	void printRuleVec(vector<Rule> list);

	void match(string type);

	void getToken();

	string toString();

	string toString2();

	string int_to_string(int n);

	//=====================================================================

	DatalogProgram beginParsing();

	//=====================================================================

	void scheme();

	void schemeList();

	//=====================================================================

	void fact();

	void factList();

	//=====================================================================

	void rule();

	void rule2();

	void rule3();

	void ruleList();

	//=====================================================================

	void query();

	void queryList();

	//=====================================================================

	void predicate();

	void predicateList();

	void parameterList();

	void parameter();
};

#endif /* PARSER_H_ */
