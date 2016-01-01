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

int DatalogProgram::getSizeS()
{
	return S.size();
}

vector<Predicate> DatalogProgram::getFacts()
{
	return F;
}

int DatalogProgram::getSizeF()
{
	return F.size();
}

vector<Predicate> DatalogProgram::getQueries()
{
	return Q;
}

int DatalogProgram::getSizeQ()
{
	return Q.size();
}

vector<Rule> DatalogProgram::getRules()
{
	return R;
}

int DatalogProgram::getSizeR()
{
	return R.size();
}

set<string> DatalogProgram::getDomain()
{
	return domain;
}

//======================================================================

void DatalogProgram::newSchemes(vector<Predicate> list)
{
	S = list;
}

void DatalogProgram::newFacts(vector<Predicate> list)
{
	F = list;
}

void DatalogProgram::newQueries(vector<Predicate> list)
{
	Q = list;
}

void DatalogProgram::newRules(vector<Rule> list)
{
	R = list;
}

void DatalogProgram::newDomain(set<string> list)
{
	domain = list;
}

//==========================================================================

void DatalogProgram::printSVec()
{
	for (int i = 0; i < (int)S.size(); i++)
	{
		cout << (i+1) << ":\t" << S[i].name << endl;
		for (int j = 0; j < (int)S[i].parameters.size(); j++)
		{
			cout << "\t" << (j+1) << ":\t" << S[i].parameters[j].value << endl;
		}
	}
}

void DatalogProgram::printFVec()
{
	for (int i = 0; i < (int)F.size(); i++)
	{
		cout << (i+1) << ":\t" << F[i].name << endl;
		for (int j = 0; j < (int)F[i].parameters.size(); j++)
		{
			cout << "\t" << (j+1) << ":\t" << F[i].parameters[j].value << endl;
		}
	}
}

void DatalogProgram::printQVec()

{
	for (int i = 0; i < (int)Q.size(); i++)
	{
		cout << (i+1) << ":\t" << Q[i].name << endl;
		for (int j = 0; j < (int)Q[i].parameters.size(); j++)
		{
			cout << "\t" << (j+1) << ":\t" << Q[i].parameters[j].value << endl;
		}
	}
}

void DatalogProgram::printRuleVec()
{
	for (int i = 0; i < (int)R.size(); i++)
	{
		cout << (i+1) << ":Head\t" << R[i].head.name << endl;
			for (int k = 0; k < (int)R[i].head.parameters.size(); k++)
			{
				cout << "\t" << (k+1) << ":\t" << R[i].head.parameters[k].value;
				cout << endl;
			}
		for (int j = 0; j < (int)R[i].tail.size(); j++)
		{
			cout << "\t\t" << (j+1) << ":\t" << R[i].tail[j].name << endl;
			for (int k = 0; k < (int)R[i].tail[j].parameters.size(); k++)
			{
				cout << "\t\t\t" << (k+1) << ":\t" << R[i].tail[j].parameters[k].value << endl;
			}
		}
	}
}

void DatalogProgram::printSet()
{
	for (set<string>::iterator it = domain.begin(); it != domain.end(); ++it)
	{
		cout << "  \'" << *it << "\'" << endl;
	}
}

//==========================================================================

Predicate DatalogProgram::accPredS(int n)
{
	return S[n];
}

Predicate DatalogProgram::accPredF(int n)
{
	return F[n];
}

Predicate DatalogProgram::accPredQ(int n)
{
	return Q[n];
}

Predicate DatalogProgram::accHeadR(int n)
{
	return R[n].head;
}

Predicate DatalogProgram::accTailR(int n, int m)
{
	return R[n].tail[m];
}

//============================================================================
