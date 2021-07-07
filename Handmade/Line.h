#pragma once

/*===================================================================#
| 'Line' source files last updated on 7 July 2021                    |
#===================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"

//TODO - Add line start/end position to ctor so that we have an actual line to begin with
//TODO - Add SetStart/end position functions to set the absolute values of the line segment

class Line : public Object
{

public:

	Line(GLfloat lineWidth = 2.0f,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);
	virtual ~Line();

	void SetEndPoints(GLfloat x1, GLfloat y1, GLfloat z1,
		GLfloat x2, GLfloat y2, GLfloat z2);

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	Buffer m_buffer;
	glm::vec4 m_color;
	GLfloat m_lineWidth;

};