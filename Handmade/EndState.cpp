#include "Debug.h"
#include "EndState.h"
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
EndState::EndState(Game* game, GameState* state) : GameState(game, state)
{

	m_HUDCamera = nullptr;
	m_splashScreen = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that creates ending splash screen message and 2D camera for state
//------------------------------------------------------------------------------------------------------
bool EndState::OnEnter()
{
 
	m_HUDCamera = new HUDCamera();
	m_splashScreen = new SplashScreen("Assets\\Sprites\\SplashScreen_3.png");
	m_splashScreen->Create();
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates splash screen object 
//------------------------------------------------------------------------------------------------------
bool EndState::Update(int deltaTime)
{

	//if in debug mode, go straight through and end the state
	//because we don't want to bother with ending screens
#ifdef DEBUG

	m_isActive = m_isAlive = false;

#endif

#ifdef RELEASE

	m_splashScreen->Update(deltaTime);
	m_isActive = m_isAlive = m_splashScreen->IsActive();

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders splash screen object
//------------------------------------------------------------------------------------------------------
bool EndState::Draw()
{

#ifdef RELEASE

	m_HUDCamera->Draw();
	m_splashScreen->Draw();

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys the main program shaders that were created in the Start State
//------------------------------------------------------------------------------------------------------
void EndState::OnExit()
{

	//if the game is in debug mode shutdown the
	//debug manager and all of its components 
#ifdef DEBUG

	//Debug::Instance()->DestroyDebugObjects();

#endif

	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();

	m_splashScreen->Destroy();
	delete m_splashScreen;
	delete m_HUDCamera;

}