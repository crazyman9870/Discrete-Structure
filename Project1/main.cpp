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

using namespace std;



int main(int argc, char* argv[])
{

	ifstream input;
	input.open(argv[1]);

	ofstream output;
	output.open(argv[2]);

	Scanner a;

	a.inicheck(input);

	a.print(output);

	input.close();
	output.close();

	return 0;
}



