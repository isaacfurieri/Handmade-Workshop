#pragma once

/*===================================================================#
| 'Tile' source files last updated on 7 July 2021                    |
#===================================================================*/

#include <string>
#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"

class Tile : public Object
{

public:

	Tile(GLfloat width = 1.0f, GLfloat height = 1.0f,
		GLuint spriteSheetCol = 1, GLuint spriteSheetRow = 1);
	virtual ~Tile();

	void IsAnimated(bool flag);
	void SetTile(GLuint tileIndex);
	void SetTile(GLuint column, GLuint row);
	void SetAnimationVelocity(GLfloat velocity);

	void SetDimension(const glm::vec3& dimension);
	void SetDimension(GLfloat width, GLfloat height);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader);

private:

	bool m_isAnimated;

	GLuint m_tileIndex;
	GLuint m_spriteSheetCol;
	GLuint m_spriteSheetRow;
	GLfloat m_animationVelocity;

	glm::vec4 m_color;
	glm::vec2 m_dimension;

	Buffer m_buffer;

	const GLuint CORNERS = 4;
	const GLuint VERTICES_PER_TILE = 6;

};