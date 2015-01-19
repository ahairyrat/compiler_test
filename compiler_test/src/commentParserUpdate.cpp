
#include "commentParser.h"

#include <iostream>

commentError removeComment(std::string input, std::string &output, commentError currentState)
{
	bool inComment = false, inString = false;
	output = "";
	if (currentState == COMMENT_MULTILINE)
		inComment = true;
	for(unsigned i = 0; i < input.size(); i++)
	{
		switch(input[i])
		{
		case '/' :
			if (inString)
			{
				output += input[i];
				break;
			}
			if (input[i - 1] == '*')
			{
				inComment = false;
				break;
			}
			switch (input[i + 1])
			{
			case '/':
				return COMMENT_NO_ERROR;
			case '*':
				inComment = true;
			}
			if (!inComment)
			{
				output += input[i];
				break;
			}
			break;
		case '"' :
			inString = !inString;
			output += input[i];
			break;
		default:
			if (!inComment)
				output += input[i];
			break;
		}
	}
	if (inComment)
		return COMMENT_MULTILINE;
	return COMMENT_NO_ERROR;
}

void debugTest(){
	std::string input = "Hello /* asfafasfsfasf";
	std::string input2 = "Hello */ asfafasfsfasf";
	std::string output;
	std::cout << std::hex << removeComment(input, output, COMMENT_NO_ERROR) << std::endl;
	std::cout << output << std::endl;
	std::cout << std::hex << removeComment(input2, output, COMMENT_MULTILINE) << std::endl;
	std::cout << output << std::endl;
}