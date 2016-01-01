/*
 * Token.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: aconstan
 */

#include "Token.h"

using namespace std;

Token::Token(string type_in, string value_in, int line_in)
{
	type = type_in;
	value = value_in;
	line = line_in;
}

Token::Token()
{
	type = "";
	value = "";
	line = 0;
}

Token::~Token()
{

}

string Token::getType()
{
	return type;
}

string Token::getValue()
{
	return value;
}

int Token::getLine()
{
	return line;
}

