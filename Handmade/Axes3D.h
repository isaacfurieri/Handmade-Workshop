#pragma once

/*===================================================================#
| 'Axes3D' source files last updated on 19 May 2021                  |
#===================================================================*/

#include "glad.h"
#include "Buffer.h"
#include "GameObject.h"

class Axes3D : public GameObject
{

public:

	Axes3D(GLint size = 15, GLfloat lineWidth = 5.0f);

	void SetSize(GLint size);
	void SetLineWidth(GLfloat lineWidth);

	virtual bool Create();
	virtual void Update(int deltaTime) {}
	virtual void Draw();
	virtual void Destroy();

private:

	GLint m_size;
	Buffer m_buffer;
	GLfloat m_lineWidth;

};