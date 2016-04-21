#include <math.h>
#include "Transform.h"

//------------------------------------------------------------------------------------------------------
//getter function that returns internal matrix object  
//------------------------------------------------------------------------------------------------------
Matrix4D& Transform::GetMatrix()
{

	return m_matrix;

}
//------------------------------------------------------------------------------------------------------
//function that sets the scale values 
//------------------------------------------------------------------------------------------------------
void Transform::Scale(float x, float y, float z)
{

	//first create a temporary matrix to store the scale value 
	Matrix4D tempMatrix;

	//assign the XYZ scale values along the matrix diagonal 
	tempMatrix[0] = x;
	tempMatrix[5] = y;
	tempMatrix[10] = z;

	//add scale to existing inner matrix
	m_matrix * tempMatrix;

}
//------------------------------------------------------------------------------------------------------
//function that sets the translation values 
//------------------------------------------------------------------------------------------------------
void Transform::Translate(float x, float y, float z)
{

	//first create a temporary matrix to store the translation value 
	Matrix4D tempMatrix;

	//assign the XYZ translation values in the top right of the matrix  
	tempMatrix[12] = x;
	tempMatrix[13] = y;
	tempMatrix[14] = z;

	//add translation to existing inner matrix
	m_matrix * tempMatrix;

}
//------------------------------------------------------------------------------------------------------
//function that sets the rotation values 
//------------------------------------------------------------------------------------------------------
void Transform::Rotate(float angle, AXIS_TYPE axisType)
{

	//first create a temporary matrix to store the rotation value 
	Matrix4D tempMatrix;

	//first convert the passed angle into a radian value
	//so that the sin and cos functions can use it
	double radian = angle / 180.0 * 3.14159265359;

	//based on which axis the rotation needs to be around
	//use cos and sin functions with the radian angle to 
	//calculate values and assign them to different parts of the matrix
	switch (axisType)
	{

		case X_AXIS:
		{
			tempMatrix[5] = (float)cos(radian);
			tempMatrix[6] = (float)sin(radian);
			tempMatrix[9] = (float)-sin(radian);
			tempMatrix[10] = (float)cos(radian);
			break;
		}

		case Y_AXIS:
		{
			tempMatrix[0] = (float)cos(radian);
			tempMatrix[2] = (float)-sin(radian);
			tempMatrix[8] = (float)sin(radian);
			tempMatrix[10] = (float)cos(radian);
			break;
		}

		case Z_AXIS:
		{
			tempMatrix[0] = (float)cos(radian);
			tempMatrix[1] = (float)sin(radian);
			tempMatrix[4] = (float)-sin(radian);
			tempMatrix[5] = (float)cos(radian);
			break;
		}

	}

	//add rotation to existing inner matrix
	m_matrix * tempMatrix;

}