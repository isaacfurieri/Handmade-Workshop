#include "Input.h"
#include "Screen.h"

//======================================================================================================
Input* Input::Instance()
{
	static Input* inputObject = new Input();
	return inputObject;
}
//======================================================================================================
Input::Input()
{
	m_keyUp = 0;
	m_keyDown = 0;

	m_cursor = nullptr;
	m_keyStates = nullptr;

	m_isXClicked = false;
	m_isKeyPressed = false;
	m_isWindowResized = false;

	m_mouseWheel = glm::ivec2(0);
	m_mouseMotion = glm::ivec2(0);
	m_mousePosition = glm::ivec2(0);

	m_isLeftButtonClicked = false;
	m_isRightButtonClicked = false;
	m_isMiddleButtonClicked = false;
}
//======================================================================================================
bool Input::IsXClicked() const
{
	return m_isXClicked;
}
//======================================================================================================
bool Input::IsKeyPressed() const
{
	return m_isKeyPressed;
}
//======================================================================================================
bool Input::IsWindowResized() const
{
	return m_isWindowResized;
}
//======================================================================================================
bool Input::IsLeftButtonClicked() const
{
	return m_isLeftButtonClicked;
}
//======================================================================================================
bool Input::IsRightButtonClicked() const
{
	return m_isRightButtonClicked;
}
//======================================================================================================
bool Input::IsMiddleButtonClicked() const
{
	return m_isMiddleButtonClicked;
}
//======================================================================================================
const glm::ivec2& Input::GetMouseWheel() const
{
	return m_mouseWheel;
}
//======================================================================================================
const glm::ivec2& Input::GetMouseMotion() const
{
	return m_mouseMotion;
}
//======================================================================================================
const glm::ivec2& Input::GetMousePosition() const
{
	return m_mousePosition;
}
//======================================================================================================
char Input::GetKeyUp() const
{
	return m_keyUp;
}
//======================================================================================================
char Input::GetKeyDown() const
{
	return m_keyDown;
}
//======================================================================================================
KeyState Input::GetKeyStates() const
{
	return m_keyStates;
}
//======================================================================================================
void Input::SetCursorType(CursorType cursorType)
{
	SDL_FreeCursor(m_cursor);
	m_cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursorType));
	SDL_SetCursor(m_cursor);
}
//======================================================================================================-
void Input::SetCursorState(CursorState cursorEnabled, CursorState cursorVisible)
{
	//If mouse cursors are enabled that means they stay within the bounds 
	//of the window. On top of that they can still be visible or hidden
	if (static_cast<bool>(cursorEnabled))
	{
		if (static_cast<bool>(cursorVisible))
		{
			SDL_ShowCursor(static_cast<int>(CursorState::Show));
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		else
		{
			SDL_ShowCursor(static_cast<int>(CursorState::Hide));
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}

	else
	{
		SDL_ShowCursor(static_cast<int>(CursorState::Hide));
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}
//======================================================================================================
void Input::Update()
{
	//This variable is declared locally 
	//so that it has no left over data
	SDL_Event events;

	m_isXClicked = false;
	m_isWindowResized = false;
	m_mouseWheel = glm::ivec2(0);
	m_mouseMotion = glm::ivec2(0);

	m_keyStates = SDL_GetKeyboardState(nullptr);

	//We check for events on SDL's event queue and keep 
	//this loop running until all events have been processed
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_WINDOWEVENT:
		{
			if (events.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				m_isWindowResized = true;
			}

			break;
		}

		case SDL_QUIT:
		{
			m_isXClicked = true;
			break;
		}

		case SDL_KEYUP:
		{
			m_isKeyPressed = false;
			m_keyUp = events.key.keysym.sym;
			break;
		}

		case SDL_KEYDOWN:
		{
			m_isKeyPressed = true;
			m_keyUp = events.key.keysym.sym;
			break;
		}

		case SDL_MOUSEMOTION:
		{
			m_mousePosition.x = events.motion.x;
			m_mousePosition.y = events.motion.y;
			m_mouseMotion.x = events.motion.xrel;
			m_mouseMotion.y = events.motion.yrel;
			break;
		}

		case SDL_MOUSEWHEEL:
		{
			m_mouseWheel.x = events.wheel.x;
			m_mouseWheel.y = events.wheel.y;
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT: { m_isLeftButtonClicked = false; break; }
			case SDL_BUTTON_RIGHT: { m_isRightButtonClicked = false; break; }
			case SDL_BUTTON_MIDDLE: { m_isMiddleButtonClicked = false; break; }
			}

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT: { m_isLeftButtonClicked = true; break; }
			case SDL_BUTTON_RIGHT: { m_isRightButtonClicked = true; break; }
			case SDL_BUTTON_MIDDLE: { m_isMiddleButtonClicked = true; break; }
			}
			break;
		}
		}
	}
}