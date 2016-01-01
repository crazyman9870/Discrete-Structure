/*
 * Scanner.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: aconstan
 */

#include "Scanner.h"

using namespace std;

Scanner::Scanner()
{
	fail = false;
	line_count = 1;
	total_token = 0;
}

Scanner::~Scanner()
{

}

void Scanner::print(ofstream& output)
{
	if (fail == true)
	{
		for (int i = 0; i < (int)tlist.size(); i++)
		{
			output << "(" << tlist[i].getType() << ",\"" << tlist[i].getValue() << "\","
					<< tlist[i].getLine() << ")" << endl;
		}
		output << "Input Error on line " << line_count << endl;
	}
	else
	{
		for (int i = 0; i < (int)tlist.size(); i++)
		{
			output << "(" << tlist[i].getType() << ",\"" << tlist[i].getValue() << "\","
					<< tlist[i].getLine() << ")" << endl;
		}
		output << "Total tokens = " << total_token << endl;
	}
}

/*void Scanner::enumString(some input of type);
{
	string str;
	switch(input)
	case COMMA:
		str == "COMMA";
		break;
	case ...
	default:
		break;
}*/

int Scanner::getTotalToken()
{
	return total_token;
}

vector<Token> Scanner::getVector()
{
	return tlist;
}

//=======================================================================

bool Scanner::getFailstate()
{
	return fail;
}

int Scanner::getLine_count()
{
	return line_count;
}

void Scanner::inicheck(ifstream& input)
{
	while(input.peek() != -1 && fail == false)
	{
		char c = input.get();
		if (isalpha(c))
		{
			ID(c, input); //checks keywords and ID tokens
		}
		else
		{
			switch(c)
			{
			case ' ':
			case '\n':
			case '\t':
				nline(c); //handles spaces and new line chars
				break;

			case '#':
				comment(c, input); //handles comments
				break;

			case ':':
				colon(c, input); //handles : :- tokens
				break;

			case '\'':
				isString(c, input); //handles string tokens
				break;

			case ',':
			case '.':
			case '?':
			case '(':
			case ')':
				punct(c); //handles , . ? ( ) tokens
				break;
			default:
				fail = true;
			}
		}
	}

	//creating a terminate token
	Token t("END","End Token", line_count);
	tlist.push_back(t);
	return;
}

void Scanner::nline(char c)
{
	if (c == ' ')
	{
		return;
	}
	else if (c == '\t')
	{
		return;
	}
	else if (c == '\n')
	{
		line_count++;
	}
	return;
}

void Scanner::comment(char c, ifstream& input)
{
	if (c == '#') //handles comments
	{
		while (c != '\n')
		{
			c = input.get();
		}
		nline(c); //handles spaces and new line chars
	}
}

void Scanner::punct(char c)
{
	if (c == ',')
	{
		Token t("COMMA",",",line_count);
		tlist.push_back(t);
		total_token++;
		return;
	}
	else if (c == '.')
	{
		Token t("PERIOD",".",line_count);
		tlist.push_back(t);
		total_token++;
		return;
	}
	else if (c == '?')
	{
		Token t("Q_MARK","?",line_count);
		tlist.push_back(t);
		total_token++;
		return;
	}
	else if (c == '(')
	{
		Token t("LEFT_PAREN","(",line_count);
		tlist.push_back(t);
		total_token++;
		return;
	}
	else if (c == ')')
	{
		Token t("RIGHT_PAREN",")",line_count);
		tlist.push_back(t);
		total_token++;
		return;
	}
	return;
}

void Scanner::colon(char c, ifstream& input)
{
	if (c == ':')
	{
		//char c1 = c;
		c = input.get();
		if (c == '-')
		{
			Token t("COLON_DASH",":-",line_count);
			tlist.push_back(t);
			total_token++;
		}
		else
		{
			Token t("COLON",":",line_count);
			tlist.push_back(t);
			total_token++;
			input.unget();
		}
	}
}

bool Scanner::keyword(string str)
{
	if (str == "Schemes")
	{
		Token t("SCHEMES","Schemes",line_count);
		tlist.push_back(t);
		total_token++;
		return true;
	}
	if (str == "Facts")
	{
		Token t("FACTS","Facts",line_count);
		tlist.push_back(t);
		total_token++;
		return true;
	}
	if (str == "Rules")
	{
		Token t("RULES","Rules",line_count);
		tlist.push_back(t);
		total_token++;
		return true;
	}
	if (str == "Queries")
	{
		Token t("QUERIES","Queries",line_count);
		tlist.push_back(t);
		total_token++;
		return true;
	}
	return false;
}

void Scanner::ID(char c, ifstream& input)
{
	bool added = false;
	string str;
	if (isalpha(c))
	{
		while (isalpha(c) || isdigit(c))
		{
			str += c;
			c = input.get();
		}
		added = keyword(str); //handles keywords
		if (added == false)
		{
			Token t("ID",str,line_count);
			tlist.push_back(t);
			total_token++;
		}
		input.unget();
	}
}

void Scanner::isString(char c, ifstream& input)
{
	string str;
	if (c == '\'')
	{
		c = input.get();
		while (c != '\'')
		{
			str += c;
			c = input.get();
			if (c == '\n' || input.eof())
			{
				fail = true;
				return;
			}
		}
		//cout << str << endl;
		Token t("STRING",str,line_count);
		tlist.push_back(t);
		total_token++;
	}
}
