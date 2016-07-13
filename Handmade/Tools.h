/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2016

  -----------------------------------------------------------------------------------------------

- This is a collection of some global tools that is intended be used throughout the client code.
  It consists of a few helper functions for converting string text to numeric values and vice- 
  versa, and for parsing text. More helper functions will be added at a later stage.

- The conversion functions use low level conversion routines and c-style strings to convert numeric
  values to string values and vice-versa. The StringToInteger() and StringToFloat() functions both
  use two different conversion routines, hence why they couldn't be rolled into one. The
  NumberToString() function uses a stringstream object to convert any numberical type (int, float, etc)
  to a string object.

- The RemoveCharacter() function can be used to remove specific characters from a string. The routine
  will run through the entire string passed to the funciton and search for every occurence of the 
  desired character that needs to be removed from the string.

- The ParseString() function is intended to be used to break a large string sentence into smaller 
  chunks, using a character token that acts as a symbol which specifies where to split the string.
  For instance MyName=John could be split into two parts, namely "MyName" and "John", using the "="
  character as a splitting token. The function does not return anything, but rather uses the passed
  substring vector reference to store the smaller substrings in. If the substring vector were to be
  created in the routine that would mean returning a copy of it, which would be quite large if there
  were many substrings. 

*/

#ifndef TOOLS_H
#define TOOLS_H

#include <sstream>
#include <string>
#include <vector>

int StringToInteger(const std::string& str);
float StringToFloat(const std::string& str);
void RemoveCharacter(std::string& str, char character);
void ParseString(std::string& str, std::vector<std::string>& subStrings, char token);

template <typename T> std::string NumberToString(T number)
{
	std::stringstream str;
	str << number;
	return str.str();
}

#endif