// compiler_test.cpp : Defines the entry point for the console application.
//
#define DEBUG true

#include <iostream>
#include <fstream>

#include "commentParser.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (DEBUG)
	{
		debugTest();
		getchar();
		return 0;
	}
	commentError currentState = COMMENT_NO_ERROR;
	string inFileName, outFileName, inputLine, outputLine, fileExtension;
	ifstream inFile;
	ofstream outFile;
	cout << "Please enter the name of the file to be parsed:" << endl;
	cin >> inFileName;
	fileExtension = inFileName.substr(inFileName.find('.'));

	if (fileExtension != ".c")
	{
		cout << "The file " << inFileName << " is not a valid C source file" << endl;
		return 0;
	}

	inFile.open(inFileName.c_str());
	if (!inFile.is_open())
	{
		cout << "The file " << inFileName << " does not exist." << endl;
		return 0;
	}

	outFileName = inFileName.substr(0, inFileName.find('.'));
	outFile.open(((outFileName += "_no_comments") += fileExtension).c_str());
	while (getline(inFile, inputLine))
	{
		currentState = removeComment(inputLine, outputLine, currentState);
		if (currentState != COMMENT_UNKNOWN_ERROR)
		{
			outFile << outputLine;
			if (currentState != COMMENT_MULTILINE && currentState != COMMENT_SINGLELINE_ONLY)
				outFile << endl;
		}
	}

	outFile.close();
	inFile.close();
	cout << "All comments have been removed" << endl;
	return 0;
}

