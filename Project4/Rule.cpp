/*
 * Rule.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: aconstan
 */

#include "Rule.h"

using namespace std;

Rule::Rule()
{

}

Rule::~Rule()
{

}

void Rule::clear_vector()
{
	while (!tail.empty())
	{
		tail.pop_back();
	}
	/*
	for (int i = 0; i < (int)tail.size(); i++)
	{
		tail.pop_back();
	}
	*/
}

string Rule::toString()
{
	string rulez;
	rulez = head.toString() + " :- ";
	int n = tail.size();
	for (int i = 0; i < n; i++)
	{
		rulez += tail[i].toString();
		if (i == (n-1))
		{

		}
		else
		{
			rulez += ",";
		}
	}
	return rulez;

}
