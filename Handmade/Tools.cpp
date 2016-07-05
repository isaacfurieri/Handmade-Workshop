#include <iostream>
#include "Tools.h"

//------------------------------------------------------------------------------------------------------
//function that converts passed string object to an integer value
//------------------------------------------------------------------------------------------------------
int StringToInteger(const std::string& str)
{

	return atoi(str.c_str());

}
//------------------------------------------------------------------------------------------------------
//function that converts passed string object to a float value
//------------------------------------------------------------------------------------------------------
float StringToFloat(const std::string& str)
{

	return (float)atof(str.c_str());

}
//------------------------------------------------------------------------------------------------------
//function that splits a string object into segments based on token passed
//------------------------------------------------------------------------------------------------------
void ParseString(std::string& str, std::vector<std::string>& subStrings, char token)
{

	//variable to hold position of token
	unsigned int tokenPosition = 0;

	//first check if string is empty and display error message if it is
	if (str.empty())
	{
		std::cout << "The passed string is empty." << std::endl;
	}

	//otherwise find the token position, store the substring  
	//and erase that portion of the original string object as 
	//long as the end of the string has not been reached 
	else
	{
		do
		{

			tokenPosition = str.find(token);
			subStrings.push_back(str.substr(0, tokenPosition));
			str.erase(0, tokenPosition + 1);

		} while (tokenPosition != std::string::npos);
	}

}