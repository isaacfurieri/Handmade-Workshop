#include "AudioManager.h"
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

	//initialize FMOD audio sub-system and return false if error occured
	if (!(AudioManager::Instance()->Initialize()))
	{
		return false;
	}

	return true;
}
//======================================================================================================
void Game::AddState(GameState* state)
{
	state->OnEnter();
	m_gameStates.push_front(state);
}
//======================================================================================================
void Game::ChangeState(GameState* state)
{
	state->OnEnter();
	m_gameStates.push_back(state);
}
//======================================================================================================
bool Game::Run()
{
	GameState* state;

	//main game loop!
	while (!m_endGame)
	{

		//current active state is always the front one
		state = m_gameStates.front();

		//update and render all objects while the current state is active
		//each state will flag itself as inactive after which the loop breaks
		while (state->IsActive())
		{

			//save time value to mark the start of the frame
			int startTime = SDL_GetTicks();

			//update FMOD audio sub-system
			AudioManager::Instance()->Update();

			//update screen by clearing OpenGL frame buffer
			Screen::Instance()->Clear();

			//update input handling by listening for input events
			Input::Instance()->Update();

			//update the currently active state
			state->Update(m_deltaTime);

			//render the currently active state
			state->Draw();

			//draw screen by swapping OpenGL frame buffer
			Screen::Instance()->Present();

			//calculate time value passed for one frame call
			//if vsync is on this value should be around 16ms
			m_deltaTime = SDL_GetTicks() - startTime;

		}

		//if game state is also flagged as dead  
		//then completely remove all of its objects
		if (!state->IsAlive())
		{
			RemoveState();
		}

		//the main game loop will run as long there are game states available
		m_endGame = m_gameStates.empty();

	}

	return true;
}
//======================================================================================================
void Game::ShutDown()
{
	//close down FMOD audio sub-system 
	AudioManager::Instance()->ShutDown();

	//close down game screen 
	Screen::Instance()->ShutDown();
}
//======================================================================================================
void Game::RemoveState()
{
	m_gameStates.front()->OnExit();

	delete m_gameStates.front();
	m_gameStates.pop_front();
}