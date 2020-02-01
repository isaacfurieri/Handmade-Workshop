#include "Debug.h"
#include "EndState.h"
#include "Input.h"
#include "Game.h"
#include "MainState.h"
#include "Shader.h"
#include "Screen.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
MainState::MainState(Game* game, GameState* state) : GameState(game, state)
{

	m_HUD = nullptr;
	m_HUDCamera = nullptr;
	m_mainCamera = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that creates the cameras and HUD objects
//------------------------------------------------------------------------------------------------------
bool MainState::OnEnter()
{

	//create the main camera to control the main view
	m_mainCamera = new MainCamera();

	//create the 2D camera for HUDs and sprite objects
	m_HUDCamera = new HUDCamera();

	//create a heads-up display object
	m_HUD = new HUD();
	m_HUD->Create();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates all active game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Update(int deltaTime)
{

	//store keyboard key states in a temp variable for processing below
	KeyState keyState = Input::Instance()->GetKeyStates();

	//update main camera
	m_mainCamera->Update(deltaTime);

	//if ESCAPE key was pressed, return flag to end game 
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		m_isActive = m_isAlive = false;
		m_game->ChangeState(new EndState(m_game, this));
	}

	//loop through all game objects in vector and update them only if they are active
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(deltaTime);
		}
	}	

	//ADD YOUR CODE HERE...
	//...

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that displays all active and visible game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Draw()
{

	//first set up camera which sets the view accordingly
	//make sure this is called BEFORE displaying the grid
	m_mainCamera->Draw();

#ifdef GAME_3D

	//Screen::Instance()->Set3DScreen(45.0f, 0.1f, 1000.0f);

#ifdef DEBUG

	//Debug::Instance()->DrawGrid3D();
	//Debug::Instance()->DrawCoordSystem3D(15.0f);

#endif
	
#endif

#ifdef GAME_2D

	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

#ifdef DEBUG

	TheDebug::Instance()->DrawGrid2D();
	TheDebug::Instance()->DrawCoordSystem2D(15.0f);

#endif

#endif

	//loop through all game objects in vector and 
	//display them only if they are active and visible
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive() && (*it)->IsVisible())
		{
			(*it)->Draw();
		}
	}

	//ADD YOUR CODE HERE...
	//...

#ifdef DEBUG

	//set the 2D camera and render the heads-up display last
	m_HUDCamera->Draw();
	m_HUD->Draw();

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys all the game objects for the state
//------------------------------------------------------------------------------------------------------
void MainState::OnExit()
{

	//destroy the HUD, camera and grid objects
	m_HUD->Destroy();
	delete m_HUD;
	delete m_HUDCamera;
	delete m_mainCamera;

	//loop through all game objects in vector and remove them from memory
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete (*it);
	}

	//clear the game object vector
	m_gameObjects.clear();

}