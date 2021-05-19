#ifndef LIGHT_H
#define LIGHT_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.				    		                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Light' source files last updated in December 2019									        |
#==============================================================================================*/

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

public:

	void SetAttenuationLinear(GLfloat attLinear);
	void SetAttenuationConstant(GLfloat attConstant);
	void SetAttenuationQuadratic(GLfloat attQuadratic);
	
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

public:

	void Create(const std::string bufferID);
	void Update();
	void Draw();
	void Destroy(const std::string bufferID);

public:

	void SendToShader();

private:

	static GLuint s_totalLights;

private:

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

#endif