#include <gtc\matrix_transform.hpp>
#include "Debug.h"
#include "HUD.h"
#include "Screen.h"
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//function that creates sprite buffers and loads the HUD image
//------------------------------------------------------------------------------------------------------
bool HUD::Create()
{

	m_sprite.Create("HUD");
	m_sprite.LoadTexture("Assets/Sprites/HUD.png", "HUD");
	m_sprite.SetSpriteType(Sprite::STATIC);
	Screen::Instance()->GetResolution(m_dimension.x, m_dimension.y);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that displays the 2D heads-up display on screen
//------------------------------------------------------------------------------------------------------
void HUD::Draw()
{

	m_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, (m_dimension.y - 150.0f), 0.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(200.0f, 140.0f, 1.0f));

	GameObject::SendToShader(false, true);
	m_sprite.Draw();

}
//------------------------------------------------------------------------------------------------------
//destructor that destroys VBO objects and unloads sprite image from memory 
//------------------------------------------------------------------------------------------------------
void HUD::Destroy()
{

	m_sprite.Destroy("HUD");
	m_sprite.UnloadTexture("HUD");

}