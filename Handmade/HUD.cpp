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
	TheTexture::Instance()->LoadFromFile("Assets\\Sprites\\HUD.png", "HUD_TEXTURE");
	
	//set dimension, texture and buffer properties of sprite object
	m_sprite.SetSpriteDimension(200, 140);
	m_sprite.SetTextureID("HUD_TEXTURE");
	m_sprite.SetBufferID("HUD_VERTEX_BUFFER", "HUD_COLOR_BUFFER", "HUD_TEXTURE_BUFFER");
	m_sprite.SetShaderAttribute("vertexIn", "colorIn", "textureIn");

	//get texture flag ID from fragment shader
	m_textureFlagUniformID = TheShader::Instance()->GetUniformID("isTextured");

	//create screen position for sprite object based on screen height
	float screenHeight = TheScreen::Instance()->GetScreenSize().y;
	m_transform = glm::translate(m_transform, glm::vec3(110.0f, (screenHeight - 80.0f), 0.0f));

}
//------------------------------------------------------------------------------------------------------
//function that displays the 2D heads-up display on screen
//------------------------------------------------------------------------------------------------------
bool HUD::Draw()
{

	//setup screen in 2D orthographic mode because all HUDs are 2D 
	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

	//reset model matrix to identity so we don't accumulate transformations
	GameObject::SetIdentity();

	//apply HUD position transformation to model matrix
	GameObject::MultiplyMatrix(m_transform);

	//send model matrix to vertex shader
	GameObject::ApplyMatrix();
	
	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, true);

	//draw HUD image
	m_sprite.Draw();

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