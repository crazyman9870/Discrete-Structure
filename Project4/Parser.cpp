/*
 * Parser.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: aconstan
 */

#include "Parser.h"

using namespace std;

Parser::Parser(vector<Token> vector_in)
{
	tlist = vector_in;
	pos = 0;
}

Parser::~Parser()
{

}

//=====================================================================

void Parser::print(ofstream& output)
{
	output << "Success!" << endl;
	output << final << endl;
	for (set<string>::iterator it = domain.begin(); it != domain.end(); ++it)
	{
		output << "  \'" << *it << "\'" << endl;
	}
}

void Parser::printSet()
{
	for (set<string>::iterator it = domain.begin(); it != domain.end(); ++it)
	{
		cout << "  \'" << *it << "\'" << endl;
	}
}

void Parser::printPreVec(vector<Predicate> list)
{
	for (int i = 0; i < (int)list.size(); i++)
	{
		cout << (i+1) << ":\t" << list[i].name << endl;
		for (int j = 0; j < (int)list[i].parameters.size(); j++)
		{
			cout << "\t" << (j+1) << ":\t" << list[i].parameters[j].value << endl;
		}
	}
}

void Parser::printRuleVec(vector<Rule> list)
{
	for (int i = 0; i < (int)list.size(); i++)
	{
		cout << (i+1) << ":Head\t" << list[i].head.name << endl;
			for (int k = 0; k < (int)list[i].head.parameters.size(); k++)
			{
				cout << "\t" << (k+1) << ":\t" << list[i].head.parameters[k].value;
				cout << endl;
			}
		for (int j = 0; j < (int)list[i].tail.size(); j++)
		{
			cout << "\t\t" << (j+1) << ":\t" << list[i].tail[j].name << endl;
			for (int k = 0; k < (int)list[i].tail[j].parameters.size(); k++)
			{
				cout << "\t\t\t" << (k+1) << ":\t" << list[i].tail[j].parameters[k].value << endl;
			}
		}
	}
}

void Parser::match(string type)
{
	if (type == "STRING")
	{
		domain.insert(curT.getValue());
	}
	/*if (type == "ID")
	{

	}
	//NOT SURE IF THE ABOVE NEEDS TO BE INCLUDED BECAUSE THE DOMAIN WILL ONLY
	//CONTAIN THE STRINGS THAT IT COMES ACROSS
	*/
	if (curT.getType() == type)
	{
		getToken();
	}
	else
	{
		throw curT;
	}
}

void Parser::getToken()
{
	pos++;
	curT = tlist[pos];
}

string Parser::toString()
{
	int n1 = S.size();
	int n2 = F.size();
	//int n3 = R.size();
	//int n4 = Q.size();
	//int n5 = domain.size();
	string result;

	//create Schemes
	string part1 = "Schemes(" + int_to_string(n1) + "):" + "\n";

	//create Schemes List
	string part2 = "";
	for (int i = 0; i < n1; i++)
	{
		part2 += "  " + S[i].toString();
		if (i != (n1-1))
		{
			part2 += "\n";
		}
	}
	part2 += "\n";

	//create Facts
	string part3 = "Facts(" + int_to_string(n2) + "):" + "\n";

	//create Facts List
	string part4 = "";
	for (int i = 0; i < n2; i++)
	{
		part4 += "  " + F[i].toString();
		if (i != (n2-1))
		{
			part4 += "\n";
		}
	}
	part4 += "\n";




	string temp = toString2();
	result = part1 + part2 + part3 + part4 + temp;
	return result;
}

string Parser::toString2()
{
	int n3 = R.size();
	int n4 = Q.size();
	int n5 = domain.size();
	string result;

	//create Rules
	string part5 = "Rules(" + int_to_string(n3) + "):" + "\n";

	//create Rules List
	string part6 = "";
	for (int i = 0; i < n3; i++)
	{
		part6 += "  " + R[i].toString();
		if (i != (n3-1))
		{
			part6 += "\n";
		}
	}
	part6 += "\n";

	//create Queries
	string part7 = "Queries(" + int_to_string(n4) + "):" + "\n";

	//create Queries List
	string part8 = "";
	for (int i = 0; i < n4; i++)
	{
		part8 += "  " + Q[i].toString();
		if (i != (n4-1))
		{
			part8 += "\n";
		}
	}
	part8 += "\n";

	//create Domain
	string part9 = "Domain(" + int_to_string(n5) + "):";

	//creates Domain List
	/*
	part10 = "";
	for (set<string>::iterator it = domain.begin(); it != domain.end(); ++it)
	{
		part10 += "  " + *it;
	}
	*/

	result = part5 + part6 + part7 + part8 + part9; //+ part10;
	return result;

}

string Parser::int_to_string(int n)
{
	ostringstream strm;
	strm << n;
	return strm.str();
}

//=====================================================================

