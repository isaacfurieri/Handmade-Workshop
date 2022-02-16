#include <assert.h>
#include "App.h"
#include "Input.h"
#include "Screen.h"

//TODO test

//======================================================================================================
App::App(State* initialState)
{
	m_deltaTime = 0;
	m_appState.reset(initialState);

	if (Initialize())
	{
		if (CreateObjects())
		{
			//??
		}
	}
}
//======================================================================================================
App::~App()
{
	Shutdown();
}
//======================================================================================================
void App::Run()
{
	if (m_appState)
	{
		m_appState->OnEnter();
	}

	while (m_appState)
	{
		int startTime = SDL_GetTicks();

		Screen::Instance()->Refresh();
		Input::Instance()->Update();

		State* nextState = m_appState->Update(m_deltaTime);

		m_appState->Render();

		Screen::Instance()->Present();

		if (nextState != m_appState.get())
		{
			m_appState->OnExit();
			m_appState.reset(nextState);

			if (m_appState)
			{
				m_appState->OnEnter();
			}
		}

		m_deltaTime = SDL_GetTicks() - startTime;
	}
}
//======================================================================================================
bool App::Initialize()
{
	if (!Screen::Instance()->Initialize("Data/Config.ini"))
	{
		return false;
	}

	return true;
}
//======================================================================================================
bool App::CreateObjects()
{
	return true;
}
//======================================================================================================
void App::Shutdown()
{
	Screen::Instance()->Shutdown();
}