/*
 * DatalogProgram.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: aconstan
 */

#include "DatalogProgram.h"

using namespace std;

DatalogProgram::DatalogProgram()
{

}

DatalogProgram::~DatalogProgram()
{

}

//=====================================================================

vector<Predicate> DatalogProgram::getSchemes()
{
	return S;
}

vector<Predicate> DatalogProgram::getFacts()
{
	return F;
}

vector<Predicate> DatalogProgram::getQueries()
{
	return Q;
}

vector<Rule> DatalogProgram::getRules()
{
	return R;
}

set<string> DatalogProgram::getDomain()
{
	return domain;
}
