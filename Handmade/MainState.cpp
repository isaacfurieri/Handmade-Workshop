#include "BufferManager.h"
#include "MainState.h"
#include "ScreenManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//function that creates the shaders, HUD VBOs and all the game objects for the state
//------------------------------------------------------------------------------------------------------
bool MainState::OnEnter()
{

#ifdef DEBUG

	m_grid = new Grid();

#endif

	//create the main camera to control the main view
	m_mainCamera = new MainCamera();

	//create the 2D camera for HUDs and sprite objects
	m_HUDCamera = new HUDCamera();

	//create a heads-up display object
	m_HUD = new HUD();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates all active game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Update()
{

	//update main camera
	m_mainCamera->Update();

	//if camera has received flag to end state then
	//set game state active flag based on camera flag 
	m_isActive = m_mainCamera->IsActive();

	//loop through all game objects in vector and update them only if they are active
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive())
		{
			(*it)->Update();
		}
	}	

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that displays all active and visible game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Draw()
{

#ifdef GAME_3D

	TheScreen::Instance()->Set3DScreen(60.0f, 0.1f, 1000.0f);
	
#endif

#ifdef GAME_2D

	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

#endif

	//first set up camera which sets the view accordingly
	m_mainCamera->Draw();

#ifdef DEBUG

	m_grid->Draw();

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

	//set the 2D camera and render the heads-up display last
	m_HUDCamera->Draw();
	m_HUD->Draw();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys all the game objects for the state
//------------------------------------------------------------------------------------------------------
void MainState::OnExit()
{

	//loop through all game objects in vector and remove them from memory
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete (*it);
	}

	//clear the game object vector
	m_gameObjects.clear();

	//destroy the HUD, camera and grid objects
	delete m_HUD;
	delete m_HUDCamera;
	delete m_mainCamera;
	delete m_grid;
	
}