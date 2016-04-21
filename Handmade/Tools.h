/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2016

  -----------------------------------------------------------------------------------------------

- This is a collection of some global tools that can be used throughout the client code

*/

#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>

//------------------------------------------------------------------------------------------------------
//declare and initialize global PI value
//------------------------------------------------------------------------------------------------------

static const double PI = 3.14159265359;

//------------------------------------------------------------------------------------------------------
//global function headers 
//------------------------------------------------------------------------------------------------------

void ParseString(std::string& text, char token, std::vector<std::string>& subStrings);

//double DegreeToRadian(double degree);
//double RadianToDegree(double radian);

//int StringToInt(const string& str);
//string IntToString(int num);
//float StringToFloat(const string& str);
//string FloatToString(float num);



#endif