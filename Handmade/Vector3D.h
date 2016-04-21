/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : March 2016

  -----------------------------------------------------------------------------------------------

- This is a templatized class that encapsulates a 3D Vector consisting of components X, Y and Z. 
  The vector objects created with this class can be used to represent points in 3D space, directions
  or basic numeric values, and can be combined with other vectors with the use of arithemetic and 
  helper functions.

- There is a forward declaration for the 2D and 4D vector versions so that the compiler is aware of
  them for the sake of the conversion functions. There is no need to actually include the header
  files for the Vector2D and Vector4D because they are templates and only need to be included when
  they are put to use. Therefore before any of the conversion routines are called, their respective
  header files will need to be included.

- The XYZ values are all public so that it is easier to access them individually in the client code.
  They can be individually assigned values or assigned in one go using the Set() routine.

- An enumeration of vector values enables basic directional vectors to be created and used. The other
  enumeration allows for either XYZ axis to be used in angle to vector conversion.

- Two static functions help to create a vector using an angle passed, and determine linear interpolation
  between two positions. They are static because they are special routines that belong to the Vector3D
  object instead of an instance, and they can be called without first instantiating a Vector3D object. 
  Both routines work solely with double types because angles and lerping work best with high precision 
  values. The Lerp() function uses a formula that works with normalised delta values. It will take in 
  two vectors and produce a third resulting vector, because the result needs to be separate from the 
  input, unlike the way the Color class handles lerping. These two functions could also be global, but 
  instead they are static so that they remain global but are part of the class.

- The arithmetic operators that represent addition, subtraction, multiplication and division have been 
  overloaded to allow for vectors to support basic mathematic functionality. The member functions support
  two vectors to be used or a vector and a scalar value to be used, ie V1 * V2 or V1 + 2.34. The global
  functions support a scalar value and a vector to be used ie 2.3 + V1. These global functions could be
  static, but then the client code will look somewhat horrific

- The class contains a variety of helper functions to calculate things such as length, distance, dot 
  product and cross product, amongst other things. A routine for projecting vectors was considered, 
  but it became more effort than it's worth. Instead vector projection can be easily calculated in the 
  client code. The Normalise() function will return a new Vector3D object instead of changing the calling
  object. This is better so that the old vector can still be used and the new normalised version is 
  independent of it.

- The Angle() function calculates the angle between two vectors. It can be called using any Vector3D type
  created, but it will first convert the calling and passed Vector3D object into a double type. The 
  function will also return a double type. This is because internally the calculations produce floating 
  point values and for the sake of maintaining precision they need to work with and return high precision
  double type objects. For instance if a Vector3D<int> is passed, instead of values being truncated and 
  producing an inacurate angle value, the converted Vector3D<double> object will instead produce an 
  accurate angle.

- The Output() function is for debug purposes and displays the XYZ values on the console window. Precision
  can be set here because sometimes displaying a very large or very small floating point number will 
  result in a number in scientific format. To overcome this the precision can be set so that the value
  will be displayed in floating point notation and will set the precision to the value specified. 

- Some parameters are const qualified and others not. The ones that are not const are so because they 
  internally call non-const functions, which causes a conflict. This is not neccessarily a good coding 
  practise, and will be amended some other time.

*/

#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <iomanip>
#include <iostream>
#include <math.h>

template <class T> class Vector2D;
template <class T> class Vector4D;

