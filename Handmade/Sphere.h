#pragma once

/*===================================================================#
| 'Sphere' source files last updated on 29 June 2021                 |
#===================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"

//TODO - Add 'SphereCollider' component to the 'Circle' and 'Sphere' classes

class Sphere : public Object
{

public:

	Sphere(GLfloat radius = 1.0f, GLuint segments = 25, GLuint slices = 25,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);
	virtual ~Sphere();

	void SetRadius(GLfloat radius);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void SendToShader() {}
	virtual void Update(GLfloat deltaTime) {}
	virtual void Render(Shader& shader);
	
private:

	GLuint m_slices;
	GLfloat m_radius;
	GLuint m_segments;

	Buffer m_buffer;
	glm::vec4 m_color;

};