DatalogProgram Parser::beginParsing()
{
	DatalogProgram prog;
	curT = tlist[pos];

	//cout << "1" << endl;

	match("SCHEMES");
	match("COLON");

	//cout << "2" << endl;

	schemeList();



	curPre.clear_vector();
	//cout << "3" << endl;

	match("FACTS");
	match("COLON");

	//cout << "4" << endl;

	factList();



	curPre.clear_vector();
	//cout << "5" << endl;

	match("RULES");
	match("COLON");

	//cout << "6" << endl;

	ruleList();



	curPre.clear_vector();
	//cout << "7" << endl;

	match("QUERIES");
	match("COLON");

	//cout << "8" << endl;

	queryList();



	curPre.clear_vector();
	//cout << "SUCCESS" << endl;

	/*
	cout << "Printing Schemes Vector" << endl;
	printPreVec(S);

	cout << "Printing Facts Vector" << endl;
	printPreVec(F);

	cout << "Printing Rules Vector" << endl;
	printRuleVec(R);

	cout << "Printing Queries Vector" << endl;
	printPreVec(Q);

	cout << "Printing Domain Set" << endl;
	printSet();
	*/

	final = toString();
	//cout << final << endl;

	//update the datalog program object with the results
	prog.newSchemes(S);
	prog.newFacts(F);
	prog.newRules(R);
	prog.newQueries(Q);
	prog.newDomain(domain);

	return prog;
}

//=====================================================================

void Parser::scheme()
{
	curPre.name = curT.getValue();
	match("ID");

	match("LEFT_PAREN");

	if (curT.getType() == "RIGHT_PAREN")
	{
		throw curT;
	}


	parameterList();

	//cout << "6" << endl;
	match("RIGHT_PAREN");

	S.push_back(curPre);
	curPre.clear_vector();

}

void Parser::schemeList()
{
	scheme();

	while(curT.getType() != "FACTS")
	{
		scheme();
	}
}

//=====================================================================

void Parser::fact()
{
	curPre.name = curT.getValue();
	match("ID");

	match("LEFT_PAREN");

	if (curT.getType() == "RIGHT_PAREN")
	{
		throw curT;
	}

	parameterList();

	match("RIGHT_PAREN");
	match("PERIOD");

	F.push_back(curPre);
	curPre.clear_vector();
}

void Parser::factList()
{
	while(curT.getType() != "RULES")
	{
		fact();
	}
}

//=====================================================================

void Parser::rule()
{
	curPre.clear_vector();
	curPre.name = curT.getValue();
	match("ID");
	match("LEFT_PAREN");

	if (curT.getType() == "RIGHT_PAREN")
	{
		throw curT;
	}

	parameterList();

	match("RIGHT_PAREN");

	curR.head = curPre; //assigns the head of the rule
	curPre.clear_vector(); //clears the head predicate vector

	match("COLON_DASH");
}

void Parser::rule2()
{


	curPre.name = curT.getValue(); //Assign the curPre to the first Predicate in the tail
	match("ID"); //There must be at least one ID after a rule head
	match("LEFT_PAREN");

	if (curT.getType() == "RIGHT_PAREN")
	{
		throw curT;
	}

	parameterList();

	match("RIGHT_PAREN");

	curR.tail.push_back(curPre); //adds this predicate to the current rule's tail
	curPre.clear_vector(); //Once again clears the new predicate's vector



}

void Parser::rule3()
{
	while(curT.getType() != "PERIOD")
		{
			match("COMMA");

			curPre.name = curT.getValue(); //Assign the curPre to the other predicates
			match("ID");
			match("LEFT_PAREN");

			if (curT.getType() == "RIGHT_PAREN")
			{
				throw curT;
			}

			parameterList();

			match("RIGHT_PAREN");

			curR.tail.push_back(curPre); //adds this predicate to the current rule's tail
			curPre.clear_vector(); //Once again clears the new predicate's vector

		}
		match("PERIOD");

		R.push_back(curR); //Adds curR to the R vector or Rules
		curR.clear_vector(); //Clears the curR vector
}

void Parser::ruleList()
{
	while(curT.getType() != "QUERIES")
	{
		rule();
		rule2();
		rule3();
	}
}

//=====================================================================

void Parser::query()
{
	curPre.name = curT.getValue();
	match("ID");
	match("LEFT_PAREN");

	if (curT.getType() == "RIGHT_PAREN")
	{
		throw curT;
	}

	parameterList();

	match("RIGHT_PAREN");
	match("Q_MARK");

	Q.push_back(curPre);
	curPre.clear_vector();

}

void Parser::queryList()
{
	query();

	while(curT.getType() != "END")
	{
		query();
	}
}

//=====================================================================

void Parser::parameterList()
{
		curPar.value = curT.getValue();
		if(curT.getType() == "STRING")
		{
			curPar.is_string = true;
			match("STRING");
		}
		else if(curT.getType() == "ID")
		{
			curPar.is_string = false;
			match("ID");
		}
		else
		{
			throw curT;
		}
		curPre.parameters.push_back(curPar);
		if(curT.getType() != "RIGHT_PAREN")
		{
			match("COMMA");
			parameterList();
		}
}

