#include "Shader.h"
#include "Sprite.h"

//======================================================================================================
Sprite::Sprite()
{
	m_spriteType = STATIC;
	m_isSpriteSampled = false;
	m_textureCell = glm::vec2(0.0f);	
	m_textureDimension = glm::vec2(1.0f);

	m_isAnimationDead = false;
	m_isAnimationLoopFinal = false;
	m_isAnimationLooping = true;
}
//======================================================================================================
bool Sprite::IsAnimationDead()
{
	return m_isAnimationDead;
}
//======================================================================================================
bool& Sprite::IsAnimationLooping()
{
	return m_isAnimationLooping;
}
//======================================================================================================
void Sprite::SetAnimationVelocity(GLfloat velocity)
{
	m_animationVelocity = velocity;
}
//======================================================================================================
void Sprite::SetSpriteType(SpriteType spritetype)
{
	m_spriteType = spritetype;
}
//======================================================================================================
void Sprite::SetBuffer(const std::string& bufferID)
{
	m_buffer.SetBuffer(bufferID);
}
//======================================================================================================
void Sprite::SetTexture(const std::string& textureID)
{
	m_texture.SetTexture(textureID);
}
//======================================================================================================
void Sprite::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a  };

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
}
//======================================================================================================
void Sprite::SetTextureCell(GLuint column, GLuint row)
{
	m_textureCell = glm::vec2(column, row);
}
//======================================================================================================
void Sprite::SetTextureDimension(GLuint column, GLuint row)
{
	m_textureDimension = glm::vec2(column, row);
}
//======================================================================================================
bool Sprite::Create(const std::string bufferID)
{
	m_buffer.Create(bufferID, 6, true);	

	GLuint vertices[] = { 0, 1, 0,
						  1, 1, 0,
						  1, 0, 0,
						  0, 0, 0 };

	GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f, 1.0f  };

	GLfloat UVs[] = { 0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f };

	GLuint indices[] = { 0, 1, 3,
						 3, 1, 2 };

	m_buffer.LinkEBO();
	m_buffer.FillEBO(indices, sizeof(indices));
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FILL_MANY);

	return true;
}
//======================================================================================================
void Sprite::Destroy(const std::string bufferID)
{
	m_buffer.Destroy(bufferID);
}
//======================================================================================================
bool Sprite::LoadTexture(const std::string& filename, const std::string textureID)
{
	return m_texture.Load(filename, textureID);
}
//======================================================================================================
void Sprite::UnloadTexture(const std::string textureID)
{
	m_texture.Unload(textureID);
}
//======================================================================================================
void Sprite::Update()
{
	//only if sprite is set to change or if it needs to be initially 
	//sampled then call the necessary functions to "cut out" the sprite 
	if (m_spriteType == DYNAMIC || (m_spriteType == STATIC && !m_isSpriteSampled))
	{

		//calculate the width and height of each cell relative to the entire texture 
		//this gives us a normalized dimension value for each "cell" in the sprite sheet
		glm::vec2 cellDimension(1.0f / m_textureDimension.x, 1.0f / m_textureDimension.y);

		//take the desired cell to "cut out" and multiply it by the cell's dimension value
		//this gives us a normalized texture coordinate value that is out "starting point" 
		glm::vec2 texCoordOrigin = m_textureCell * cellDimension;

		//create new UV data that for our texture coordinates
		GLfloat UVs[] = { texCoordOrigin.x,                   texCoordOrigin.y,
						  texCoordOrigin.x + cellDimension.x, texCoordOrigin.y,
						  texCoordOrigin.x + cellDimension.x, texCoordOrigin.y + cellDimension.y,
						  texCoordOrigin.x,                   texCoordOrigin.y + cellDimension.y };

		//fill texture VBO with new UV data 
		m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FILL_MANY);

		//set flag so that static sprites are not created again
		m_isSpriteSampled = true;

	}	

	//Animation code==================================================================================
	//store the total time elapsed since animation began which will be used in formula below
	m_timeElapsed += 0.016; // Game::Instance()->GetElapsedTime() / 1000.0f;

	//aquire index value of specific texture cell to "cut out" using a formula
	//the texture index is zero based and is a whole number value counting from
	//top left and going right and down the spritesheet, and is capable of "wrapping"
	GLuint textureIndex = (GLint)(m_timeElapsed * m_animationVelocity) %
		(GLint)(m_textureDimension.x * m_textureDimension.y);

	//use modulo and divide with the texture index to get exact column/row 
	//index to "cut out", because with animations, the texture cell is dynamic
	m_textureCell.x = (GLfloat)(textureIndex % (GLint)m_textureDimension.x);
	m_textureCell.y = (GLfloat)(textureIndex / (GLint)m_textureDimension.x);

	//if animation is set to cycle endlessly then set the kill and final flags
	//to false so that no other final checks are made and that the animation loops
	if (m_isAnimationLooping)
	{
		m_isAnimationDead = false;
		m_isAnimationLoopFinal = false;
	}

	//otherwise if animation is set to cycle once and the last texture
	//cell has been reached then flag this as the final animation loop
	else if (!m_isAnimationLooping &&
		textureIndex == (m_textureDimension.x * m_textureDimension.y - 1))
	{
		m_isAnimationLoopFinal = true;
	}

	//if this is the final animation, flag to kill entire animation
	//because even though the animation is marked final, a few more 
	//frames will be called with the last texture cell set, so only
	//mark it dead when the first texture cell comes around again
	if (m_isAnimationLoopFinal && textureIndex == 0)
	{
		m_isAnimationDead = true;
	}

	//if animation is set to run, then render 
	//the sprite using the base class function
	if (!m_isAnimationDead)
	{
		Sprite::Update();
	}

}
//======================================================================================================
void Sprite::Render(Shader& shader)
{
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);
	//m_buffer.LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ, Buffer::FLOAT);

	//m_texture.Bind();
	m_buffer.Render(Buffer::TRIANGLES);
}