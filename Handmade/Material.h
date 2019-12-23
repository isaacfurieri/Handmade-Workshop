/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class is another core component and represents a material that can be applied to any 
  object or 3D model in the game world. All of its ambient, diffuse and specular properties can
  be set accordingly and are passed to the fragment shader to be processed by the lighting 
  calculations. 

*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "glad.h"
#include <glm.hpp>

class Material
{

public:

	Material();

public:

	void SetShininess(GLfloat shininess);
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

public:

	void SendToShader();

private:

	GLfloat m_shininess;
	
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};

#endif