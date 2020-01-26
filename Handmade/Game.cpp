#include "AudioManager.h"
#include "Debug.h"
#include "Game.h"
#include "Input.h"
#include "Shader.h"
#include "Screen.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Game::Game()
{

	m_endGame = false;
	m_deltaTime = 0;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in milliseconds
//------------------------------------------------------------------------------------------------------
int Game::GetTotalTime()
{

	return SDL_GetTicks();

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in milliseconds
//------------------------------------------------------------------------------------------------------
int Game::GetElapsedTime()
{

	return m_deltaTime;

}
//------------------------------------------------------------------------------------------------------
//function that initializes all other managers of the game
//------------------------------------------------------------------------------------------------------
bool Game::Initialize(std::string name, int screenWidth, int screenHeight,
	                  int pixelsPerUnit, bool fullscreen)
{

	//initialise game screen with passed values 
	if (!(Screen::Instance()->
		Initialize(name.c_str(), screenWidth, screenHeight, pixelsPerUnit, 4, 0, true, fullscreen)))
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
//------------------------------------------------------------------------------------------------------
//function that loads and adds a game state to the front of the queue (for temporary states)
//------------------------------------------------------------------------------------------------------
void Game::AddState(GameState* state)
{

	state->OnEnter();
	m_gameStates.push_front(state);

}
//------------------------------------------------------------------------------------------------------
//function that loads and adds a game state to the back of the queue (for new states)
//------------------------------------------------------------------------------------------------------
void Game::ChangeState(GameState* state)
{

	state->OnEnter();
	m_gameStates.push_back(state);

}
//------------------------------------------------------------------------------------------------------
//function that runs the game while at least one game state is active
//------------------------------------------------------------------------------------------------------
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
			Screen::Instance()->ClearScreen();

			//update input handling by listening for input events
			Input::Instance()->Update();

			//update the currently active state
			state->Update(m_deltaTime);

			//render the currently active state
			state->Draw();

			//draw screen by swapping OpenGL frame buffer
			Screen::Instance()->SwapBuffer();

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
//------------------------------------------------------------------------------------------------------
//function that closes down all other managers of the game
//------------------------------------------------------------------------------------------------------
void Game::ShutDown()
{

	//close down FMOD audio sub-system 
	AudioManager::Instance()->ShutDown();

	//close down game screen 
	Screen::Instance()->ShutDown();

}
//------------------------------------------------------------------------------------------------------
//function that unloads and removes the front-most game state from the queue
//------------------------------------------------------------------------------------------------------
void Game::RemoveState()
{

	m_gameStates.front()->OnExit();

	delete m_gameStates.front();
	m_gameStates.pop_front();

}