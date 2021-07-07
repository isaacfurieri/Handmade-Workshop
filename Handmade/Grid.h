#pragma once

/*===================================================================#
| 'Grid' source files last updated on 7 July 2021                    |
#===================================================================*/

#include "glad.h"
#include "Buffer.h"
#include "Object.h"
#include "Shader.h"
//#include "Transform.h"

class Grid : public Object
{

public:

	Grid(GLint size = 15, GLfloat lineWidth = 2.0f);
	virtual ~Grid();

	void SetSize(GLint size);
	void SetLineWidth(GLfloat lineWidth);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	//Transform& GetTransform();

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	GLint m_size;
	GLfloat m_lineWidth;
	//glm::vec3 m_eulerAngles;

	Buffer m_buffer;
	//Transform m_transform;
};