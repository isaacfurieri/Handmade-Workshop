#pragma once

/*===================================================================#
| 'Sphere' source files last updated on 25 May 2021                  |
#===================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "GameObject.h"

//TODO - Add 'SphereCollider' component to the 'Circle' and 'Sphere' classes

class Sphere : public GameObject
{

public:

	Sphere(GLfloat radius = 1.0f, GLuint segments = 25, GLuint slices = 25,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);

	void SetRadius(GLfloat radius);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual bool Create();
	virtual void Update(GLint deltaTime) {}
	virtual void Draw();
	virtual void Destroy();

private:

	GLuint m_slices;
	GLfloat m_radius;
	GLuint m_segments;

	Buffer m_buffer;
	glm::vec4 m_color;

};