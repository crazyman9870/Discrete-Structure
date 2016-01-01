/*
 * Scanner.h
 *
 *  Created on: Jun 28, 2014
 *      Author: aconstan
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sstream>


#include "Token.h"

using namespace std;

class Scanner
{
private:
	bool fail;
	int line_count;
	vector<Token> tlist;
	int total_token;

public:
	Scanner();
	virtual ~Scanner();

	void print(ofstream& output);

	//void enumString(some input of type);

	int getTotalToken();

	vector<Token> getVector();

	//======================================================================

	bool getFailstate();

	int getLine_count();

	void inicheck(ifstream& input);

	void nline(char c);

	void comment(char c, ifstream& input);

	void punct(char c);

	void colon(char c, ifstream& input);

	bool keyword(string str);

	void ID(char c, ifstream& input);

	void isString(char c, ifstream& input);

};

#endif /* SCANNER_H_ */
