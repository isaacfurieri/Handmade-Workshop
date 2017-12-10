#include "DebugManager.h"
#include "HUD.h"
#include "ScreenManager.h"
#include "PipelineManager.h"

//------------------------------------------------------------------------------------------------------
//function that creates sprite buffers and loads the HUD image
//------------------------------------------------------------------------------------------------------
bool HUD::Create()
{

	m_sprite.Create("HUD");
	m_sprite.LoadTexture("Assets\\Sprites\\HUD.png", "HUD");
	m_sprite.SetSpriteType(Sprite::STATIC);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that displays the 2D heads-up display on screen
//------------------------------------------------------------------------------------------------------
void HUD::Draw()
{

	//setup screen in 2D orthographic mode because all HUDs are 2D 
	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

	//reset model matrix to identity so we don't accumulate transformations
	GameObject::SetIdentity();

	float screenHeight = TheScreen::Instance()->GetScreenSize().y;
	GameObject::Translate(10.0f, (screenHeight - 150.0f), 0.0f);

	GameObject::Scale(200.0f, 140.0f, 1.0f);

	//send all flags and matrices to shaders 
	GameObject::SendToShader(false, true);
	
	//draw HUD image
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