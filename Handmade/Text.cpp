#include <glew.h>
#include "ScreenManager.h"
#include "ShaderManager.h"
#include "Text.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Text::Text()
{

	//set sprite to be dynamic by default
	m_spriteType = DYNAMIC;

	//set other default values
	m_text = "";
	m_charSpace = 0.0f;
	
	//default font texture dimensions are set to 16x16
	//as is setup in the Bitmap Font Builder textures
	m_textureDimension.x = 16;
	m_textureDimension.y = 16;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns string text to object
//------------------------------------------------------------------------------------------------------
void Text::SetText(const std::string& text)
{

	m_text = text;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns spacing size between text letters
//------------------------------------------------------------------------------------------------------
void Text::SetCharSpace(float charSpace)
{

	m_charSpace = charSpace;

}
//------------------------------------------------------------------------------------------------------
//function that creates and draws the actual text on screen
//------------------------------------------------------------------------------------------------------
void Text::Draw()
{

	//only if sprite is set to change or if it needs to be initially 
	//created then call the necessary functions to create the sprite 
	if (m_spriteType == DYNAMIC || (m_spriteType == STATIC && !m_isSpriteCreated))
	{

		//clear all buffer data from vectors
		ClearBufferData();

		//loop through the entire text string and 
		//create buffer data for each character
		for (size_t i = 0; i < m_text.size(); i++)
		{

			//the texture index is the actual ASCII value of the letter
			m_textureIndex = m_text[i];

			//create the vertex, texture and color buffer data
			CreateVertices(i);
			CreateTexCoords();
			CreateColors();

		}

		//fill the VBOs with the buffer data
		FillBuffers();

		//set flag so that static sprites are not created again
		m_isSpriteCreated = true;

	}

	//create and draw the sprite
	CreateSprite();

}
//------------------------------------------------------------------------------------------------------
//function that adds vertex data to buffer object's vertex vector
//------------------------------------------------------------------------------------------------------
void Text::CreateVertices(int characterIndex)
{

	//variable that stores centre point of current character in string text around which 
	//text object will be created. This will always translate on X axis no matter how the
	//text object is transformed because the letters always read from left to right
	float characterOrigin = (0.0f + m_spriteDimension.x + m_charSpace) * characterIndex;

	//sprite vertices are based on centre position of sprite
	//therefore we have to halve the width and height dimensions first
	glm::vec2 halfDimension(m_spriteDimension.x / 2.0f, m_spriteDimension.y / 2.0f);

	//vertex data for vertex #1
	m_buffer.Vertices().push_back(characterOrigin - halfDimension.x);
	m_buffer.Vertices().push_back(halfDimension.y);

	//vertex data for vertex #2
	m_buffer.Vertices().push_back(characterOrigin + halfDimension.x);
	m_buffer.Vertices().push_back(halfDimension.y);

	//vertex data for vertex #3
	m_buffer.Vertices().push_back(characterOrigin - halfDimension.x);
	m_buffer.Vertices().push_back(-halfDimension.y);

	//vertex data for vertex #4
	m_buffer.Vertices().push_back(characterOrigin - halfDimension.x);
	m_buffer.Vertices().push_back(-halfDimension.y);

	//vertex data for vertex #5
	m_buffer.Vertices().push_back(characterOrigin + halfDimension.x);
	m_buffer.Vertices().push_back(halfDimension.y);

	//vertex data for vertex #6
	m_buffer.Vertices().push_back(characterOrigin + halfDimension.x);
	m_buffer.Vertices().push_back(-halfDimension.y);

}