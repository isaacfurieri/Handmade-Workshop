/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a light component in the game world. It comprises of all lighting 
  properties that will affect the lighting calculations in the fragment shader. The light itself
  can also be drawn and this is for debug purposes to see where the light is in the scene. In
  particular the Create(), Update(), Draw() and Destroy() functions are for DEBUG only and are
  there to create and render an actual "light bulb" in the scene. The SendToShader() function
  passes all the light properties to the fragment shader to be processed to light up the scene
  accordingly.

*/

#ifndef LIGHT_H
#define LIGHT_H

#include "glad.h"
#include <glm.hpp>
#include "Buffer.h"

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