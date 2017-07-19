/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This is a class that encapsulates a Quaternion object consisting of components W, X, Y and Z. 
  This object will represent rotations and is more flexible to use than dealing with Euler angles. 
  The class could also be templatized, however this is not really worth it, as quaternions will 
  mostly be implemented using floating point rotation values. The type double is used throughout 
  the class to represent values using high precision.
  
- The WXYZ values are all public so that it is easier to access them individually in the client 
  code. The only other private member is the internal 4x4 matrix object which is used when wanting 
  to represent the quaternion rotation in a matrix format. The GetMatrix() routine will return the 
  quaternion as a Matrix4D object.

- Internally the quaternion object works in radians, because of the C++ sin and cos functions, 
  but externally degrees are sent to the object and returned back to the calling code.

- Four constructors exist, the first one without any parameters, to avoid ambiguity with the second 
  constructor when creating the object. The second and third constructor have no default values, 
  so that there is also no ambiguity. The second and third constructor convert the passed degrees 
  to radians which stay like that throughout, while the first and fourth ones assign the quaternion 
  to the identity.

- The multiplication operator has been overloaded to allow for basic multiplication with two 
  quaternion objects and a quaternion and a vector. Therefore Q * Q and Q * V are supported, however
  multiplying a vector by a quaternion is not supported, ie V * Q will not work. For now, the 
  *= operator has not been overloaded.

- There is a Length() and LengthSquared() function. They are more for internal use but are also 
  useful for outside use as debug functions, ie to check if a quaternion is unit length. Generally
  the length of a quaternion is not really ever required, because they always will be unit length 
  in order to work properly. The Normalise() function will change the calling Quaternion object and 
  return that instead of creating a new Quaternion object. This is because almost always a normalised
  version of a quaternion will be needed and used. This is not the case in the Vector classes.

- The Output() function is for debug purposes and displays the WXYZ values on the console window.
  Precision can be set here because sometimes displaying a very large or very small floating point 
  number will result in a number in scientific format. To overcome this the precision can be set so 
  that the value will be displayed in floating point notation and will set the precision to the value 
  specified.

- Some of the code is based on code snippets from SAE London and from the website :
  http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation

*/

#ifndef QUATERNION_H
#define QUATERNION_H

#include <glm.hpp>

class Quaternion
{

public :

	enum QuaternionType { IDENTITY };

public :

	Quaternion(); 
	Quaternion(double angle, double x, double y, double z); 
	Quaternion(double angleX, double angleY, double angleZ); 
	Quaternion(QuaternionType quaternionType);

public :

	double GetAngle(); 
	glm::mat4& GetMatrix();
	glm::vec3 GetAxis();
	
public :

	void SetRotation(double angle, double x, double y, double z);
	void SetRotation(double angleX, double angleY, double angleZ);
	
public:

	Quaternion& operator=(const QuaternionType rhs);
	Quaternion operator*(const Quaternion& rhs); 
	glm::vec3 operator*(const glm::vec3& rhs); 

public :

	double Length(); 
	double LengthSquared(); 
	Quaternion Conjugate(); 
	Quaternion& Normalise(); 

public:

	void Output(unsigned int precision = 0);

private:

	void SetAngleAxis(double angle, double x, double y, double z);    
	void SetEulerAngles(double angleX, double angleY, double angleZ); 

public :

	double W;
	double X;
	double Y;
	double Z;

private :

	glm::mat4 m_matrix;
	
};

#endif