template <class T> class Vector3D
{

public:

	enum AxisType   { X_AXIS, Y_AXIS, Z_AXIS };
	enum VectorType { ZERO, LEFT, RIGHT, UP, DOWN, FORWARD, BACKWARD };

public:

	static Vector3D<double> AngleToVector(double angle, double size = 1.0, AxisType axis = Z_AXIS);
	static Vector3D<double> Lerp(Vector3D<double>& firstVector, 
		                         Vector3D<double>& secondVector, double delta, double epsilon = 0.01);
	
public :

	Vector3D(T x = 0, T y = 0, T z = 0);
	Vector3D(VectorType vectorType);

public :

	Vector3D<T>& operator=(const T rhs);
	Vector3D<T>& operator=(const VectorType rhs);

	Vector3D<T> operator+(const Vector3D<T>& rhs) const;
	Vector3D<T> operator+(const T rhs);
	Vector3D<T>& operator+=(const Vector3D<T>& rhs);
	Vector3D<T>& operator+=(const T rhs);

	Vector3D<T> operator-(const Vector3D<T>& rhs) const;
	Vector3D<T> operator-(const T rhs);
	Vector3D<T>& operator-=(const Vector3D<T>& rhs);
	Vector3D<T>& operator-=(const T rhs);

	Vector3D<T> operator*(const Vector3D<T>& rhs) const;
	Vector3D<T> operator*(const T rhs);
	Vector3D<T>& operator*=(const Vector3D<T>& rhs);
	Vector3D<T>& operator*=(const T rhs);

	Vector3D<T> operator/(const Vector3D<T>& rhs) const;
	Vector3D<T> operator/(const T rhs);
	Vector3D<T>& operator/=(const Vector3D<T>& rhs);
	Vector3D<T>& operator/=(const T rhs);

	Vector3D<T>& operator++();
	Vector3D<T> operator++(int);
	Vector3D<T>& operator--();
	Vector3D<T> operator--(int);

	Vector3D<T> operator-();

	bool operator==(const Vector3D<T>& rhs);
	bool operator==(const T rhs);
	bool operator==(const VectorType rhs);
	
	bool operator!=(const Vector3D<T>& rhs);
	bool operator!=(const T rhs);
	bool operator!=(const VectorType rhs);

	bool operator<(const Vector3D<T>& rhs);
	bool operator<(const T rhs);
	bool operator<=(const Vector3D<T>& rhs);
	bool operator<=(const T rhs);

	bool operator>(const Vector3D<T>& rhs);
	bool operator>(const T rhs);
	bool operator>=(const Vector3D<T>& rhs);
	bool operator>=(const T rhs);

public :

	T Length();
	T LengthSquared();
	T Distance(const Vector3D<T>& secondVector);
	T DotProduct(const Vector3D<T>& secondVector) const;

	void Set(T x, T y, T z);
	double Angle(Vector3D<T>& secondVector);
		
	Vector3D<T> Normalise();
	Vector2D<T> Convert2D() const;
	Vector4D<T> Convert4D() const;
	Vector3D<T> CrossProduct(const Vector3D<T>& secondVector) const;

public :

	void Output(unsigned int precision = 0);

public :

	T X;
	T Y;
	T Z;

};

