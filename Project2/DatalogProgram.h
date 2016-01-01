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

	vector<Predicate> getFacts();

	vector<Predicate> getQueries();

	vector<Rule> getRules();

	set<string> getDomain();

};

#endif /* DATALOGPROGRAM_H_ */
