/*
 * Scheme.h
 *
 *  Created on: Jul 21, 2014
 *      Author: aconstan
 */

#ifndef SCHEME_H_
#define SCHEME_H_

#include <string>
#include <vector>

using namespace std;

class Scheme
{
private:

	vector<string> atributes;


public:
	Scheme()
	{

	}
	virtual ~Scheme()
	{

	}
//============================================================================
	vector<string> getAtributes()
	{
		return atributes;
	}

	void addAtribute(string str)
	{
		atributes.push_back(str);
	}

	void print()
	{
		for (int i = 0; i < (int)atributes.size(); i++)
		{
			cout << i << ":\t" << atributes[i] << endl;
		}
	}

	void clear()
	{
		int num = (int)atributes.size();
		for (int i = 0; i < num; i++)
		{
			atributes.pop_back();
		}
	}

};

#endif /* SCHEME_H_ */
