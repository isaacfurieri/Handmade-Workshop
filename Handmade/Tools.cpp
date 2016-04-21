#include "Tools.h"

//------------------------------------------------------------------------------------------------------
//function that splits a string of text into segments based on token passed
//------------------------------------------------------------------------------------------------------
void ParseString(std::string& text, char token, std::vector<std::string>& subStrings)
{

	//variable to hold position of token
	unsigned int tokenPosition = 0;

	//as long as the end of the string is not reached place each
	//substring in a vector whenever the token symbol is found
	do
	{

		tokenPosition = text.find(token);
		subStrings.push_back(text.substr(0, tokenPosition));

		if (tokenPosition != std::string::npos)
		{
			text.erase(0, tokenPosition + 1);
		}

	} while (tokenPosition != std::string::npos);

}

//------------------------------------------------------------------------------------------------------
//function that converts a passed degree into a radian value
//------------------------------------------------------------------------------------------------------
//double DegreeToRadian(double degree)
//{
//
//	return degree / 180.0 * PI;
//	
//}
////------------------------------------------------------------------------------------------------------
////function that converts a passed radian into a degree value
////------------------------------------------------------------------------------------------------------
//double RadianToDegree(double radian)
//{
//
//	return radian / PI * 180.0;
//
//}
////------------------------------------------------------------------------------------------------------
////function that converts a string object to an integer value
////------------------------------------------------------------------------------------------------------
//int StringToInt(const string& str)
//{
//
//	return atoi(str.c_str());
//
//}
////------------------------------------------------------------------------------------------------------
////function that converts an integer value to a string object
////------------------------------------------------------------------------------------------------------
//string IntToString(int num)
//{
//
//	char tempStr[10];
//	
//	string str;
//	_itoa_s(num, tempStr, sizeof(tempStr), 10);
//	str = tempStr;
//
//	return str;
//
//}
////------------------------------------------------------------------------------------------------------
////function that converts a string object to a float value
////------------------------------------------------------------------------------------------------------
//float StringToFloat(const string& str)
//{
//
//	return (float)atof(str.c_str());
//
//}
////------------------------------------------------------------------------------------------------------
////function that converts a float value to a string object
////------------------------------------------------------------------------------------------------------
//string FloatToString(float num)
//{
//
//	stringstream str;
//	str << num;
//	return str.str();
//
//}