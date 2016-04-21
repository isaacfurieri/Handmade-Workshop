#include "BufferManager.h"
#include "DebugManager.h"
#include "HUD.h"
#include "ScreenManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that creates VBO objects, loads sprite image and assigns all defaults 
//------------------------------------------------------------------------------------------------------
HUD::HUD()
{

	//create a vertex, color and texture VBO for the heads-up display
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "HUD_VERTEX_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "HUD_COLOR_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::TEXTURE_BUFFER, "HUD_TEXTURE_BUFFER");

	//load HUD sprite image from file
	TheTexture::Instance()->LoadFromFile("Sprites\\HUD.png", "HUD_TEXTURE");
	
	//set dimension, texture and buffer properties of sprite object
	m_sprite.SetSpriteDimension(200, 140);
	m_sprite.SetTextureID("HUD_TEXTURE");
	m_sprite.SetBufferID("HUD_VERTEX_BUFFER", "HUD_COLOR_BUFFER", "HUD_TEXTURE_BUFFER");

	//create screen position for sprite object based on screen height
	m_transform.Translate(110.0f, (float)(TheScreen::Instance()->GetScreenSize().Y - 80));

}
//------------------------------------------------------------------------------------------------------
//function that displays the 2D heads-up display on screen
//------------------------------------------------------------------------------------------------------
bool HUD::Draw()
{

	//temporarily disable debug shaders
	TheDebug::Instance()->Disable();

	//setup screen in 2D orthographic mode because all HUDS are 2D 
	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

	//set modelview matrix to identity for a fresh new 2D start point
	TheScreen::Instance()->ModelViewMatrix() = Matrix4D::IDENTITY;

	//temporarily attach and link main program shaders
	TheShader::Instance()->Attach(ShaderManager::VERTEX_SHADER, "MAIN_VERTEX_SHADER");
	TheShader::Instance()->Attach(ShaderManager::FRAGMENT_SHADER, "MAIN_FRAGMENT_SHADER");
	TheShader::Instance()->Link();

	//link shader attribute variables to sprite object
	m_sprite.SetShaderAttribute("vertexIn", "colorIn", "textureIn");

	//move to top left corner of screen, apply position to modelview matrix 
	TheScreen::Instance()->ModelViewMatrix() * m_transform.GetMatrix();
	
	//send all matrix data to shaders
	TheShader::Instance()->SetUniform(TheShader::Instance()->GetUniform("projectionMatrix"),
		                              TheScreen::Instance()->ProjectionMatrix().GetMatrixArray());

	TheShader::Instance()->SetUniform(TheShader::Instance()->GetUniform("modelviewMatrix"),
		                              TheScreen::Instance()->ModelViewMatrix().GetMatrixArray());

	//draw HUD image
	m_sprite.Draw();

	//detach main program shaders
	TheShader::Instance()->Detach(ShaderManager::VERTEX_SHADER, "MAIN_VERTEX_SHADER");
	TheShader::Instance()->Detach(ShaderManager::FRAGMENT_SHADER, "MAIN_FRAGMENT_SHADER");

	//re-enable debug shaders
	TheDebug::Instance()->Enable();

	return true;

}
//------------------------------------------------------------------------------------------------------
//destructor that destroys VBO objects and unloads sprite image from memory 
//------------------------------------------------------------------------------------------------------
HUD::~HUD()
{

	//destroy vertex, color and texture VBOs for HUD
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "HUD_VERTEX_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "HUD_COLOR_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::TEXTURE_BUFFER, BufferManager::CUSTOM_BUFFER, "HUD_TEXTURE_BUFFER");

	//free HUD sprite image from memory
	TheTexture::Instance()->UnloadFromMemory(TextureManager::CUSTOM_TEXTURE, "HUD_TEXTURE");

}