#include <gtc\matrix_transform.hpp>
#include "Debug.h"
#include "HUD.h"
#include "Screen.h"
#include "Shader.h"

//======================================================================================================
bool HUD::Create()
{
	m_sprite.Create("HUD");
	m_sprite.LoadTexture("Assets/Sprites/HUD.png", "HUD");
	m_sprite.SetSpriteType(Sprite::STATIC);
	return true;
}
//======================================================================================================
void HUD::Draw()
{
	Screen::Instance()->GetResolution(m_dimension.x, m_dimension.y);
	m_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, (m_dimension.y - 150.0f), 0.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(200.0f, 140.0f, 1.0f));

	GameObject::SendToShader(false, true);
	m_sprite.Draw();
}
//======================================================================================================
void HUD::Destroy()
{
	m_sprite.Destroy("HUD");
	m_sprite.UnloadTexture("HUD");
}