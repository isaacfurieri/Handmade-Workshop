/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2016

  -----------------------------------------------------------------------------------------------

- This class wraps multiple variable types into one entity. This can become useful in situations
  when arbitrary data needs to be sent back and forth, and it's not known what types are needed
  or being used. The class supports the basic data types bool, char, string, int, float and 
  double. The main member variable, m_value, is a void pointer that references nothing at first
  and points to data specific to its type once created. To assign and access the data, specific
  type casting is used. There is a default constructor and a constructor for creating a variable
  of each type as well, because internally each specific data type needs to be separately 
  instantiated.

- There are various getter functions to return casted data values back to the client code. Each
  data type has its own getter, because having a generic getter that returns a void or void* will
  cause errors in the calling code.

- An Output() routine is there for debug purposes only and will print to the console what data type
  the Variable class currently represents, as well as what data it's containing.

*/

#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class Variable
{

public :

	enum VariableType { NULL_TYPE, BOOL_TYPE, CHAR_TYPE, STRING_TYPE, 
		                INT_TYPE, FLOAT_TYPE, DOUBLE_TYPE };

public :

	Variable();
	~Variable();
	
public :

	Variable(Variable& rhs);
	Variable(const bool& rhs);
	Variable(const char& rhs);
	Variable(const std::string& rhs);
	Variable(const int& rhs);
	Variable(const float& rhs);
	Variable(const double& rhs);

public :

	VariableType GetType();

public :

	bool GetBool();
	char GetChar();
	std::string GetString();
	int GetInt();
	float GetFloat();
	double GetDouble();	

public :

	Variable& operator=(const Variable& rhs);
	Variable& operator=(const bool& rhs);
	Variable& operator=(const char& rhs);
	Variable& operator=(const std::string& rhs);
	Variable& operator=(const int& rhs);
	Variable& operator=(const float& rhs);
	Variable& operator=(const double& rhs);

public :

	void Clear();
	void Output();

private :

	void* m_value;
	VariableType m_type;

};

#endif