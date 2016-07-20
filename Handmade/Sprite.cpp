#include "BufferManager.h"
#include "Sprite.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sprite::Sprite()
{

	//set flag to false by default
	m_isSpriteCreated = false;

	//assign ID to a default 0
	m_textureID = 0;

	//assign texture index to first sprite cell by default 
	m_textureIndex = 0;

	//set texture color to a default white color
	m_color = Color::WHITE;

	//set sprite to be static by default
	m_spriteType = STATIC;

	//assign texture dimension to 1 by default
	//this assumes the sprite's texture contains 1 image
	m_textureDimension.X = 1;
	m_textureDimension.Y = 1;

	//set the component sizes for the sprite object's vertex and color data
	m_buffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XY);
	m_buffer.SetComponentSize(Buffer::COLOR_BUFFER, Buffer::RGBA);

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns color reference
//------------------------------------------------------------------------------------------------------
Color& Sprite::SpriteColor()
{

	return m_color;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns type of sprite
//------------------------------------------------------------------------------------------------------
void Sprite::SetSpriteType(SpriteType spritetype)
{

	m_spriteType = spritetype;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific position of image cell in texture
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureCell(int column, int row)
{

	m_textureCell.X = column;
	m_textureCell.Y = row;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension of texture
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureDimension(int column, int row)
{

	m_textureDimension.X = column;
	m_textureDimension.Y = row;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns texture image ID to sprite based on index value passed
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureID(const std::string& mapIndex)
{

	m_textureID = TheTexture::Instance()->GetTextureID(mapIndex);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns size of sprite
//------------------------------------------------------------------------------------------------------
void Sprite::SetSpriteDimension(float width, float height)
{

	m_spriteDimension.X = width;
	m_spriteDimension.Y = height;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns VBO IDs based on ID names passed
//------------------------------------------------------------------------------------------------------
void Sprite::SetBufferID(const std::string& vertexID, const std::string& colorID,
				         const std::string& textureID)
{

	m_buffer.SetBufferID(Buffer::VERTEX_BUFFER, vertexID);
	m_buffer.SetBufferID(Buffer::COLOR_BUFFER, colorID);
	m_buffer.SetBufferID(Buffer::TEXTURE_BUFFER, textureID);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns shader attribute IDs based on attribute names passed
//------------------------------------------------------------------------------------------------------
void Sprite::SetShaderAttribute(const std::string& vertexAttr, const std::string& colorAttr, 
	                            const std::string& textureAttr)
{

	m_buffer.SetAttributeID(Buffer::VERTEX_BUFFER, vertexAttr);
	m_buffer.SetAttributeID(Buffer::COLOR_BUFFER, colorAttr);
	m_buffer.SetAttributeID(Buffer::TEXTURE_BUFFER, textureAttr);

}
//------------------------------------------------------------------------------------------------------
//function that creates and draws the actual sprite on screen
//------------------------------------------------------------------------------------------------------
void Sprite::Draw()
{

	//aquire index value of specific texture cell to "cut out" using a basic formula 
	m_textureIndex = (m_textureCell.Y * m_textureDimension.X) + m_textureCell.X;

	//only if sprite is set to change or if it needs to be initially 
	//created then call the necessary functions to create the sprite 
	if (m_spriteType == DYNAMIC || (m_spriteType == STATIC && !m_isSpriteCreated))
	{

		//clear all buffer data from vectors
		ClearBufferData();

		//create the vertex, texture and color buffer data
		CreateVertices();
		CreateTexCoords();
		CreateColors();

		//fill the VBOs with the buffer data
		FillBuffers();

		//set flag so that static sprites are not created again
		m_isSpriteCreated = true;

	}

	//create and draw the sprite
	CreateSprite();

}
//------------------------------------------------------------------------------------------------------
//function that fills VBO buffers with vertex, texture and color data
//------------------------------------------------------------------------------------------------------
void Sprite::FillBuffers()
{

	m_buffer.FillData(Buffer::COLOR_BUFFER);
	m_buffer.FillData(Buffer::VERTEX_BUFFER);
	m_buffer.FillData(Buffer::TEXTURE_BUFFER);

}
//------------------------------------------------------------------------------------------------------
//function that clears the vertex, texture and color buffer data for new use
//------------------------------------------------------------------------------------------------------
void Sprite::ClearBufferData()
{

	m_buffer.Colors().clear();
	m_buffer.Vertices().clear();
	m_buffer.Textures().clear();

}
//------------------------------------------------------------------------------------------------------
//function that binds the texture, and sends sprite data to shaders 
//------------------------------------------------------------------------------------------------------
void Sprite::CreateSprite()
{

	//bind texture with sprite based on texture ID
	TheTexture::Instance()->Enable(m_textureID);

	//send sprite data to shaders
	m_buffer.DrawData(Buffer::TRIANGLES);

	//unbind texture so that there are no left over links
	TheTexture::Instance()->Disable();

}
//------------------------------------------------------------------------------------------------------
//function that adds color data to buffer object's color vector
//------------------------------------------------------------------------------------------------------
void Sprite::CreateColors()
{

	//color data for vertex #1
	m_buffer.Colors().push_back(m_color.R); m_buffer.Colors().push_back(m_color.G);
	m_buffer.Colors().push_back(m_color.B); m_buffer.Colors().push_back(m_color.A);

	//color data for vertex #2
	m_buffer.Colors().push_back(m_color.R); m_buffer.Colors().push_back(m_color.G);
	m_buffer.Colors().push_back(m_color.B); m_buffer.Colors().push_back(m_color.A);

	//color data for vertex #3
	m_buffer.Colors().push_back(m_color.R); m_buffer.Colors().push_back(m_color.G);
	m_buffer.Colors().push_back(m_color.B); m_buffer.Colors().push_back(m_color.A);

	//color data for vertex #4
	m_buffer.Colors().push_back(m_color.R); m_buffer.Colors().push_back(m_color.G);
	m_buffer.Colors().push_back(m_color.B); m_buffer.Colors().push_back(m_color.A);

	//color data for vertex #5
	m_buffer.Colors().push_back(m_color.R); m_buffer.Colors().push_back(m_color.G);
	m_buffer.Colors().push_back(m_color.B); m_buffer.Colors().push_back(m_color.A);

	//color data for vertex #6
	m_buffer.Colors().push_back(m_color.R); m_buffer.Colors().push_back(m_color.G);
	m_buffer.Colors().push_back(m_color.B); m_buffer.Colors().push_back(m_color.A);

}
//------------------------------------------------------------------------------------------------------
//function that adds vertex data to buffer object's vertex vector
//------------------------------------------------------------------------------------------------------
void Sprite::CreateVertices()
{

	//sprite vertices are based on centre position of sprite
	//therefore we have to halve the width and height dimensions first
	Vector2D<float> halfDimension(m_spriteDimension.X / 2.0f, m_spriteDimension.Y / 2.0f);

	//vertex data for vertex #1
	m_buffer.Vertices().push_back(-halfDimension.X);
	m_buffer.Vertices().push_back(halfDimension.Y);

	//vertex data for vertex #2
	m_buffer.Vertices().push_back(halfDimension.X);
	m_buffer.Vertices().push_back(halfDimension.Y);

	//vertex data for vertex #3
	m_buffer.Vertices().push_back(-halfDimension.X);
	m_buffer.Vertices().push_back(-halfDimension.Y);

	//vertex data for vertex #4
	m_buffer.Vertices().push_back(-halfDimension.X);
	m_buffer.Vertices().push_back(-halfDimension.Y);

	//vertex data for vertex #5
	m_buffer.Vertices().push_back(halfDimension.X);
	m_buffer.Vertices().push_back(halfDimension.Y);

	//vertex data for vertex #6
	m_buffer.Vertices().push_back(halfDimension.X);
	m_buffer.Vertices().push_back(-halfDimension.Y);

}
//------------------------------------------------------------------------------------------------------
//function that adds texture coordinate data to buffer object's texture coordinate vector
//------------------------------------------------------------------------------------------------------
void Sprite::CreateTexCoords()
{

	//variable for temporary texture coordinates
	Vector2D<float> texCoord;

	//calculate fractional X and Y texture dimension value based on texture dimension
	//this fractional value is needed to keep texture UVs between 0 and 1
	Vector2D<float> oneOverDimension(1.0f / m_textureDimension.X, 1.0f / m_textureDimension.Y);

	//use modulo and divide with the texture index 
	//to get exact cell block XY coordinates to "cut out"
	texCoord.X = (float)(m_textureIndex % m_textureDimension.X);
	texCoord.Y = (float)(m_textureIndex / m_textureDimension.X);

	//multiply the texture coordinate result by 
	//oneOverDimension to get a value between 0 and 1
	texCoord *= oneOverDimension;
	
	//texture coordinate data for vertex #1
	m_buffer.Textures().push_back(texCoord.X);
	m_buffer.Textures().push_back(texCoord.Y);

	//texture coordinate data for vertex #2
	m_buffer.Textures().push_back(texCoord.X + oneOverDimension.X);
	m_buffer.Textures().push_back(texCoord.Y);

	//texture coordinate data for vertex #3
	m_buffer.Textures().push_back(texCoord.X);
	m_buffer.Textures().push_back(texCoord.Y + oneOverDimension.Y);

	//texture coordinate data for vertex #4
	m_buffer.Textures().push_back(texCoord.X);
	m_buffer.Textures().push_back(texCoord.Y + oneOverDimension.Y);

	//texture coordinate data for vertex #5
	m_buffer.Textures().push_back(texCoord.X + oneOverDimension.X);
	m_buffer.Textures().push_back(texCoord.Y);

	//texture coordinate data for vertex #6
	m_buffer.Textures().push_back(texCoord.X + oneOverDimension.X);
	m_buffer.Textures().push_back(texCoord.Y + oneOverDimension.Y);

}