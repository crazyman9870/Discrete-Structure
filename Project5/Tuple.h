/*
 * Tuple.h
 *
 *  Created on: Jul 21, 2014
 *      Author: aconstan
 */

#ifndef TUPLE_H_
#define TUPLE_H_

#include <string>
#include <vector>

using namespace std;

class Tuple : public vector<string>
{
public:
	Tuple()
	{

	}
	virtual ~Tuple()
	{

	}

	Tuple cartesian(Tuple& tu2)
	{
		Tuple newGuy = *this;
		for(int i = 0; i < (int)tu2.size(); i++)
		{
			newGuy.push_back(tu2[i]);
		}
		return newGuy;
	}

	bool checkPossible(Tuple& tu2, vector<int>& v1, vector<int>& v2)
	{
		for(int i = 0; i < (int)v1.size(); i++)
		{
			int pos1 = v1[i];
			int pos2 = v2[i];
			if(at(pos1) != tu2[pos2])
			{
				return false;
			}
		}
		return true;
	}

	bool find(int index, vector<int>& v2)
	{
		for(int i = 0; i < (int)v2.size(); i++)
		{
			if(index == v2[i])
			{
				return true;
			}
		}
		return false;
	}

	Tuple joinT(Tuple& tu2, vector<int>& v2)
	{
		Tuple newGuy = *this;
		for(int i = 0; i < (int)tu2.size(); i++)
		{
			if(!find(i, v2))
			{
				newGuy.push_back(tu2[i]);
			}
		}
		return newGuy;
	}



	bool joinTuples(Tuple& tu2, vector<int>& v1, vector<int>& v2, Tuple& tu3)
	{
		if(tu2.size() == 0)
		{
			return false;
		}
		else if(v1.size() == 0)
		{
			//cout << "CARTESIAN" << endl;
			tu3 = cartesian(tu2);
			return true;
		}
		else
		{
			//cout << "NON CARTESIAN" << endl;
			if(checkPossible(tu2, v1, v2))
			{
				//cout << "JOINABLE" << endl;
				tu3 = joinT(tu2, v2);
				return true;
			}
		}
		return false;
	}
};

#endif /* TUPLE_H_ */
