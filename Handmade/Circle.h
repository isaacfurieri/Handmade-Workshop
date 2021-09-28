#pragma once

/*===================================================================#
| 'Circle' source files last updated on 28 September 2021            |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "Buffer.h"
#include "Object.h"

class Circle : public Object
{

public:

	Circle(GLfloat radius = 1.0f, GLuint slices = 25,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);
	virtual ~Circle();

	void SetRadius(GLfloat radius);
	void SetColor(const glm::vec4& color);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	GLuint m_slices;
	GLfloat m_radius;
	Buffer m_buffer;

};