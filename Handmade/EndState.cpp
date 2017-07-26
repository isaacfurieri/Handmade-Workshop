#include "DebugManager.h"
#include "EndState.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------
//function that creates ending splash screen message and 2D camera for state
//------------------------------------------------------------------------------------------------------
bool EndState::OnEnter()
{
 
	m_HUDCamera = new HUDCamera();
	m_splashScreen = new SplashScreen("Assets\\Sprites\\SplashScreen_3.png");
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates splash screen object 
//------------------------------------------------------------------------------------------------------
bool EndState::Update()
{

#ifdef DEBUG

	m_isActive = false;

#endif

#ifdef RELEASE

	m_splashScreen->Update();
	m_isActive = m_splashScreen->IsActive();

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

	TheDebug::Instance()->DestroyBuffers();

#endif

	TheShader::Instance()->
	Destroy(ShaderManager::VERTEX_SHADER, ShaderManager::CUSTOM_SHADER, "MAIN_VERTEX_SHADER");
	TheShader::Instance()->
	Destroy(ShaderManager::FRAGMENT_SHADER, ShaderManager::CUSTOM_SHADER, "MAIN_FRAGMENT_SHADER");

	delete m_splashScreen;
	delete m_HUDCamera;

}