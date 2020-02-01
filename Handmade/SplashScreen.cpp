#include <gtc\matrix_transform.hpp>
#include "Game.h"
#include "Input.h"
#include "Screen.h"
#include "SplashScreen.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults 
//------------------------------------------------------------------------------------------------------
SplashScreen::SplashScreen(std::string filename)
{

	m_alpha = 0.0f;
	m_fade = FADE_IN;
	m_filename = filename;
	m_sprite.SetColor(1.0f, 1.0f, 1.0f, 0.0f);

}
//------------------------------------------------------------------------------------------------------
//function that creates sprite buffers and loads the images
//------------------------------------------------------------------------------------------------------
bool SplashScreen::Create()
{

	//create buffers for splash screen and if they 
	//already exist assign to the existing ones
	if (!m_sprite.Create("SPLASH"))
	{
		m_sprite.SetBuffer("SPLASH");
	}

	//load texture image and associate with this particular splash screen
	m_sprite.LoadTexture(m_filename, "SPLASH_" + m_filename);
	
	//this sprite will never change so make it static
	m_sprite.SetSpriteType(Sprite::STATIC);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates image's alpha to fade in and out
//------------------------------------------------------------------------------------------------------
void SplashScreen::Update(int deltaTime)
{

	//store keyboard key states in a temp variable for processing below
	KeyState keyState = Input::Instance()->GetKeyStates();

	//if TAB key was pressed, deactivate splash screen 
	if (keyState[SDL_SCANCODE_TAB])
	{
		m_isActive = false;
	}

	//if image is set to fade in and image is not yet fully opaque then fade in image
	if (m_alpha <= 1.0f && m_fade == FADE_IN)
	{
		m_alpha += 0.5f * (float)deltaTime / 1000;
		m_sprite.SetColor(1.0f, 1.0f, 1.0f, m_alpha);
	}

	//otherwise once image becomes opaque set flag to fade out and begin fading out
	else
	{
		m_fade = FADE_OUT;
		m_alpha -= 0.5f * (float)deltaTime / 1000;
		m_sprite.SetColor(1.0f, 1.0f, 1.0f, m_alpha);
	}
	
	//once image becomes transparent again deactivate this splash screen
	if (m_alpha <= 0.0f && m_fade == FADE_OUT)
	{
		m_alpha = 0.0f;
		m_isActive = false;
	}
	
}
//------------------------------------------------------------------------------------------------------
//function that displays the 2D splash screen
//------------------------------------------------------------------------------------------------------
void SplashScreen::Draw()
{

	m_modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1024.0f, 768.0f, 1.0f));
	SendToShader(false, true);
	m_sprite.Draw();

}
//------------------------------------------------------------------------------------------------------
//destructor that destroys VBO objects and unloads sprite image from memory 
//------------------------------------------------------------------------------------------------------
void SplashScreen::Destroy()
{

	m_sprite.Destroy("SPLASH");
	m_sprite.UnloadTexture("SPLASH_" + m_filename);

}