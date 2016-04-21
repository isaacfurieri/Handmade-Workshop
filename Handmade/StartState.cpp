#include "ShaderManager.h"
#include "StartState.h"

//------------------------------------------------------------------------------------------------------
//function that creates the main shaders for the entire game
//------------------------------------------------------------------------------------------------------
bool StartState::OnEnter()
{

	//create vertex shader for main program and return false if there are errors
	if (!(TheShader::Instance()->Create(ShaderManager::VERTEX_SHADER, "MAIN_VERTEX_SHADER")))
	{
		return false;
	}

	//create fragment shader for main program and return false if there are errors
	if (!(TheShader::Instance()->Create(ShaderManager::FRAGMENT_SHADER, "MAIN_FRAGMENT_SHADER")))
	{
		return false;
	}

	//compile vertex shader for main program and return false if there are errors
	if (!(TheShader::Instance()->Compile(ShaderManager::VERTEX_SHADER,
		                                 "Shaders\\Main.vert", "MAIN_VERTEX_SHADER")))
	{
		return false;
	}

	//compile fragment shader for main program and return false if there are errors
	if (!(TheShader::Instance()->Compile(ShaderManager::FRAGMENT_SHADER,
		                                 "Shaders\\Main.frag", "MAIN_FRAGMENT_SHADER")))
	{
		return false;
	}

	//create both splash screen objects for state
	m_APILogo = new SplashScreen("Sprites\\APIs.jpg");
	m_handmadeLogo = new SplashScreen("Sprites\\Handmade.jpg");

	//set second splash screen to inactive as 
	//it only activates after the first one is done
	m_APILogo->IsActive() = false;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates splash screen objects 
//------------------------------------------------------------------------------------------------------
bool StartState::Update()
{

#ifdef DEBUG

	m_isActive = false;

#endif

#ifdef RELEASE

	//if first splash screen is active then update it
	if (m_handmadeLogo->IsActive())
	{
		m_handmadeLogo->Update();
	}

	//otherwise activate second splash screen so that it can start updating
	else
	{
		m_APILogo->IsActive() = true;
	}

	//if second splash screen is active then update it and monitor its active 
	//state so that game state deactivates as soon as second splash screen is done
	if (m_APILogo->IsActive())
	{
		m_APILogo->Update();
		m_isActive = m_APILogo->IsActive();
	}

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders splash screen objects 
//------------------------------------------------------------------------------------------------------
bool StartState::Draw()
{

#ifdef RELEASE

	if (m_handmadeLogo->IsActive())
	{
		m_handmadeLogo->Draw();
	}

	if (m_APILogo->IsActive())
	{
		m_APILogo->Draw();
	}

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys the two splash screen objects
//------------------------------------------------------------------------------------------------------
void StartState::OnExit()
{

	delete m_handmadeLogo;
	delete m_APILogo;

}