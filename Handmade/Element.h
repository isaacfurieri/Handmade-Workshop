#pragma once

/*===================================================================#
| 'Element' source files last updated on 25 May 2021                 |
#===================================================================*/

#include "Buffer.h"
#include "GameObject.h"

class Element : public GameObject
{

public:

	Element() {}

	virtual bool Create();
	virtual void Update(GLint deltaTime) {}
	virtual void Draw() {}

	void DrawVertex(GLfloat x, GLfloat y, GLfloat z,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f,
		GLfloat pointSize = 10.0f);

	void DrawVector(GLfloat x, GLfloat y, GLfloat z,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f,
		GLfloat lineWidth = 2.0f);

	void DrawLineSegment(GLfloat x1, GLfloat y1, GLfloat z1,
		GLfloat x2, GLfloat y2, GLfloat z2,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f,
		GLfloat lineWidth = 2.0f);

	virtual void Destroy();

private:

	Buffer m_buffer;

};