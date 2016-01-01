/*
 * Predicate.h
 *
 *  Created on: Jul 7, 2014
 *      Author: aconstan
 */

#ifndef PREDICATE_H_
#define PREDICATE_H_

#include "Parameter.h"
#include "Token.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

class Predicate
{
private:



public:
	Predicate();
	virtual ~Predicate();

	string name;
	vector<Parameter> parameters;

	void clear_vector();

	string toString();
};

#endif /* PREDICATE_H_ */