//------------------------------------------------------------------------------------------------------
//STATIC function that creates a Vector3D object based on angle, size and axis passed
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<double> Vector3D<T>::AngleToVector(double angle, double size, AxisType axis)
{

	//create a specific double type vector 
	//which will be the resulting vector to send back
	Vector3D<double> result;

	//first convert the passed angle into a radian value
	//so that the sin and cos functions can use it
	double radian = angle / 180.0 * 3.14159265359;

	//based on which axis value has been passed, calculate the cos and sin
	//cos and sin of the passed angle calculate the respective x and y positions
	//of the result vector in 3D space. However these positions are in effect 2D 
	//positions on a particular plane, either X, Y or Z. Based on which plane we
	//want to calculate x and y, assign the result of the other two components accordingly
	switch (axis)
	{

		//the x axis is the plane that rotates around it. That means that
		//the 2D Z and Y components are assigned their cos and sin results.
		//Z is multiplied by negative 1 so that the angle gets larger from
		//the negative Z to the positive Z axis
		case X_AXIS:
		{
			result.Z = cos(radian) * -1;
			result.Y = sin(radian);
			break;
		}

		//the y axis is the plane that rotates around it. That means that
		//the 2D X and Z components are assigned their cos and sin results.
		//Z is multiplied by negative 1 so that the angle gets larger from
		//the negative Z to the positive Z axis
		case Y_AXIS:
		{
			result.X = cos(radian);
			result.Z = sin(radian) * -1;
			break;
		}

		//the z axis is the plane that rotates around it. That means that
		//the 2D X and Y components are assigned their cos and sin results.
		case Z_AXIS:
		{
			result.X = cos(radian);
			result.Y = sin(radian);
			break;
		}

	}

	//the resulting vector will always be normalised
	//so enlarge it based on size passed and return it
	return (result *= size);

}
//------------------------------------------------------------------------------------------------------
//STATIC function that performs linear interpolation between two Vector3D objects 
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<double> Vector3D<T>::Lerp(Vector3D<double>& firstVector,
													  Vector3D<double>& secondVector,
													  double delta, double epsilon)
{

	//use a simple algorithm to create the new lerped vector value
	Vector3D<double> result = (firstVector * (1.0 - delta)) + (secondVector * delta);

	//check if the difference between the XYZ components of the source and destination vector
	//are within the epsilon range. If they are, make them both equal. This ensures that the source
	//vector will reach the destination value as quick as the epsilon value states. The smaller the 
	//epsilon value, the longer it will take to reach the destination vector.
	if (abs(secondVector.X - result.X) <= epsilon)
	{
		result.X = secondVector.X;
	}

	if (abs(secondVector.Y - result.Y) <= epsilon)
	{
		result.Y = secondVector.Y;
	}

	if (abs(secondVector.Z - result.Z) <= epsilon)
	{
		result.Z = secondVector.Z;
	}

	return result;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns X, Y and Z values
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>::Vector3D(T x, T y, T z)
{

	X = x;
	Y = y;
	Z = z;

}
//------------------------------------------------------------------------------------------------------
//second constructor that assigns X, Y and Z values based on vector enum type passed
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>::Vector3D(VectorType vectorType)
{

	//based on vector type assign the XYZ values accordingly
	//these types are best used for the common six directions
	//and a null vector
	switch (vectorType)
	{
		case ZERO:     { X = 0;  Y = 0;  Z = 0;  break; }
		case LEFT:	   { X = -1; Y = 0;  Z = 0;  break; }
		case RIGHT:	   { X = 1;  Y = 0;  Z = 0;  break; }
		case UP:	   { X = 0;  Y = 1;  Z = 0;  break; }
		case DOWN:	   { X = 0;  Y = -1; Z = 0;  break; }
		case FORWARD:  { X = 0;  Y = 0;  Z = -1; break; }
		case BACKWARD: { X = 0;  Y = 0;  Z = 1;  break; }
	}

}
//------------------------------------------------------------------------------------------------------
//function that assigns a value to a Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator=(const T rhs)
{
		
	X = rhs;
	Y = rhs;
	Z = rhs;
	
	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that assigns a value to a Vector3D object based on vector enum type passed
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator=(const VectorType rhs)
{

	//based on vector type assign the XYZ values accordingly
	switch (rhs)
	{
		case ZERO:     { X = 0;  Y = 0;  Z = 0;  break; }
		case LEFT:	   { X = -1; Y = 0;  Z = 0;  break; }
		case RIGHT:	   { X = 1;  Y = 0;  Z = 0;  break; }
		case UP:	   { X = 0;  Y = 1;  Z = 0;  break; }
		case DOWN:	   { X = 0;  Y = -1; Z = 0;  break; }
		case FORWARD:  { X = 0;  Y = 0;  Z = -1; break; }
		case BACKWARD: { X = 0;  Y = 0;  Z = 1;  break; }
	}

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that adds a Vector3D object to a value using the + member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> operator+(const T lhs, Vector3D<T>& rhs)
{

	return rhs + lhs;

}
//------------------------------------------------------------------------------------------------------
//function that adds two Vector3D objects using the += member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator+(const Vector3D<T>& rhs) const
{

	Vector3D<T> result(*this);
	return (result += rhs);

}
//------------------------------------------------------------------------------------------------------
//function that adds a value to a Vector3D object using the += member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator+(const T rhs)
{

	Vector3D<T> result(*this);
	return (result += rhs);

}
//------------------------------------------------------------------------------------------------------
//function that adds and assigns a Vector3D to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator+=(const Vector3D<T>& rhs)
{

	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that adds and assigns a value to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator+=(const T rhs)
{

	X += rhs;
	Y += rhs;
	Z += rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that subtracts a Vector3D object from a value using the - member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> operator-(const T lhs, Vector3D<T>& rhs)
{

	//create a temporary vector based on lhs passed value and then use -= function to subtract
	//this is because subtraction differs between lhs - rhs and rhs - lhs 
	//this method is the most efficient way to overcome this issue
	Vector3D<T> result(lhs, lhs, lhs);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts two Vector3D objects using the -= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator-(const Vector3D<T>& rhs) const
{

	Vector3D<T> result(*this);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts a value from a Vector3D object using the -= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator-(const T rhs)
{

	Vector3D<T> result(*this);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts and assigns a Vector3D to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator-=(const Vector3D<T>& rhs)
{

	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that subtracts and assigns a value to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator-=(const T rhs)
{

	X -= rhs;
	Y -= rhs;
	Z -= rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a value by a Vector3D object using the * member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> operator*(const T lhs, Vector3D<T>& rhs)
{

	return rhs * lhs;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies two Vector3D objects using the *= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator*(const Vector3D<T>& rhs) const
{

	Vector3D<T> result(*this);
	return (result *= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a Vector3D object by a value using the *= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator*(const T rhs)
{

	Vector3D<T> result(*this);
	return (result *= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that multiplies and assigns a Vector3D to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator*=(const Vector3D<T>& rhs)
{

	X *= rhs.X;
	Y *= rhs.Y;
	Z *= rhs.Z;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies and assigns a value to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator*=(const T rhs)
{

	X *= rhs;
	Y *= rhs;
	Z *= rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that divides a value by a Vector3D object using the /= member function (GLOBAL)
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> operator/(const T lhs, Vector3D<T>& rhs)
{

	//create a temporary vector based on lhs passed value and then use /= function to divide
	//this is because division differs between lhs / rhs and rhs / lhs 
	//this method is the most efficient way to overcome this issue
	Vector3D<T> result(lhs, lhs, lhs);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides two Vector3D objects using the /= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator/(const Vector3D<T>& rhs) const
{

	Vector3D<T> result(*this);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides a Vector3D object by a value using the /= member function
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator/(const T rhs)
{

	Vector3D<T> result(*this);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides and assigns a Vector3D to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator/=(const Vector3D<T>& rhs)
{

	//first make sure that we do not divide by 0!
	if(rhs.X != 0) X /= rhs.X;
	if(rhs.Y != 0) Y /= rhs.Y;
	if(rhs.Z != 0) Z /= rhs.Z;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that divides and assigns a value to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator/=(const T rhs)
{

	//first make sure that we do not divide by 0!
	if(rhs != 0) X /= rhs;
	if(rhs != 0) Y /= rhs;
	if(rhs != 0) Z /= rhs;

	//return a reference of the vector object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that increments a Vector3D object using the prefix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator++()
{

	X++;
	Y++;
	Z++;

	//return a reference of the vector object because
	//the object is changed before being used
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that increments a Vector3D object using the postfix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator++(int)
{

	//first create a temporary vector before incrementing
	Vector3D<T> temp(*this);
	++(*this);
	
	//return the temporary vector instead of the incremented one
	//because the old object needs to be used before the new one 
	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that decrements a Vector3D object using the prefix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T>& Vector3D<T>::operator--()
{

	X--;
	Y--;
	Z--;

	//return a reference of the vector object because
	//the object is changed before being used
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that decrements a Vector3D object using the postfix method
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator--(int)
{

	//first create a temporary vector before decrementing
	Vector3D<T> temp(*this);
	--(*this);

	//return the temporary vector instead of the decremented one
	//because the old object needs to be used before the new one 
	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that negates a Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::operator-()
{

	Vector3D<T> temp(-X, -Y, -Z);

	//make sure there is no -0
	if(temp.X == -0) temp.X = 0;
	if(temp.Y == -0) temp.Y = 0;
	if(temp.Z == -0) temp.Z = 0;

	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that determines if two Vector3D objects are identical
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator==(const Vector3D<T>& rhs)
{

	return (X == rhs.X && Y == rhs.Y && Z == rhs.Z);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is identical to a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator==(const T rhs)
{

	return (X == rhs && Y == rhs && Z == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that checks if Vector3D object is a certain value based on vector enum type passed
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator==(const VectorType rhs)
{

	//check the XYZ values individually to see if that vector type is active
	switch (rhs)
	{
		case ZERO:     { return (X == 0  && Y == 0  && Z == 0);  }
		case LEFT:	   { return (X == -1 && Y == 0  && Z == 0);  }
		case RIGHT:	   { return (X == 1  && Y == 0  && Z == 0);  }
		case UP:	   { return (X == 0  && Y == 1  && Z == 0);  }
		case DOWN:	   { return (X == 0  && Y == -1 && Z == 0);  }
		case FORWARD:  { return (X == 0  && Y == 0  && Z == -1); }
		case BACKWARD: { return (X == 0  && Y == 0  && Z == 1);  }
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that determines if two Vector3D objects are unequal using the inverse of the == function
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator!=(const Vector3D<T>& rhs)
{

	return (!(*this == rhs));

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is unequal to a value using the inv. of the == function
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator!=(const T rhs)
{

	return (!(*this == rhs));

}
//------------------------------------------------------------------------------------------------------
//function that checks if Vector3D object is not a certain value based on vector enum type passed
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator!=(const VectorType rhs)
{

	//use the == overloaded function and negate its result
	//this will oppose the == functionality and prevent repetitive code
	return !(*this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is smaller than another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator<(const Vector3D<T>& rhs)
{

	return (X < rhs.X && Y < rhs.Y && Z < rhs.Z);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is smaller than a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator<(const T rhs)
{

	return (X < rhs && Y < rhs && Z < rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is smaller or equal to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator<=(const Vector3D<T>& rhs)
{

	//use the < and == member functions and return the result
	return (*this < rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is smaller or equal to a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator<=(const T rhs)
{

	//use the < and == member functions and return the result
	return (*this < rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is bigger than another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator>(const Vector3D<T>& rhs)
{

	return (X > rhs.X && Y > rhs.Y && Z > rhs.Z);
	
}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is smaller than a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator>(const T rhs)
{

	return (X > rhs && Y > rhs && Z > rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is bigger than or equal to another Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator>=(const Vector3D<T>& rhs)
{

	//use the > and == member functions and return the result
	return (*this > rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that determines if a Vector3D object is bigger than or equal to a value
//------------------------------------------------------------------------------------------------------
template <class T> bool Vector3D<T>::operator>=(const T rhs)
{

	//use the > and == member functions and return the result
	return (*this > rhs || *this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that calculates the length of a Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> T Vector3D<T>::Length()
{

	return (T)(sqrt(LengthSquared()));

}
//------------------------------------------------------------------------------------------------------
//function that calculates the squared length of a Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> T Vector3D<T>::LengthSquared()
{

	return (X * X + Y * Y + Z * Z);

}
//------------------------------------------------------------------------------------------------------
//function that calculates the distance between two Vector3D objects
//------------------------------------------------------------------------------------------------------
template <class T> T Vector3D<T>::Distance(const Vector3D<T>& secondVector)
{

	Vector3D<T> temp(*this);
	temp -= secondVector;
	return temp.Length();

}
//------------------------------------------------------------------------------------------------------
//function that calculates the dot product of two Vector3D objects
//------------------------------------------------------------------------------------------------------
template <class T> T Vector3D<T>::DotProduct(const Vector3D<T>& secondVector) const
{

	return ((X * secondVector.X) + (Y * secondVector.Y) + (Z * secondVector.Z));

}
//------------------------------------------------------------------------------------------------------
//function that assigns all components of Vector3D object at once
//------------------------------------------------------------------------------------------------------
template <class T> void Vector3D<T>::Set(T x, T y, T z)
{

	X = x;
	Y = y;
	Z = z;

}
//------------------------------------------------------------------------------------------------------
//function that calculates the angle in degrees between two Vector3D objects
//------------------------------------------------------------------------------------------------------
template <class T> double Vector3D<T>::Angle(Vector3D<T>& secondVector)
{

	//manually cast the calling vector and passed vector object into double types
	//so that precision is maintained in the following calculation
	Vector3D<double> tempVector_1(X, Y, Z);
	Vector3D<double> tempVector_2(secondVector.X, secondVector.Y, secondVector.Z);

	//calculate the angle in radians using a formula
	double radian = acos((tempVector_1.DotProduct(tempVector_2)) /
		                 (tempVector_1.Length() * tempVector_2.Length()));

	//convert the angle to degrees before returning it
	return (radian / 3.14159265359 * 180.0);

}
//------------------------------------------------------------------------------------------------------
//function that normalises a Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::Normalise()
{

	Vector3D<T> temp(*this);

	T length = temp.Length();

	temp.X /= length;
	temp.Y /= length;
	temp.Z /= length;

	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that converts the Vector3D object to a Vector2D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector2D<T> Vector3D<T>::Convert2D() const
{

	return Vector2D<T>(X, Y);

}
//------------------------------------------------------------------------------------------------------
//function that converts the Vector3D object to a Vector4D object
//------------------------------------------------------------------------------------------------------
template <class T> Vector4D<T> Vector3D<T>::Convert4D() const
{

	return Vector4D<T>(X, Y, Z);

}
//------------------------------------------------------------------------------------------------------
//function that calculates the cross product of two Vector3D objects
//------------------------------------------------------------------------------------------------------
template <class T> Vector3D<T> Vector3D<T>::CrossProduct(const Vector3D<T>& secondVector) const
{

	Vector3D<T> crossProduct((Y * secondVector.Z - Z * secondVector.Y),
		                     (Z * secondVector.X - X * secondVector.Z),
		                     (X * secondVector.Y - Y * secondVector.X));

	return crossProduct;

}
//------------------------------------------------------------------------------------------------------
//function that displays X, Y and Z values of a Vector3D object
//------------------------------------------------------------------------------------------------------
template <class T> void Vector3D<T>::Output(unsigned int precision)
{

	//if precision value is passed then set display mode 
	//to floating point notation and set the precision accordingly
	if (precision > 0)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(precision);
	}

	std::cout << "X = " << X << " <<>> " << "Y = " << Y << " <<>> " << "Z = " << Z << std::endl;

}

#endif