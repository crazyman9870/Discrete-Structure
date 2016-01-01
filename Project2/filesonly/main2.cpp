/*
 * main.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: aconstan
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sstream>

#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parser.h"

using namespace std;

void printTokenList(vector<Token> list, int size)
{
	for (int i = 0; i < (int)list.size(); i++)
	{
		cout << "(" << list[i].getType() << ",\"" << list[i].getValue() << "\","
				<< list[i].getLine() << ")" << endl;
	}
	cout << "Total Tokens = " << size << endl;
	cout << "**NOTE** total tokens does not include the end token" << endl;
}

int main(int argc, char* argv[])
{

	ifstream input;
	input.open(argv[1]);

	ofstream output;
	output.open(argv[2]);

	try
	{
		Scanner a;

		a.inicheck(input);

		/*
		 THIS A.PRINT LINE OF CODE WAS USED FOR WRITING OUT THE RESULTS OF THE
		 SCANNER TO THE OUTPUT FILE IS NO LONGER NECESSARY BUT IF WANTED YOU COULD
		 UNCOMMENT IT OUT TO WRITE THOSE RESULTS TO THE OUTPUT FILE
		*/
		//a.print(output);

		//end everything to do with scanning the input
		//begin with parser prep and parsing

		vector<Token> tlist = a.getVector();

		/*
		UNCOMMENT THESE NEXT TWO LINES IN ORDER TO PRINT OUT THE TOKEN LIST
		THAT IS CREATED BY THE SCANNER
		*/
		//int token_count = a.getTotalToken();
		//printTokenList(tlist, token_count);

		Parser b(tlist);

		DatalogProgram c = b.beginParsing();
		b.print(output);

		input.close();
		output.close();
	}
	catch(Token t)
	{
		output << "Failure!" << endl;
		output << "(" << t.getType() << ",\"" << t.getValue() << "\","
				<< t.getLine() << ")" << endl;

		input.close();
		output.close();
	}



	return 0;
}



