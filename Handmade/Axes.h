#pragma once

/*===================================================================#
| 'Axes' source files last updated on 29 June 2021                   |
#===================================================================*/

#include <string>
#include <glm.hpp>
#include "Buffer.h"
#include "Object.h"
#include "Shader.h"

class Axes : public Object
{

public:

	Axes(GLint size = 15, GLfloat lineWidth = 5.0f);
	~Axes();

	void SetSize(GLint size);
	void SetLineWidth(GLfloat lineWidth);

	virtual void SendToShader() {}
	virtual void Update(GLfloat deltaTime) {}
	virtual void Render(Shader& shader);

private:

	GLint m_size;
	Buffer m_buffer;
	GLfloat m_lineWidth;

};