#include "Camera.h"
#include "Debug.h"
#include "Game.h"
#include "GameObject.h"
#include "MainState.h"
#include "Shader.h"
#include "Screen.h"
#include "StartState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
StartState::StartState(GameState* state) : GameState(state)
{

	m_HUDCamera = nullptr;
	m_splashScreen_1 = nullptr;
	m_splashScreen_2 = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that creates the main shaders for the entire game
//------------------------------------------------------------------------------------------------------
bool StartState::OnEnter()
{

	//create shader program for the main shaders
	if (!(Shader::Instance()->CreateProgram()))
	{
		return false;
	}

	//create vertex and fragment shader objects for main program
	if (!(Shader::Instance()->CreateShaders()))
	{
		return false;
	}

	//compile vertex shader for main program 
	if(!(Shader::Instance()->CompileShader(Shader::VERTEX_SHADER, "Shaders\\Main.vert")))
	{
		return false;
	}

	//compile fragment shader for main program 
	if(!(Shader::Instance()->CompileShader(Shader::FRAGMENT_SHADER, "Shaders\\Main.frag")))
	{
		return false;
	}

	//attach both shaders to the main shader program
	Shader::Instance()->AttachShaders();

	//link main shader program
	if (!Shader::Instance()->LinkProgram())
	{
		return false;
	}

	//create 2D camera to view the splash images
	m_HUDCamera = new HUDCamera();

	//create both splash screen objects for state
	m_splashScreen_1 = new SplashScreen("Assets\\Sprites\\SplashScreen_1.png");
	m_splashScreen_2 = new SplashScreen("Assets\\Sprites\\SplashScreen_2.png");
	
	//create the buffers for the sprite images
	m_splashScreen_1->Create();
	m_splashScreen_2->Create();

	//set second splash screen to inactive as 
	//it only activates after the first one is done
	m_splashScreen_2->IsActive() = false;
	
	//if the game is in debug mode initialize the 
	//debug manager and all of its debug objects 
#ifdef DEBUG

	if (!Debug::Instance()->CreateDebugObjects(15))
	{
		return false;
	}

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates splash screen objects 
//------------------------------------------------------------------------------------------------------
bool StartState::Update()
{

	//if in debug mode, go straight through to the main state
	//because we don't want to bother with menus and start screens
#ifdef DEBUG

	m_isActive = m_isAlive = false;
	Game::Instance()->ChangeState(new MainState(this));

#endif

#ifdef RELEASE

	//if first splash screen is active then update it
	if (m_splashScreen_1->IsActive())
	{
		m_splashScreen_1->Update();
	}

	//otherwise activate second splash screen so that it can start updating
	else
	{
		m_splashScreen_2->IsActive() = true;
	}

	//if second splash screen is active then update it and monitor its active 
	//state so that game state deactivates as soon as second splash screen is done
	if (m_splashScreen_2->IsActive())
	{
		m_splashScreen_2->Update();
		m_isActive = m_isAlive = m_splashScreen_2->IsActive();
	}

	//load up next state as soon as this one is done with all the splash screens
	if (!m_isAlive)
	{
		TheGame::Instance()->ChangeState(new MainState(this));
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

	if (m_splashScreen_1->IsActive())
	{
		m_HUDCamera->Draw();
		m_splashScreen_1->Draw();
	}

	if (m_splashScreen_2->IsActive())
	{
		m_HUDCamera->Draw();
		m_splashScreen_2->Draw();
	}

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys the two splash screen and camera objects
//------------------------------------------------------------------------------------------------------
void StartState::OnExit()
{

	m_splashScreen_1->Destroy();
	m_splashScreen_2->Destroy();

	delete m_splashScreen_2;
	delete m_splashScreen_1;
	delete m_HUDCamera;

}