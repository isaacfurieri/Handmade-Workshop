/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : March 2016

  -----------------------------------------------------------------------------------------------

- This is a templatized class that encapsulates a 4D Vector consisting of components X, Y, Z and W. 
  The vector objects created with this class cannot be used to represent anything in 3D space. 
  Instead, this vector class is used to represent numbers in groups of four, for example for use in
  quaternions, matrices and other complex number representations. These numbers can be combined with
  other vectors with the use of arithemetic and helper functions.

- There is a forward declaration for the 2D and 3D vector versions so that the compiler is aware of
  them for the sake of the conversion functions. There is no need to actually include the header
  files for the Vector2D and Vector3D because they are templates and only need to be included when
  they are put to use. Therefore before any of the conversion routines are called, their respective
  header files will need to be included.

- The XYZW values are all public so that it is easier to access them individually in the client code.
  They can be individually assigned values or assigned in one go using the Set() routine.

- The arithmetic operators that represent addition, subtraction, multiplication and division have been
  overloaded to allow for vectors to support basic mathematic functionality. The member functions support
  two vectors to be used or a vector and a scalar value to be used, ie V1 * V2 or V1 + 2.34. The global
  functions support a scalar value and a vector to be used ie 2.3 + V1. These global functions could be
  static, but then the client code will look somewhat horrific

- The class contains a variety of helper functions to calculate things such as length, squared length, 
  dot product and normalising. The Normalise() function will return a new Vector4D object instead of 
  changing the calling object. This is better so that the old vector can still be used and the new 
  normalised version is independent of it.

- The Output function is for debug purposes and displays the XYZW values on the console window. Precision
  can be set here because sometimes displaying a very large or very small floating point number will 
  result in a number in scientific format. To overcome this the precision can be set so that the value
  will be displayed in floating point notation and will set the precision to the value specified. 

*/

#ifndef VECTOR_4D_H
#define VECTOR_4D_H

#include <iomanip>
#include <iostream>
#include <math.h>

template <class T> class Vector2D;
template <class T> class Vector3D;

template <class T> class Vector4D
{

public:

	Vector4D(T x = 0, T y = 0, T z = 0, T w = 0);

public:

	Vector4D<T>& operator=(const T rhs);
	
	Vector4D<T> operator+(const Vector4D<T>& rhs) const;
	Vector4D<T> operator+(const T rhs);
	Vector4D<T>& operator+=(const Vector4D<T>& rhs);
	Vector4D<T>& operator+=(const T rhs);

	Vector4D<T> operator-(const Vector4D<T>& rhs) const;
	Vector4D<T> operator-(const T rhs);
	Vector4D<T>& operator-=(const Vector4D<T>& rhs);
	Vector4D<T>& operator-=(const T rhs);

	Vector4D<T> operator*(const Vector4D<T>& rhs) const;
	Vector4D<T> operator*(const T rhs);
	Vector4D<T>& operator*=(const Vector4D<T>& rhs);
	Vector4D<T>& operator*=(const T rhs);

	Vector4D<T> operator/(const Vector4D<T>& rhs) const;
	Vector4D<T> operator/(const T rhs);
	Vector4D<T>& operator/=(const Vector4D<T>& rhs);
	Vector4D<T>& operator/=(const T rhs);

	Vector4D<T>& operator++();
	Vector4D<T> operator++(int);
	Vector4D<T>& operator--();
	Vector4D<T> operator--(int);

	Vector4D<T> operator-();

	bool operator==(const Vector4D<T>& rhs);
	bool operator==(const T rhs);
	bool operator!=(const Vector4D<T>& rhs);
	bool operator!=(const T rhs);
	
	bool operator<(const Vector4D<T>& rhs);
	bool operator<(const T rhs);
	bool operator<=(const Vector4D<T>& rhs);
	bool operator<=(const T rhs);

	bool operator>(const Vector4D<T>& rhs);
	bool operator>(const T rhs);
	bool operator>=(const Vector4D<T>& rhs);
	bool operator>=(const T rhs);

public:

	T Length();
	T LengthSquared();
	T DotProduct(const Vector4D<T>& secondVector) const;

	void Set(T x, T y, T z, T w);
	
	Vector4D<T> Normalise();
	Vector2D<T> Convert2D() const;
	Vector3D<T> Convert3D() const;

public:

	void Output(unsigned int precision = 0);

public:

	T X;
	T Y;
	T Z;
	T W;

};

