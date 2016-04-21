#include <OpenGL.h>
#include "ScreenManager.h"
#include "ShaderManager.h"
#include "Text.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Text::Text()
{

	//set sprite to dynamic by default 
	//as the textures will change constantly
	m_spriteType = DYNAMIC;

	//set other default values
	m_text = "";
	m_uniform = "";
	m_charSpace = 0.0f;
	
	//default font texture dimensions are set to 16x16
	//as is setup in the Bitmap Font Builder textures
	m_textureDimension.X = 16;
	m_textureDimension.Y = 16;

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
void Text::SetCharSpace(GLfloat charSpace)
{

	m_charSpace = charSpace;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns shader uniform name based on uniform name passed
//------------------------------------------------------------------------------------------------------
void Text::SetShaderUniform(const std::string& uniform)
{

	m_uniform = uniform;

}
//------------------------------------------------------------------------------------------------------
//function that creates and draws the actual text on screen
//------------------------------------------------------------------------------------------------------
void Text::Draw()
{

	//set character positioning value for each letter in string text
	//always translate on X axis no matter how the text object is 
	//transformed because the letters always read from left to right
	m_translation.Translate(m_spriteDimension.X + m_charSpace, 0, 0);

	//loop through the entire text string
	for (size_t i = 0; i < m_text.size(); i++)
	{
		
		//the texture index is the actual ascii value of the letter
		m_textureIndex = m_text[i];
		
		//draw each individual letter sprite with texture using the base class functions
		CreateVertices();
		CreateTexCoords();
		CreateColors();
		CreateSprite();

		//move position to next letter in string using translation set earlier 
		TheScreen::Instance()->ModelViewMatrix() * m_translation.GetMatrix();

		//first get the shader modelview matrix uniform id from the shader 
		//manager then use that to pass the modelview matrix data to the shader
		//this needs to be done for each letter because the modelview matrix changes each time
		TheShader::Instance()->SetUniform(TheShader::Instance()->GetUniform(m_uniform),
			                              TheScreen::Instance()->ModelViewMatrix().GetMatrixArray());

	}

	//reset translation value so that it doesn't accumulate
	m_translation.GetMatrix() = Matrix4D::IDENTITY;

}