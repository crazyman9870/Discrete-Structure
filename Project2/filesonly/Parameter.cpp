/*
 * Parameter.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: aconstan
 */

#include "Parameter.h"

using namespace std;

Parameter::Parameter()
{
	value = "";
	is_string = false;
}

Parameter::~Parameter()
{

}

string Parameter::toString()
{
	string par;
	if (is_string == true)
	{
		par = "\'" + value +"\'";
	}
	else
	{
		par = value;
	}
	return par;
}
