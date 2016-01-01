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

	int getSize()
	{
		return atributes.size();
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

	void createNewScheme(Scheme s2)
	{
		for(int i = 0; i < (int)s2.getAtributes().size(); i++)
		{
			bool dbl = compare(s2.getAtributes()[i]);
			if (dbl == false)
			{
				atributes.push_back(s2.getAtributes()[i]);
			}
		}
	}

	bool compare(string val)
	{
		for(int i = 0; i < (int)atributes.size(); i++)
		{
			if(val == atributes[i])
			{
				return true;
			}
		}
		return false;
	}

	void fill(vector<string> s2, vector<int>& v1, vector<int>& v2)
	{
		for(int i = 0; i < (int)atributes.size(); i++)
		{
			for(int j = 0; j < (int)s2.size(); j++)
			{
				if(atributes[i] == s2[j])
				{
					v1.push_back(i);
					v2.push_back(j);
				}
			}
		}
	}
//============================================================================

};

#endif /* SCHEME_H_ */
