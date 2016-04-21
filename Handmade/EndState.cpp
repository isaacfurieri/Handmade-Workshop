#include "EndState.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------
//function that creates ending splash screen message for state
//------------------------------------------------------------------------------------------------------
bool EndState::OnEnter()
{
 
	m_endMessage = new SplashScreen("Sprites\\Credits.jpg");
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

	m_endMessage->Update();
	m_isActive = m_endMessage->IsActive();

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders splash screen object
//------------------------------------------------------------------------------------------------------
bool EndState::Draw()
{

#ifdef RELEASE

	m_endMessage->Draw();

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys the main program shaders that were created in the Start State
//------------------------------------------------------------------------------------------------------
void EndState::OnExit()
{

	TheShader::Instance()->
	Destroy(ShaderManager::VERTEX_SHADER, ShaderManager::CUSTOM_SHADER, "MAIN_VERTEX_SHADER");
	TheShader::Instance()->
	Destroy(ShaderManager::FRAGMENT_SHADER, ShaderManager::CUSTOM_SHADER, "MAIN_FRAGMENT_SHADER");

}