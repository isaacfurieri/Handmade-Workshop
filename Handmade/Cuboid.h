#pragma once

/*===================================================================#
| 'Cuboid' source files last updated on 25 May 2021                  |
#===================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "GameObject.h"

//TODO - Add 'BoxCollider' component to the 'Quad' and 'Cuboid' classes

class Cuboid : public GameObject
{

public:

	Cuboid(GLfloat width = 1.0f, GLfloat height = 1.0f, GLfloat depth = 1.0f,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SetDimension(GLfloat width, GLfloat height, GLfloat depth);

	virtual bool Create();
	virtual void Update(GLint deltaTime) {}
	virtual void Draw();
	virtual void Destroy();

private:

	Buffer m_buffer;
	glm::vec4 m_color;
	glm::vec3 m_dimension;

};