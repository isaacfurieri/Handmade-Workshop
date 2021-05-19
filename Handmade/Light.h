#pragma once

/*===================================================================#
| 'Light' source files last updated on 19 May 2021                   |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>
#include "Buffer.h"

//TODO - Refine class such that it follows newer design
//TODO - Add support for spot, directional and point lights

class Light
{

public:

	Light();
	~Light();

	void SetAttenuationLinear(GLfloat attLinear);
	void SetAttenuationConstant(GLfloat attConstant);
	void SetAttenuationQuadratic(GLfloat attQuadratic);

	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	void Create(const std::string bufferID);
	void Update();
	void Draw();
	void Destroy(const std::string bufferID);

	void SendToShader();

private:

	static GLuint s_totalLights;

	GLuint m_lightNumber;

	GLfloat m_attLinear;
	GLfloat m_attConstant;
	GLfloat m_attQuadratic;

	glm::vec3 m_position;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	Buffer m_buffer;

};