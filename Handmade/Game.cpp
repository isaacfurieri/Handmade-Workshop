#include "AudioManager.h"
#include "DebugManager.h"
#include "Game.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "ScreenManager.h"
#include "TimeManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Game::Game()
{

	m_activeGameState = 0;
	m_gameStateManager.reserve(5);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns address of active game state
//------------------------------------------------------------------------------------------------------
GameState* Game::GetActiveGameState()
{

	return m_activeGameState;

}
//------------------------------------------------------------------------------------------------------
//setter function that adds a game state to the end of the vector container 
//------------------------------------------------------------------------------------------------------
void Game::AddGameState(GameState* gameState)
{

	m_gameStateManager.push_back(gameState);

}
//------------------------------------------------------------------------------------------------------
//function that initializes all other managers of the game
//------------------------------------------------------------------------------------------------------
bool Game::Initialize(std::string name, int screenWidth, int screenHeight, 
	                  int pixelScaleValue, bool fullscreen)
{

	//initialise game screen with passed values and return false if error occured
	if(!(TheScreen::Instance()->
		 Initialize(name.c_str(), screenWidth, screenHeight, pixelScaleValue, 4.0, true, fullscreen)))
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

//if the game is in debug mode initialize 
//debug manager and all its shaders and components 
#ifdef DEBUG

	if (!TheDebug::Instance()->Initialize())
	{
		return false;
	}

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that runs the game while at least one game state is active
//------------------------------------------------------------------------------------------------------
bool Game::Run()
{

	//start SDL timer sub-system
	TheTime::Instance()->Start();

	//run game indefinately until no more game states are 
	//available at which point the game loop will break
	while (1)
	{

		//if there are no game states available break out of loop
		if (m_gameStateManager.size() == 0)
		{
			break;
		}

		//otherwise assign game state to active game state pointer
		m_activeGameState = *(m_gameStateManager.end() - 1);

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

			//update FMOD audio sub-system
			TheAudio::Instance()->Update();

			//update SDL timer sub-system
			TheTime::Instance()->Update();

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

		}

		//call the active game state's shutdown tasks
		m_activeGameState->OnExit();
	
		//reset active game state pointer and
		//remove game state from vector container
		m_activeGameState = 0;
		m_gameStateManager.pop_back();
		
	}

	//stop SDL timer sub-system
	TheTime::Instance()->Stop();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down all other managers of the game
//------------------------------------------------------------------------------------------------------
void Game::ShutDown()
{

//if the game is in debug mode shutdown 
//debug manager and all its shaders and components 
#ifdef DEBUG

	TheDebug::Instance()->ShutDown();

#endif

	//close down shader manager 
	TheShader::Instance()->ShutDown();

	//close down FMOD audio sub-system 
	TheAudio::Instance()->ShutDown();

	//close down game screen 
	TheScreen::Instance()->ShutDown();

}