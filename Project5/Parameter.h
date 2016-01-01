/*
 * Parameter.h
 *
 *  Created on: Jul 7, 2014
 *      Author: aconstan
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "Token.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

class Parameter
{
private:

public:
	Parameter();
	virtual ~Parameter();

	string value;
	bool is_string;

	string toString();
};

#endif /* PARAMETER_H_ */
