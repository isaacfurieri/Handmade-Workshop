#include "Debug.h"
#include "Game.h"
#include "Input.h"
#include "Shader.h"
#include "Screen.h"

//======================================================================================================
Game::Game()
{
	m_endGame = false;
	m_deltaTime = 0;
}
//======================================================================================================
int Game::GetTotalTime()
{
	return SDL_GetTicks();
}
//======================================================================================================
int Game::GetElapsedTime()
{
	return m_deltaTime;
}
//======================================================================================================
bool Game::Initialize(const std::string& name, GLuint screenWidth,
	GLuint screenHeight, GLuint pixelsPerUnit, bool isFullscreen)
{
	//initialise game screen with passed values 
	if (!(Screen::Instance()->
		Initialize(name.c_str(), screenWidth, screenHeight, pixelsPerUnit, 4, 5, true, isFullscreen)))
	{
		return false;
	}

	return true;
}
//======================================================================================================
bool Game::Run()
{
	while (!m_endGame)
	{

		//update and render all objects while the current state is active
		//each state will flag itself as inactive after which the loop breaks
		while (1)
		{

			//save time value to mark the start of the frame
			int startTime = SDL_GetTicks();

			//update screen by clearing OpenGL frame buffer
			Screen::Instance()->Clear();

			//update input handling by listening for input events
			Input::Instance()->Update();

			//draw screen by swapping OpenGL frame buffer
			Screen::Instance()->Present();

			//calculate time value passed for one frame call
			//if vsync is on this value should be around 16ms
			m_deltaTime = SDL_GetTicks() - startTime;

		}

	}

	return true;
}
//======================================================================================================
void Game::ShutDown()
{
	//close down game screen 
	Screen::Instance()->ShutDown();
}