#pragma once

/*===================================================================#
| 'Quad' source files last updated on 19 May 2021                    |
#===================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "GameObject.h"

//TODO - Add 'BoxCollider' component to the 'Quad' and 'Cuboid' classes

class Quad : public GameObject
{

public:

	Quad(GLfloat width = 1.0f, GLfloat height = 1.0f,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);

	void SetDimension(GLfloat width, GLfloat height);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual bool Create();
	virtual void Update(int deltaTime) {}
	virtual void Draw();
	virtual void Destroy();

private:

	Buffer m_buffer;
	glm::vec4 m_color;
	glm::vec2 m_dimension;

};