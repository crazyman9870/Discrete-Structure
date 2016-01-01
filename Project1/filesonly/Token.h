/*
 * Token.h
 *
 *  Created on: Jun 28, 2014
 *      Author: aconstan
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sstream>

using namespace std;


/*enum TokenType
{
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES,
	FACTS, RULES, QUERIES, ID, STRING
};*/


class Token
{

private:
	string type;
	string value;
	int line;


public:
	Token(string type_in, string value_in, int line_in);
	virtual ~Token();


	string getType();

	string getValue();

	int getLine();



};

#endif /* TOKEN_H_ */
