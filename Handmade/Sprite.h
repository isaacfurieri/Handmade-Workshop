#pragma once

/*===================================================================#
| 'Sprite' source files last updated on 24 June 2021                 |
#===================================================================*/

//TODO - Add 'Tile' class
//TODO - Remove 'Sprite' and 'Animation' classes  
//TODO - Add functionality to process sprite sheets(static/animated)

#include <string>
#include "glad.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"

class Sprite
{

public:

	enum SpriteType 
	{ 
		STATIC, 
		DYNAMIC 
	};

	Sprite();           

	bool IsAnimationDead();
	bool& IsAnimationLooping();
	void SetAnimationVelocity(GLfloat velocity);

	void SetSpriteType(SpriteType spritetype);

	void SetBuffer(const std::string& bufferID);
	void SetTexture(const std::string& textureID);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	void SetTextureCell(GLuint column, GLuint row);
	void SetTextureDimension(GLuint column, GLuint row);

	bool Create(const std::string bufferID);
	void Destroy(const std::string bufferID);
	bool LoadTexture(const std::string& filename, const std::string textureID);
	void UnloadTexture(const std::string textureID);

	void Update();
	void Render(Shader& shader);

private:

	bool m_isAnimationDead;
	bool m_isAnimationLoopFinal;
	bool m_isAnimationLooping;

	double m_timeElapsed;
	GLfloat m_animationVelocity;

	bool m_isSpriteSampled;

	glm::vec2 m_textureCell;
	glm::vec2 m_textureDimension;

	Buffer m_buffer;
	Texture m_texture;
	SpriteType m_spriteType;

};