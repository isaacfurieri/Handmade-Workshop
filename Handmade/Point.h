#pragma once

/*===================================================================#
| 'Point' source files last updated on 29 June 2021                  |
#===================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"

//TODO - Add position value to the ctor (use David's MFC app as a reference)

class Point : public Object
{

public:

	Point(GLfloat pointSize = 5.0f, 
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);
	virtual ~Point();

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void SendToShader() {}
	virtual void Update(GLfloat deltaTime) {}
	virtual void Render(Shader& shader);

private:

	Buffer m_buffer;
	glm::vec4 m_color;
	GLfloat m_pointSize;

};