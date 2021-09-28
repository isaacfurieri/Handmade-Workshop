#pragma once

/*===================================================================#
| 'Tile' source files last updated on 28 September 2021              |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <string>
#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"
#include "Texture.h"

class Tile : public Object
{

public:

	Tile(const std::string& filename,
		GLfloat width = 1.0f, GLfloat height = 1.0f,
		GLuint spriteSheetCol = 1, GLuint spriteSheetRow = 1);
	virtual ~Tile();

	bool IsAnimationDead() const;
	bool IsAnimationLooping() const;

	void IsAnimated(bool flag);
	void IsAnimationLooping(bool flag);

	void SetTileIndex(GLuint tileIndex);
	void SetTileIndex(GLuint column, GLuint row);
	void SetAnimationVelocity(GLfloat velocity);

	void SetDimension(const glm::vec3& dimension);
	void SetDimension(GLfloat width, GLfloat height);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader);

private:

	bool m_isAnimated;
	bool m_isAnimationDead;
	bool m_isAnimationLooping;
	bool m_isAnimationLoopFinal;

	GLuint m_tileIndex;
	GLuint m_spriteSheetCol;
	GLuint m_spriteSheetRow;
	GLfloat m_animationVelocity;

	Buffer m_buffer;
	Texture m_texture;

	glm::vec4 m_color;
	glm::vec2 m_dimension;

	const GLuint CORNERS = 4;
	const GLuint VERTICES_PER_TILE = 6;

};