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
	m_axes2D = nullptr;
	m_axes3D = nullptr;
	m_grid2D = nullptr;
	m_grid3D = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that creates the cameras and HUD objects
//------------------------------------------------------------------------------------------------------
bool MainState::OnEnter()
{

	m_cameras.push_back(new FPSCamera);
	m_cameras.push_back(new UICamera);

	m_HUD = new HUD;
	m_HUD->Create();

	m_axes2D = new Axes2D;
	m_axes2D->Create();
	  
	m_axes3D = new Axes3D;
	m_axes3D->Create();

	m_grid2D = new Grid2D;
	m_grid2D->Create();

	m_grid3D = new Grid3D;
	m_grid3D->Create();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates all active game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Update(int deltaTime)
{

	//store keyboard key states in a temp variable for processing below
	KeyState keyState = Input::Instance()->GetKeyStates();

	//update all cameras
	for (auto it = m_cameras.begin(); it != m_cameras.end(); it++)
	{
		(*it)->Update(deltaTime);
	}

	//if ESCAPE key was pressed, return flag to end game 
	if (keyState[SDL_SCANCODE_ESCAPE] || Input::Instance()->IsXClicked())
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
	//..

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that displays all active and visible game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Draw()
{

#ifdef GAME_3D

	//first set up camera which sets the view accordingly
	//make sure this is called BEFORE displaying the grid
	m_cameras[0]->SetPerspView();
	m_cameras[0]->Draw();

#ifdef DEBUG

	m_grid3D->Draw();
	m_axes3D->Draw();

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
	//m_cameras[1]->SetOrthoView();
	//m_cameras[1]->Draw();  
	//m_grid2D->Draw();
	//m_axes2D->Draw();
	//m_HUD->Draw();

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

	m_grid2D->Destroy();
	delete m_grid2D;

	m_grid3D->Destroy();
	delete m_grid3D;

	m_axes2D->Destroy();
	delete m_axes2D;

	m_axes3D->Destroy();
	delete m_axes3D;

	//loop through all game objects in vector and remove them from memory
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete (*it);
	}

	for (auto it = m_cameras.begin(); it != m_cameras.end(); it++)
	{
		delete (*it);
	}

	//clear the game object vector
	m_gameObjects.clear();
	m_cameras.clear();

}