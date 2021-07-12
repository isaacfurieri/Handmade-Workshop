#pragma once

/*===================================================================#
| 'Light' source files last updated on 12 July 2021                  |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Object.h"

//TODO - Refine class such that it follows newer design
//TODO - Add support for spot, directional and point lights

class Light : public Object
{

public:

	Light();
	virtual ~Light();

	void SetAttenuationLinear(GLfloat attLinear);
	void SetAttenuationConstant(GLfloat attConstant);
	void SetAttenuationQuadratic(GLfloat attQuadratic);

	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	virtual void Render(Shader& shader); /*debug only*/
	virtual void Update(GLfloat deltaTime) { /*debug only*/ }
	virtual void SendToShader(Shader& shader);

private:

	static GLuint s_totalLights;

	GLuint m_lightNumber;

	GLfloat m_attLinear;
	GLfloat m_attConstant;
	GLfloat m_attQuadratic;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	Buffer m_buffer;

};