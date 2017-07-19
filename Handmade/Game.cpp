#include "AudioManager.h"
#include "DebugManager.h"
#include "Game.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Game::Game()
{

	m_elapsedTime = 0;
	m_activeGameState = 0;
	m_gameStates.reserve(5);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in hours
//------------------------------------------------------------------------------------------------------
double Game::GetElapsedTimeHours()
{

	return (double)m_elapsedTime / 3600000;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in minutes
//------------------------------------------------------------------------------------------------------
double Game::GetElapsedTimeMinutes()
{

	return (double)m_elapsedTime / 60000;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in seconds
//------------------------------------------------------------------------------------------------------
double Game::GetElapsedTimeSeconds()
{
	
	return (double)m_elapsedTime / 1000;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in milliseconds
//------------------------------------------------------------------------------------------------------
int Game::GetElapsedTimeMilliseconds()
{

	return m_elapsedTime;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in hours
//------------------------------------------------------------------------------------------------------
double Game::GetTotalTimeHours()
{

	return (double)SDL_GetTicks() / 3600000;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in minutes
//------------------------------------------------------------------------------------------------------
double Game::GetTotalTimeMinutes()
{

	return (double)SDL_GetTicks() / 60000;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in seconds
//------------------------------------------------------------------------------------------------------
double Game::GetTotalTimeSeconds()
{

	return (double)SDL_GetTicks() / 1000;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in milliseconds
//------------------------------------------------------------------------------------------------------
int Game::GetTotalTimeMilliseconds()
{

	return SDL_GetTicks();

}
//------------------------------------------------------------------------------------------------------
//function that adds a game state to the end of the vector  
//------------------------------------------------------------------------------------------------------
void Game::AddGameState(GameState* gameState)
{

	m_gameStates.push_back(gameState);

}
//------------------------------------------------------------------------------------------------------
//function that removes a game state from the middle of the vector based on index value passed 
//------------------------------------------------------------------------------------------------------
void Game::RemoveGameState(int index)
{

	m_gameStates.erase(m_gameStates.begin() + index);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns address of active game state
//------------------------------------------------------------------------------------------------------
GameState* Game::GetActiveGameState()
{

	return m_activeGameState;

}
//------------------------------------------------------------------------------------------------------
//function that initializes all other managers of the game
//------------------------------------------------------------------------------------------------------
bool Game::Initialize(std::string name, int screenWidth, int screenHeight, 
	                  int pixelScaleValue, bool fullscreen)
{

	//initialise game screen with passed values and return false if error occured
	if(!(TheScreen::Instance()->
		 Initialize(name.c_str(), screenWidth, screenHeight, pixelScaleValue, 3, 0, true, fullscreen)))
	{
		return false;
	}

	//initialize FMOD audio sub-system and return false if error occured
	if (!(TheAudio::Instance()->Initialize()))
	{
		return false;
	}

	//initialize shader manager and return false if error occured
	if (!TheShader::Instance()->Initialize())
	{
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that runs the game while at least one game state is active
//------------------------------------------------------------------------------------------------------
bool Game::Run()
{

	//run game indefinately until no more game states are 
	//available at which point the game loop will break
	while (1)
	{

		//if there are no game states available break out of loop
		if (m_gameStates.size() == 0)
		{
			break;
		}

		//otherwise assign game state to active game state pointer
		m_activeGameState = *(m_gameStates.end() - 1);

		//set the state's active flag to enable main loop below 
		m_activeGameState->IsActive() = true;

		//call the active game state's start up tasks
		if (!(m_activeGameState->OnEnter()))
		{
			return false;
		}

		//keep looping while current game state is active
		while (m_activeGameState->IsActive())
		{

			//save time value to mark the start of the frame
			int startTime = SDL_GetTicks();

			//update FMOD audio sub-system
			TheAudio::Instance()->Update();

			//update screen by clearing OpenGL frame buffer
			TheScreen::Instance()->Update();
		
			//update input handling by listening for input events
			TheInput::Instance()->Update();

			//update components in active game state
			if (!m_activeGameState->Update())
			{
				return false;
			}

			//draw components in active game state
			if (!m_activeGameState->Draw())
			{
				return false;
			}

			//draw screen by swapping OpenGL frame buffer
			TheScreen::Instance()->Draw();

			//calculate time value passed for one frame call
			//if vsync is on this value should be around 16ms
			m_elapsedTime = SDL_GetTicks() - startTime;

		}

		//call the active game state's shutdown tasks
		m_activeGameState->OnExit();
	
		//reset active game state pointer and
		//remove game state from vector container
		m_activeGameState = 0;
		m_gameStates.pop_back();
		
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down all other managers of the game
//------------------------------------------------------------------------------------------------------
void Game::ShutDown()
{

	//close down shader manager 
	TheShader::Instance()->ShutDown();

	//close down FMOD audio sub-system 
	TheAudio::Instance()->ShutDown();

	//close down game screen 
	TheScreen::Instance()->ShutDown();

}