#pragma once

/*===================================================================#
| 'Material' source files last updated on 19 May 2021                |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>

//TODO - Refine class such that it follows newer design

class Material
{

public:

	Material();

	void SetShininess(GLfloat shininess);
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SendToShader();

private:

	GLfloat m_shininess;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};