
#include "commentParser.h"

//Removes comments within strings ("//xxxxxxxxx") even when it shouldn't
unsigned removeComment(std::string input, std::string &output, unsigned currentState)
{
	int commentPos = 0;
	if(currentState == COMMENT_SINGLELINE_ONLY)
		currentState = COMMENT_NO_ERROR;
	if(currentState != COMMENT_MULTILINE && currentState != COMMENT_UNKNOWN_ERROR)
	{
		commentPos = input.find("/*");
		//used for multi line commenting (/* ... */)
		if(commentPos != std::string::npos)
		{
			std::string inputRemainder;
			unsigned localState = COMMENT_MULTILINE;
			output =  input.substr(0, commentPos);
			localState = removeComment(input, inputRemainder, COMMENT_MULTILINE);
			if(localState == COMMENT_NO_ERROR)
				output += inputRemainder;
			return localState;
		}
		else
		{
			commentPos = input.find("//");
			//Used for in line commenting (//)
			if(commentPos != std::string::npos)
			{
				output =  input.substr(0, commentPos);
				if(output == "")
					return COMMENT_SINGLELINE_ONLY;
			}
			else
				output = input;
		}
		return COMMENT_NO_ERROR;
	}
	else if(currentState == COMMENT_MULTILINE)
	{
		//searches for the */ symbol
		unsigned localState = COMMENT_MULTILINE;
		commentPos = input.find("*/");
		if(commentPos != std::string::npos)
		{
			output =  input.substr(commentPos+2);
			//checks for any additional comments on that line
			localState = removeComment(output, output, COMMENT_NO_ERROR);
			return localState;
		}
		output = "";
		return COMMENT_MULTILINE;
	}
	return COMMENT_UNKNOWN_ERROR;
}
