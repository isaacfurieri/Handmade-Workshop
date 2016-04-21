#include <iostream>
#include "Variable.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
Variable::Variable()
{

	m_value = 0;
	m_type = NULL_TYPE;
	
}
//------------------------------------------------------------------------------------------------------
//copy constructor that makes a deep copy of each object based on passed copy's data type
//------------------------------------------------------------------------------------------------------
Variable::Variable(Variable& rhs)
{

	//first assign default values so that
	//if the copy is null nothing is done
	m_value = 0;
	m_type = NULL_TYPE;

	//first check that copy's data type is not null because
	//there is no need to make a copy of an empty variable 
	//use internal operator= function to assign values
	if (rhs.m_type != NULL_TYPE)
	{
		*this = rhs;
	}

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns passed boolean value using inner operator= function
//------------------------------------------------------------------------------------------------------
Variable::Variable(const bool& rhs)
{

	*this = rhs;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns passed character value using inner operator= function
//------------------------------------------------------------------------------------------------------
Variable::Variable(const char& rhs)
{
	
	*this = rhs;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns passed string value using inner operator= function
//------------------------------------------------------------------------------------------------------
Variable::Variable(const std::string& rhs)
{

	*this = rhs;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns passed integer value using inner operator= function
//------------------------------------------------------------------------------------------------------
Variable::Variable(const int& rhs)
{

	*this = rhs;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns passed float value using inner operator= function
//------------------------------------------------------------------------------------------------------
Variable::Variable(const float& rhs)
{

	*this = rhs;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns passed double value using inner operator= function
//------------------------------------------------------------------------------------------------------
Variable::Variable(const double& rhs)
{

	*this = rhs;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns variable object type
//------------------------------------------------------------------------------------------------------
Variable::VariableType Variable::GetType()
{

	return m_type;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns boolean type value
//------------------------------------------------------------------------------------------------------
bool Variable::GetBool()
{

	return *((bool*)m_value);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns character type value
//------------------------------------------------------------------------------------------------------
char Variable::GetChar()
{

	return *((char*)m_value);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns string type value
//------------------------------------------------------------------------------------------------------
std::string Variable::GetString()
{

	return *((std::string*)m_value);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns integer type value
//------------------------------------------------------------------------------------------------------
int Variable::GetInt()
{

	return *((int*)m_value);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns float type value
//------------------------------------------------------------------------------------------------------
float Variable::GetFloat()
{

    return *((float*)m_value);
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns double type value
//------------------------------------------------------------------------------------------------------
double Variable::GetDouble()
{

	return *((double*)m_value);

}
//------------------------------------------------------------------------------------------------------
//assignment function that makes a deep copy of another variable object
//------------------------------------------------------------------------------------------------------
Variable& Variable::operator=(const Variable& rhs)
{

	//based on what data type the variable contains make
	//call to correct assignment operator to create copy
	switch (rhs.m_type)
	{
		case BOOL_TYPE   : 	{ *this = *((bool*)(rhs.m_value)); break;        }
		case CHAR_TYPE   : 	{ *this = *((char*)(rhs.m_value)); break;	     }
		case STRING_TYPE : 	{ *this = *((std::string*)(rhs.m_value)); break; }
		case INT_TYPE    :	{ *this = *((int*)(rhs.m_value)); break;	     }
		case FLOAT_TYPE  : 	{ *this = *((float*)(rhs.m_value)); break;       }
		case DOUBLE_TYPE : 	{ *this = *((double*)(rhs.m_value)); break;      }
	}

	//return a reference of the variable object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//assignment function that assigns boolean data to variable object
//------------------------------------------------------------------------------------------------------
Variable& Variable::operator=(const bool& rhs)
{

	//first delete old value
	delete m_value;

	//create new bool data on heap
	m_value = new bool;

	//assign passed data to variable
	*((bool*)m_value) = rhs;

	//assign data type
	m_type = BOOL_TYPE;

	//return a reference of the variable object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//assignment function that assigns character data to variable object
//------------------------------------------------------------------------------------------------------
Variable& Variable::operator=(const char& rhs)
{

	//first delete old value
	delete m_value;
	
	//create new character data on heap
	m_value = new char;

	//assign passed data to variable
	*((char*)m_value) = rhs;
	
	//assign data type
	m_type = CHAR_TYPE;

	//return a reference of the variable object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//assignment function that assigns string data to variable object
//------------------------------------------------------------------------------------------------------
Variable& Variable::operator=(const std::string& rhs)
{

	//first delete old value
	delete m_value;

	//create new string data on heap
	m_value = new std::string;
	
	//assign passed data to variable
	*((std::string*)m_value) = rhs;
	
	//assign data type
	m_type = STRING_TYPE;
	
	//return a reference of the variable object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//assignment function that assigns integer data to variable object
//------------------------------------------------------------------------------------------------------
Variable& Variable::operator=(const int& rhs)
{

	//first delete old value
	delete m_value;

	//create new integer data on heap
	m_value = new int;

	//assign passed data to variable
	*((int*)m_value) = rhs;

	//assign data type
	m_type = INT_TYPE;

	//return a reference of the variable object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//assignment function that assigns float data to variable object
//------------------------------------------------------------------------------------------------------
Variable& Variable::operator=(const float& rhs)
{

	//first delete old value
	delete m_value;

	//create new float data on heap
	m_value = new float;

	//assign passed data to variable
	*((float*)m_value) = rhs;

	//assign data type
	m_type = FLOAT_TYPE;

	//return a reference of the variable object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//assignment function that assigns double data to variable object
//------------------------------------------------------------------------------------------------------
Variable& Variable::operator=(const double& rhs)
{

	//first delete old value
	delete m_value;

	//create new double data on heap
	m_value = new double;

	//assign passed data to variable
	*((double*)m_value) = rhs;

	//assign data type
	m_type = DOUBLE_TYPE;

	//return a reference of the variable object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that clears old data and resets values
//------------------------------------------------------------------------------------------------------
void Variable::Clear()
{

	delete m_value;
	m_value = 0;
	m_type = NULL_TYPE;

}
//------------------------------------------------------------------------------------------------------
//function that displays variable type and value
//------------------------------------------------------------------------------------------------------
void Variable::Output()
{

	system("cls");
	std::cout << "------------------------------------" << std::endl;

	//based on variable data type output it and the cast value 
	switch (m_type)
	{
		case NULL_TYPE :
		{
			std::cout << "Variable is of type : NULL" << std::endl;
			std::cout << "Variable value is   : 0" << std::endl;
			break;
		}

		case BOOL_TYPE : 
		{ 
			std::cout << "Variable is of type : BOOL" << std::endl;
		    std::cout << "Variable value is   : " << *((bool*)m_value) << std::endl;
		    break;   
		}

		case CHAR_TYPE : 
		{  
			std::cout << "Variable is of type : CHAR" << std::endl;
			std::cout << "Variable value is   : " << *((char*)m_value) << std::endl;
			break;
		}
		
		case STRING_TYPE : 
		{
			std::cout << "Variable is of type : STRING" << std::endl;
			std::cout << "Variable value is   : " << *((std::string*)m_value) << std::endl;
			break; 
		}

		case INT_TYPE : 
		{  
			std::cout << "Variable is of type : INT" << std::endl;
			std::cout << "Variable value is   : " << *((int*)m_value) << std::endl;
			break;
		}

		case FLOAT_TYPE : 
		{  
			std::cout << "Variable is of type : FLOAT" << std::endl;
			std::cout << "Variable value is   : " << *((float*)m_value) << std::endl;
			break;
		}

		case DOUBLE_TYPE :
		{
			std::cout << "Variable is of type : DOUBLE" << std::endl;
			std::cout << "Variable value is   : " << *((double*)m_value) << std::endl;
			break;
		}

	}

	std::cout << "------------------------------------" << std::endl;

}
//------------------------------------------------------------------------------------------------------
//destructor that destoys data pointer
//------------------------------------------------------------------------------------------------------
Variable::~Variable()
{

	delete m_value;

}