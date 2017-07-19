#include <iomanip>
#include <iostream>
#include <math.h>
#include "Quaternion.h"

//------------------------------------------------------------------------------------------------------
//constructor that creates Quaternion object and makes it an identity quaternion
//------------------------------------------------------------------------------------------------------
Quaternion::Quaternion()
{

	*this = IDENTITY;

}
//------------------------------------------------------------------------------------------------------
//second constructor that creates Quaternion object based on angle and axis passed
//------------------------------------------------------------------------------------------------------
Quaternion::Quaternion(double angle, double x, double y, double z)
{

	//call the internal function to do all the work
	SetAngleAxis(angle, x, y, z);

}
//------------------------------------------------------------------------------------------------------
//third constructor that creates Quaternion object based on three Euler angles passed
//------------------------------------------------------------------------------------------------------
Quaternion::Quaternion(double angleX, double angleY, double angleZ)
{

	//call the internal function to do all the work
	SetEulerAngles(angleX, angleY, angleZ);

}
//------------------------------------------------------------------------------------------------------
//fourth constructor that creates Quaternion object based on quaternion enum type passed
//------------------------------------------------------------------------------------------------------
Quaternion::Quaternion(QuaternionType quaternionType)
{

	switch (quaternionType)
	{
		case IDENTITY: { W = 1; X = 0; Y = 0; Z = 0; break; }
	}

}
//------------------------------------------------------------------------------------------------------
//getter function that returns the angle portion of the Quaternion object
//------------------------------------------------------------------------------------------------------
double Quaternion::GetAngle()
{

	//calculate the angle using a formula based on W, and return it in degrees
	return acos(W) * 2.0 / 3.14159265359 * 180.0;

}
//------------------------------------------------------------------------------------------------------
//getter function that sets the Matrix4D object accordingly and returns it
//------------------------------------------------------------------------------------------------------
glm::mat4& Quaternion::GetMatrix()
{

	m_matrix[0][0] = (float)(1.0f - 2.0f * (Y * Y + Z * Z));
	m_matrix[0][1] = (float)(2.0f * (X * Y + Z * W));
	m_matrix[0][2] = (float)(2.0f * (X * Z - Y * W));
	m_matrix[0][3] = 0.0f;

	m_matrix[1][0] = (float)(2.0f * (X * Y - Z * W));
	m_matrix[1][1] = (float)(1.0f - 2.0f * (X * X + Z * Z));
	m_matrix[1][2] = (float)(2.0f * (Z * Y + X * W));
	m_matrix[1][3] = 0.0f;

	m_matrix[2][0] = (float)(2.0f * (X * Z + Y * W));
	m_matrix[2][1] = (float)(2.0f * (Y * Z - X * W));
	m_matrix[2][2] = (float)(1.0f - 2.0f * (X * X + Y * Y));
	m_matrix[2][3] = 0.0f;

	m_matrix[3][0] = 0.0f;
	m_matrix[3][1] = 0.0f;
	m_matrix[3][2] = 0.0f;
	m_matrix[3][3] = 1.0f;

	return m_matrix;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns the axis portion of the Quaternion object
//------------------------------------------------------------------------------------------------------
glm::vec3 Quaternion::GetAxis()
{

	//first create a temporary vector based on XYZ components 
	//of quaternion and then return a normalised version of that
	glm::vec3 temp(X, Y, Z);
	return glm::normalize(temp);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns Quaternion object based on angle and axis passed
//------------------------------------------------------------------------------------------------------
void Quaternion::SetRotation(double angle, double x, double y, double z)
{

	//call the internal function to do all the work
	SetAngleAxis(angle, x, y, z);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns Quaternion object based on three Euler angles passed
//------------------------------------------------------------------------------------------------------
void Quaternion::SetRotation(double angleX, double angleY, double angleZ)
{

	//call the internal function to do all the work
	SetEulerAngles(angleX, angleY, angleZ);

}
//------------------------------------------------------------------------------------------------------
//function that assigns a value to a Quaternion object based on quaternion enum type passed
//------------------------------------------------------------------------------------------------------
Quaternion& Quaternion::operator=(const QuaternionType rhs)
{

	switch (rhs)
	{
		case IDENTITY: { W = 1; X = 0; Y = 0; Z = 0; break; }
	}

	//return a reference of the quaternion object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies two Quaternions objects together
//------------------------------------------------------------------------------------------------------	
Quaternion Quaternion::operator*(const Quaternion& rhs)
{

	Quaternion result;
	
	result.W = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
	result.X = W * rhs.X + X * rhs.W + Y * rhs.Z - Z * rhs.Y;
	result.Y = W * rhs.Y + Y * rhs.W + Z * rhs.X - X * rhs.Z;
	result.Z = W * rhs.Z + Z * rhs.W + X * rhs.Y - Y * rhs.X;

	return result;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a Quaternion object by a Vector3D object
//------------------------------------------------------------------------------------------------------
glm::vec3 Quaternion::operator*(const glm::vec3& rhs)
{

	//create a temporary vector and store the passed vector in there
	glm::vec3 temp = rhs;
	
	//if temp vector is null, return it because
	//a null vector is useless to use
	if(temp == glm::vec3(0.0f))
	{
		return temp;
	}

	//otherwise normalise it first before use
	//it is best to work with normalised vector values
	//so that there are no shearing artefacts
	temp = glm::normalize(temp);

	//create two quaternion objects, the first one is for disguising 
	//the passed vector as a quaternion object. The second one is used
	//for representing the accumulated rotations. 
	Quaternion vectorQuaternion;
	Quaternion resultQuaternion;

	//assign the XYZ components of the passed vector and set the W to 0
	vectorQuaternion.W = 0.0f;
	vectorQuaternion.X = temp.x;
	vectorQuaternion.Y = temp.y;
	vectorQuaternion.Z = temp.z;
			
	//calculate the result quaternion using a formula
	resultQuaternion = (*this) * vectorQuaternion * Conjugate();

	//create a new vector by changing the resulting quaternion back
	//to a normalised vector representation, and return that
	return(glm::vec3(resultQuaternion.X, resultQuaternion.Y, resultQuaternion.Z));

}
//------------------------------------------------------------------------------------------------------
//function that calculates the length of a Quaternion object
//------------------------------------------------------------------------------------------------------
double Quaternion::Length()
{

	return sqrt(LengthSquared());

}
//------------------------------------------------------------------------------------------------------
//function that calculates the squared length of a Quaternion object
//------------------------------------------------------------------------------------------------------
double Quaternion::LengthSquared()
{

	return (W * W + X * X + Y * Y + Z * Z);

}
//------------------------------------------------------------------------------------------------------
//function that inverts only the XYZ components of Quaternion object
//------------------------------------------------------------------------------------------------------
Quaternion Quaternion::Conjugate()
{

	Quaternion temp;

	temp.W = W;
	temp.X = -X;
	temp.Y = -Y;
	temp.Z = -Z;

	return temp;

}
//------------------------------------------------------------------------------------------------------
//function that normalises Quaternion object
//------------------------------------------------------------------------------------------------------
Quaternion& Quaternion::Normalise()
{

	double length = Length();

	W /= length;
	X /= length;
	Y /= length;
	Z /= length;

	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that displays W, X, Y and Z values of Quaternion object
//DEBUG purposes only
//------------------------------------------------------------------------------------------------------
void Quaternion::Output(unsigned int precision)
{

	//if precision value is passed then set display mode 
	//to floating point notation and set the precision accordingly
	if (precision > 0)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(precision);
	}

	std::cout << "W = " << W << " <<>> " << "X = " << X << " <<>> " 
		      << "Y = " << Y << " <<>> " << "Z = " << Z << std::endl;

}
//------------------------------------------------------------------------------------------------------
//internal function that calculates Quaternion object based on angle and axis passed
//------------------------------------------------------------------------------------------------------
void Quaternion::SetAngleAxis(double angle, double x, double y, double z)
{

	//first convert passed angle to radian value
	double radian = angle / 180.0 * 3.14159265359;

	//create variables to store calculations for easier coding 
	double sinThetaOverTwo = sin(radian / 2.0f);
	double cosThetaOverTwo = cos(radian / 2.0f);

	//create temporary vector based on XYZ values passed and 
	//normalise it so that the resulting quaternion will be normalised
	glm::vec3 temp(x, y, z);
	temp = glm::normalize(temp);

	//assign WXYZ components using a formula and temporary vector
	W = cosThetaOverTwo;
	X = temp.x * sinThetaOverTwo;
	Y = temp.y * sinThetaOverTwo;
	Z = temp.z * sinThetaOverTwo;

}
//------------------------------------------------------------------------------------------------------
//internal function that calculates Quaternion object based on three Euler angles passed
//------------------------------------------------------------------------------------------------------
void Quaternion::SetEulerAngles(double angleX, double angleY, double angleZ)
{

	//first convert passed Euler angles to radian values
	double radianX = angleX / 180.0 * 3.14159265359;
	double radianY = angleY / 180.0 * 3.14159265359;
	double radianZ = angleZ / 180.0 * 3.14159265359;

	//create variables to store calculations for easier coding 
	double sinX = sin(radianX / 2.0);
	double sinY = sin(radianY / 2.0);
	double sinZ = sin(radianZ / 2.0);

	double cosX = cos(radianX / 2.0);
	double cosY = cos(radianY / 2.0);
	double cosZ = cos(radianZ / 2.0);

	//assign WXYZ components using a formula 
	W = cosZ * cosX * cosY + sinZ * sinX * sinY;
	X = cosZ * sinX * cosY + sinZ * cosX * sinY;
	Y = cosZ * cosX * sinY - sinZ * sinX * cosY;
	Z = sinZ * cosX * cosY - cosZ * sinX * sinY;

}