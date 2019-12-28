#include "Shader.h"
#include "Sprite.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sprite::Sprite()
{

	m_spriteType = STATIC;
	m_isSpriteSampled = false;

	//assign texture dimension to 1 by default
	//this assumes the sprite's texture contains 1 image
	m_textureDimension = glm::vec2(1.0f);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns type of sprite
//------------------------------------------------------------------------------------------------------
void Sprite::SetSpriteType(SpriteType spritetype)
{

	m_spriteType = spritetype;

}
//------------------------------------------------------------------------------------------------------
//function that assigns buffers to sprite based on buffer ID passed
//------------------------------------------------------------------------------------------------------
void Sprite::SetBuffer(const std::string& bufferID)
{

	m_buffer.SetBuffers(bufferID);

}
//------------------------------------------------------------------------------------------------------
//function that sets texture to sprite based on texture ID passed
//------------------------------------------------------------------------------------------------------
void Sprite::SetTexture(const std::string& textureID)
{

	m_texture.SetTexture(textureID);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific color of sprite
//------------------------------------------------------------------------------------------------------
void Sprite::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	//data that represents passed color for quad image
	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a  };

	//fill color buffer with passed color data
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific position of image cell in texture
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureCell(GLuint column, GLuint row)
{

	m_textureCell = glm::vec2(column, row);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension of texture
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureDimension(GLuint column, GLuint row)
{

	m_textureDimension = glm::vec2(column, row);

}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
bool Sprite::Create(const std::string bufferID)
{

	//create VAO, VBOs and EBO and if there is an error
	//it means the buffer has already been created in memory
	if (!m_buffer.CreateBuffers(bufferID, 6, true))
	{
		return false;
	}

	//data that represents vertices for sprite image
	//they are whole number values since a pixel is whole
	GLuint vertices[] = { 0, 1, 0,
						  1, 1, 0,
						  1, 0, 0,
						  0, 0, 0 };

	//data that represents colors for quad image
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f, 1.0f  };

	//data that represents texture coordinates for quad image
	GLfloat UVs[] = { 0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f };

	//data that represents indeces for quad image
	GLuint indices[] = { 0, 1, 3,
						 3, 1, 2 };

	//bind EBO and all VBOs and shader attributes together with VAO
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::U_INT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::TEXTURE_BUFFER, "textureIn", Buffer::UV, Buffer::FLOAT);

	//fill vertex and color VBOs with data 
	m_buffer.FillEBO(indices, sizeof(indices));
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::STATIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::DYNAMIC_FILL);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys all buffer objects
//------------------------------------------------------------------------------------------------------
void Sprite::Destroy(const std::string bufferID)
{

	m_buffer.DestroyBuffers(bufferID);

}
//------------------------------------------------------------------------------------------------------
//function that loads in texture file for sprite
//------------------------------------------------------------------------------------------------------
bool Sprite::LoadTexture(const std::string& filename, const std::string textureID)
{

	return m_texture.Load(filename, textureID);

}
//------------------------------------------------------------------------------------------------------
//function that unloads texture file for sprite
//------------------------------------------------------------------------------------------------------
void Sprite::UnloadTexture(const std::string textureID)
{

	m_texture.Unload(textureID);

}
//------------------------------------------------------------------------------------------------------
//function that samples the sprite with the correct texture or texture "cel"
//------------------------------------------------------------------------------------------------------
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
		m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::DYNAMIC_FILL);

		//set flag so that static sprites are not created again
		m_isSpriteSampled = true;

	}	

}
//------------------------------------------------------------------------------------------------------
//function that binds the sprite texture and sends all buffer data to shader
//------------------------------------------------------------------------------------------------------
void Sprite::Draw()
{

	m_texture.Bind();
	m_buffer.Draw(Buffer::TRIANGLES);

}