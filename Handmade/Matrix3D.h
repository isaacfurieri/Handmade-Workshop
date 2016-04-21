/*
  
  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : November 2015

  -----------------------------------------------------------------------------------------------

- This is a Matrix class that represents a 3x3 matrix. It is not intended for much external 
  use, because 4x4 matrices are more frequently used. Instead this class is there to assist
  the Matrix4D class when it comes to inverse calculations, and to make the calculations easier 
  to read.  

- The main member variable is an internal array of floats that will represent the matrix
  in column major format. Unlike the Vector or Quaternion classes I have created, the Matrix
  class' array is inaccessible, and can only be accessed via the GetMatrixArray() function, 
  which returns the entire array, or the [] overloaded operator function, which returns only 
  one element of the array.

- While most reference parameters are const and should be so, not all are because of conflicts
  within the functions. These can be addressed at a later stage.

- The Output() function is for debug purposes and displays the matrix values in three neatly
  aligned columns and rows on the console window.

- The Determinant() routine is only there to help make things easier in the Inverse() function
  of the Matrix4D class. It is public so that the Matrix4D class can access it, making it also
  accessible to external code, however it will probably not be used much externally.

*/

#ifndef MATRIX_3D_H
#define MATRIX_3D_H

class Matrix3D
{

public:

	enum MATRIX_TYPE { IDENTITY };

public:

	Matrix3D(); 
	Matrix3D(const float* rhs); 

public :

	float* GetMatrixArray(); 

public:

	float& operator[](const int index);
	Matrix3D& operator=(const float* rhs); 
	Matrix3D& operator=(const MATRIX_TYPE rhs);

public:

	void Output(); 
	float Determinant();

private:

	float m_matrix[9];

};

#endif