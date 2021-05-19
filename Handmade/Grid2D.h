#pragma once

/*===================================================================#
| 'Grid2D' source files last updated on 19 May 2021                  |
#===================================================================*/

#include "glad.h"
#include "Buffer.h"
#include "GameObject.h"

class Grid2D : public GameObject
{

public:

	Grid2D(GLint size = 15, GLfloat lineWidth = 2.0f);

	void SetSize(GLint size);
	void SetLineWidth(GLfloat lineWidth);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	virtual bool Create();
	virtual void Update(int deltaTime) {}
	virtual void Draw();
	virtual void Destroy();

private:

	GLint m_size;
	Buffer m_buffer;
	GLfloat m_lineWidth;

};