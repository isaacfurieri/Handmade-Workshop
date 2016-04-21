/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2016

  -----------------------------------------------------------------------------------------------

- This class represents the three main transformations, namely translation, rotation and scale. 
  It consists of three enum values that will be used when rotation is needed - ie either around 
  the X, Y or Z axis. Each transformation made will add onto the previous one. This means that
  until the inner Matrix object is reset to the identity, the transformations will accumulate.

- For each transformation there is a function that will be called to set the values accordingly. 
  The class supports both 2D and 3D transformations, as each transformation routine has a default
  parameter for Z. 

*/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix4D.h"

class Transform
{

public:

	enum AXIS_TYPE { X_AXIS, Y_AXIS, Z_AXIS };

public :

	Matrix4D& GetMatrix();

public :

	void Scale(float x, float y, float z = 0);
	void Translate(float x, float y, float z = 0);
	void Rotate(float angle, AXIS_TYPE axisType = Z_AXIS);
	
private :

	Matrix4D m_matrix;

};

#endif