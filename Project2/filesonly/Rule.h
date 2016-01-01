/*
 * Rule.h
 *
 *  Created on: Jul 8, 2014
 *      Author: aconstan
 */

#ifndef RULE_H_
#define RULE_H_

#include "Parameter.h"
#include "Predicate.h"
#include "Token.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

class Rule
{
private:



public:
	Rule();
	virtual ~Rule();

	Predicate head;
	vector<Predicate> tail;

	void clear_vector();

	string toString();

};

#endif /* RULE_H_ */