//------------------------------------------------------------------------------------------------------
//constructor that assigns X, Y, Z and W values
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>::Vector4D(T x, T y, T z, T w)
{

	X = x;
	Y = y;
	Z = z;
	W = w;

}
//------------------------------------------------------------------------------------------------------
//function that assigns a value to a Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator=(const T rhs)
{

	X = rhs;
	Y = rhs;
	Z = rhs;
	W = rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that adds a Vector4D object to a value using the + member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> operator+(const T lhs, Vector4D<T>& rhs)
{

	return rhs + lhs;

}
//------------------------------------------------------------------------------------------------------
//function that adds two Vector4D objects using the += member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator+(const Vector4D<T>& rhs) const
{

	Vector4D<T> result(*this);
	return (result += rhs);

}
//------------------------------------------------------------------------------------------------------
//function that adds a value to a Vector4D object using the += member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator+(const T rhs)
{

	Vector4D<T> result(*this);
	return (result += rhs);

}
//------------------------------------------------------------------------------------------------------
//function that adds and assigns a Vector4D to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator+=(const Vector4D<T>& rhs)
{

	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	W += rhs.W;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that adds and assigns a value to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator+=(const T rhs)
{

	X += rhs;
	Y += rhs;
	Z += rhs;
	W += rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that subtracts a Vector4D object from a value using the - member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> operator-(const T lhs, Vector4D<T>& rhs)
{

	//create a temporary vector based on lhs passed value and then use -= function to subtract
	//this is because subtraction differs between lhs - rhs and rhs - lhs 
	//this method is the most efficient way to overcome this issue
	Vector4D<T> result(lhs, lhs, lhs, lhs);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts two Vector4D objects using the -= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator-(const Vector4D<T>& rhs) const
{

	Vector4D<T> result(*this);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts a value from a Vector4D object using the -= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator-(const T rhs)
{

	Vector4D<T> result(*this);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts and assigns a Vector4D to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator-=(const Vector4D<T>& rhs)
{

	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	W -= rhs.W;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that subtracts and assigns a value to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator-=(const T rhs)
{

	X -= rhs;
	Y -= rhs;
	Z -= rhs;
	W -= rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a value by a Vector4D object using the * member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> operator*(const T lhs, Vector4D<T>& rhs)
{

	return rhs * lhs;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies two Vector4D objects using the *= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator*(const Vector4D<T>& rhs) const
{

	Vector4D<T> result(*this);
	return (result *= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a Vector4D object by a value using the *= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator*(const T rhs)
{

	Vector4D<T> result(*this);
	return (result *= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that multiplies and assigns a Vector4D to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator*=(const Vector4D<T>& rhs)
{

	X *= rhs.X;
	Y *= rhs.Y;
	Z *= rhs.Z;
	W *= rhs.W;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies and assigns a value to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator*=(const T rhs)
{

	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	W *= rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that divides a value by a Vector4D object using the /= member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> operator/(const T lhs, Vector4D<T>& rhs)
{

	//create a temporary vector based on lhs passed value and then use /= function to divide
	//this is because division differs between lhs / rhs and rhs / lhs 
	//this method is the most efficient way to overcome this issue
	Vector4D<T> result(lhs, lhs, lhs, lhs);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides two Vector4D objects using the /= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator/(const Vector4D<T>& rhs) const
{

	Vector4D<T> result(*this);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides a Vector4D object by a value using the /= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator/(const T rhs)
{

	Vector4D<T> result(*this);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides and assigns a Vector4D to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator/=(const Vector4D<T>& rhs)
{

	//first make sure that we do not divide by 0!
	if (rhs.X != 0) X /= rhs.X;
	if (rhs.Y != 0) Y /= rhs.Y;
	if (rhs.Z != 0) Z /= rhs.Z;
	if (rhs.W != 0) W /= rhs.W;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that divides and assigns a value to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator/=(const T rhs)
{

	//first make sure that we do not divide by 0!
	if (rhs != 0) X /= rhs;
	if (rhs != 0) Y /= rhs;
	if (rhs != 0) Z /= rhs;
	if (rhs != 0) W /= rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that increments a Vector4D object using the prefix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator++()
{

	X++;
	Y++;
	Z++;
	W++;

	//return a reference of the vector object because
	//the object is changed before being used
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that increments a Vector4D object using the postfix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator++(int)
{

	//first create a temporary vector before incrementing
	Vector4D<T> temp(*this);
	++(*this);

	//return the temporary vector instead of the incremented one
	//because the old object needs to be used before the new one 
	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that decrements a Vector4D object using the prefix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T>& Vector4D<T>::operator--()
{

	X--;
	Y--;
	Z--;
	W--;

	//return a reference of the vector object because
	//the object is changed before being used
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that decrements a Vector4D object using the postfix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator--(int)
{

	//first create a temporary vector before decrementing
	Vector4D<T> temp(*this);
	--(*this);

	//return the temporary vector instead of the decremented one
	//because the old object needs to be used before the new one 
	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that negates a Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::operator-()
{

	Vector4D<T> temp(-X, -Y, -Z, -W);

	//make sure there is no -0
	if (temp.X == -0) temp.X = 0;
	if (temp.Y == -0) temp.Y = 0;
	if (temp.Z == -0) temp.Z = 0;
	if (temp.W == -0) temp.W = 0;

	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that determines if two Vector4D objects are identical
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator==(const Vector4D<T>& rhs)
{

	return (X == rhs.X && Y == rhs.Y && Z == rhs.Z && W == rhs.W);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is identical to a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator==(const T rhs)
{

	return (X == rhs && Y == rhs && Z == rhs && W == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if two Vector4D objects are unequal using the inverse of the == function
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator!=(const Vector4D<T>& rhs)
{

	return (!(*this == rhs));

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is unequal to a value using the inv. of the == function
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator!=(const T rhs)
{

	return (!(*this == rhs));

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is smaller than another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator<(const Vector4D<T>& rhs)
{

	return (X < rhs.X && Y < rhs.Y && Z < rhs.Z && W < rhs.W);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is smaller than a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator<(const T rhs)
{

	return (X < rhs && Y < rhs && Z < rhs && W < rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is smaller or equal to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator<=(const Vector4D<T>& rhs)
{

	//use the < and == member functions and return the result
	return (*this < rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is smaller or equal to a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator<=(const T rhs)
{

	//use the < and == member functions and return the result
	return (*this < rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is bigger than another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator>(const Vector4D<T>& rhs)
{

	return (X > rhs.X && Y > rhs.Y && Z > rhs.Z && W > rhs.W);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is smaller than a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator>(const T rhs)
{

	return (X > rhs && Y > rhs && Z > rhs && W > rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is bigger than or equal to another Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator>=(const Vector4D<T>& rhs)
{

	//use the > and == member functions and return the result
	return (*this > rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector4D object is bigger than or equal to a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector4D<T>::operator>=(const T rhs)
{

	//use the > and == member functions and return the result
	return (*this > rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that calculates the length of a Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> T Vector4D<T>::Length()
{

	return (T)(sqrt(LengthSquared()));

}
//------------------------------------------------------------------------------------------------------
//function that calculates the squared length of a Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> T Vector4D<T>::LengthSquared()
{

	return (X * X + Y * Y + Z * Z + W * W);

}
//------------------------------------------------------------------------------------------------------
//function that calculates the dot product of two Vector4D objects
//------------------------------------------------------------------------------------------------------
template <class T> T Vector4D<T>::DotProduct(const Vector4D<T>& secondVector) const
{

	return ((X * secondVector.X) + (Y * secondVector.Y) + (Z * secondVector.Z) + (W * secondVector.W));

}
//------------------------------------------------------------------------------------------------------
//function that assigns all components of Vector4D object at once
//------------------------------------------------------------------------------------------------------
template <class T> void Vector4D<T>::Set(T x, T y, T z, T w)
{

	X = x;
	Y = y;
	Z = z;
	W = w;

}
//------------------------------------------------------------------------------------------------------
//function that normalises a Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector4D<T>::Normalise()
{

	Vector4D<T> temp(*this);

	T length = temp.Length();

	temp.X /= length;
	temp.Y /= length;
	temp.Z /= length;
	temp.W /= length;

	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that converts the Vector4D object to a Vector2D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector2D<T> Vector4D<T>::Convert2D() const
{

	return Vector2D<T>(X, Y);

}
//------------------------------------------------------------------------------------------------------
//function that converts the Vector4D object to a Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector4D<T>::Convert3D() const
{

	return Vector3D<T>(X, Y, Z);

}
//------------------------------------------------------------------------------------------------------
//function that displays X, Y, Z and W values of a Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> void Vector4D<T>::Output(unsigned int precision)
{

	//if precision value is passed then set display mode 
	//to floating point notation and set the precision accordingly
	if (precision > 0)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(precision);
	}

	std::cout << "X = " << X << " <<>> " << "Y = " << Y << " <<>> " 
		      << "Z = " << Z << " <<>> " << "W = " << W << std::endl;

}

#endif