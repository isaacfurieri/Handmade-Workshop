/*
 
  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : November 2015

  -----------------------------------------------------------------------------------------------

- This is a Matrix class that represents a 4x4 matrix. It is intended for use with modern
  OpenGL applications that enforce the use of self-developed matrices. It has all the 
  common matrix functionality needed to perform basic matrix arithmetic with other 
  matrices or vectors.

- The main member variable is an internal array of floats that will represent the matrix
  in column major format. Unlike the Vector or Quaternion classes I have created, the Matrix
  class' array is inaccessible, and can only be accessed via the GetMatrixArray() function,
  which returns the entire array, or the [] overloaded operator function, which returns only
  one element of the array.

- While most reference parameters are const and should be so, not all are because of conflicts
  within the functions. These can be addressed at a later stage.

- The *operator() function has been overloaded five times to allow for matrix and matrix
  multiplication, matrix and vector multiplication and matrix and float value multiplication.
  The latter routine is really there to perform matrix and float value multiplication which
  is needed inside the Inverse() function. Therefore M * M, M * V and M * f operations are
  all supported.

- When multiplying a matrix by a 2D or 3D vector, the vectors are intended to be directions 
  instead of points in space. This is because you cannot really rotate and scale points. The
  M * V4 function might not be used much externally, it is more for being called internally
  from the other multiplication operations such as M * V2 or M * V3.

- The Output() function is for debug purposes and displays the matrix values in four neatly
  aligned columns and rows on the console window.

- The Inverse() function is comprised of a very long formula to work out the inverse of the 
  matrix. It might not be the most practical, but based on an online tutorial it has been 
  directly translated into code to demonstrate inverse calculations using minors, cofactors
  and adjugates. 

*/

#ifndef MATRIX_4D_H
#define MATRIX_4D_H

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4D
{

public:

	enum MATRIX_TYPE { IDENTITY };

public :

	Matrix4D();
	Matrix4D(const float* rhs);

public:

	float* GetMatrixArray();

public :

	float& operator[](const int index);
	Matrix4D& operator=(const float* rhs);
	Matrix4D& operator=(const MATRIX_TYPE rhs);

public :

	Matrix4D& operator*(Matrix4D& rhs);
	Matrix4D& operator*(const float rhs);
	Vector2D<float> operator*(const Vector2D<float>& rhs);  
	Vector3D<float> operator*(const Vector3D<float>& rhs);  
	Vector4D<float> operator*(const Vector4D<float>& rhs);  

public :

	void Output();
	Matrix4D Inverse();

private :

	float m_matrix[16];

};

#endif