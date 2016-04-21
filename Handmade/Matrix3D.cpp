#include <iomanip>
#include <iostream>
#include "Matrix3D.h"

//------------------------------------------------------------------------------------------------------
//constructor that sets the identity matrix as a default using =operator function
//------------------------------------------------------------------------------------------------------
Matrix3D::Matrix3D()
{

	*this = IDENTITY;

}
//------------------------------------------------------------------------------------------------------
//second constructor that assigns an array to Matrix object using =operator function
//------------------------------------------------------------------------------------------------------
Matrix3D::Matrix3D(const float* rhs)
{

	*this = rhs;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns internal matrix array  
//------------------------------------------------------------------------------------------------------
float* Matrix3D::GetMatrixArray()
{

	return m_matrix;

}
//------------------------------------------------------------------------------------------------------
//function that returns an index reference of Matrix object's inner array based on index passed
//------------------------------------------------------------------------------------------------------
float& Matrix3D::operator[](const int index)
{

	return m_matrix[index];

}
//------------------------------------------------------------------------------------------------------
//function that assigns an array to Matrix object
//------------------------------------------------------------------------------------------------------
Matrix3D& Matrix3D::operator=(const float* rhs)
{

	//loop through each element in rhs array
	//and assign each to Matrix object's array
	for (int i = 0; i < 9; i++)
	{
		m_matrix[i] = rhs[i];
	}

	//return a reference of the matrix object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that assigns a value to a Matrix object based on matrix enum type passed
//------------------------------------------------------------------------------------------------------
Matrix3D& Matrix3D::operator=(const MATRIX_TYPE rhs)
{

	switch (rhs)
	{
		//if value passed is IDENTITY, 
		//then make an identity matrix
		case IDENTITY:
		{
			//first set all elements to 0
			for (int i = 0; i < 9; i++)
			{
				m_matrix[i] = 0.0f;
			}

			//then set the major diagonal to 1
			m_matrix[0] = 1.0f;
			m_matrix[4] = 1.0f;
			m_matrix[8] = 1.0f;

			break;
		}

	}

	//return a reference of the matrix object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that displays Matrix object on console window
//this is for DEBUG only
//------------------------------------------------------------------------------------------------------
void Matrix3D::Output()
{

	//clear the console window screen
	system("cls");

	//assign flags to left align numbers correctly in their columns, 
	//and display them in floating point format with a two decimal point precision
	std::cout << std::left << std::fixed << std::setprecision(2) << std::endl;

	//loop through all 9 elements of inner array and
	//position and display values on screen
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << std::setw(5) << "[" << std::setw(7)
				      << m_matrix[i + (j * 3)] << "]" << std::setw(5) << " ";
		}

		std::cout << std::endl << std::endl;
	}

}
//------------------------------------------------------------------------------------------------------
//function that calculates and returns the determinant of matrix using a formula
//the formula for this has been extracted from this website :
//http://www.mathsisfun.com/algebra/matrix-determinant.html
//------------------------------------------------------------------------------------------------------
float Matrix3D::Determinant()
{

	return (m_matrix[0] * (m_matrix[4] * m_matrix[8] - m_matrix[5] * m_matrix[7])) -
		   (m_matrix[3] * (m_matrix[1] * m_matrix[8] - m_matrix[2] * m_matrix[7])) +
		   (m_matrix[6] * (m_matrix[1] * m_matrix[5] - m_matrix[2] * m_matrix[4]));

}