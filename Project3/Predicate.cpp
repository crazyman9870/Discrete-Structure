/*
 * Predicate.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: aconstan
 */

#include "Predicate.h"

using namespace std;

Predicate::Predicate()
{

}

Predicate::~Predicate()
{

}


void Predicate::clear_vector()
{
	while (!parameters.empty())
	{
		parameters.pop_back();
	}
	/*
	for (int i = 0; i < (int)parameters.size(); i++)
	{
		parameters.pop_back();
	}
	*/
}

string Predicate::toString()
{
	string pre;
	pre = name + "(";
	int n = parameters.size();
	for (int i = 0; i < n; i++)
	{
		pre += parameters[i].toString();
		if (i == (n - 1))
		{
			pre += ")";
		}
		else
		{
			pre += ",";
		}
	}
	return pre;
}
