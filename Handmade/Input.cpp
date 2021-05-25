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
	m_keyStates = 0;
	m_isXClicked = false;
	m_isKeyPressed = false;
	m_isWindowResized = false;

	m_cursor = nullptr;

	m_mouseWheel = glm::vec2(0.0f);
	m_mouseMotion = glm::vec2(0.0f);
	m_mousePosition = glm::vec2(0.0f);

	m_leftButtonState = ButtonState::UP;
	m_rightButtonState = ButtonState::UP;
	m_middleButtonState = ButtonState::UP;
}
//======================================================================================================
bool Input::IsXClicked()
{
	return m_isXClicked;
}
//======================================================================================================
bool Input::IsKeyPressed()
{
	return m_isKeyPressed;
}
//======================================================================================================
bool Input::IsWindowResized()
{
	return m_isWindowResized;
}
//======================================================================================================
KeyState Input::GetKeyStates()
{
	return m_keyStates;
}
//======================================================================================================
glm::vec2 Input::GetMousePosition()
{
	return m_mousePosition;
}
//======================================================================================================
glm::vec2 Input::GetMouseMotion()
{
	return m_mouseMotion;
}
//======================================================================================================
glm::vec2 Input::GetMouseWheel()
{
	return m_mouseWheel;
}
//======================================================================================================
Input::ButtonState Input::GetLeftButtonState()
{
	return m_leftButtonState;
}
//======================================================================================================
Input::ButtonState Input::GetMiddleButtonState()
{
	return m_middleButtonState;
}
//======================================================================================================
Input::ButtonState Input::GetRightButtonState()
{
	return m_rightButtonState;
}
//======================================================================================================
void Input::SetCursorPosition(int x, int y)
{
	//SDL_WarpMouseInWindow(Screen::Instance()->GetWindow(), x, y);
}
//======================================================================================================
void Input::SetCursorType(CursorType cursorType)
{
	//first destroy old cursor object from memory
	SDL_FreeCursor(m_cursor);

	//based on type of cursor value passed, create mouse cursor using SDL ID flag value 
	m_cursor = SDL_CreateSystemCursor(SDL_SystemCursor(cursorType));

	//use cursor pointer to assign cursor to SDL
	SDL_SetCursor(m_cursor);
}
//======================================================================================================-
void Input::SetCursorState(CursorState cursorEnabled, CursorState cursorVisible)
{
	//if mouse cursor is enabled then check if it's visible  
	//and display the cursor accordingly, and keep the mouse 
	//cursor within the window border as long as it's enabled
	if (static_cast<bool>(cursorEnabled))
	{
		if (static_cast<bool>(cursorVisible))
		{
			SDL_ShowCursor(1);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		else
		{
			SDL_ShowCursor(0);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}

	//if mouse cursor is disabled then hide it and free it from the window border
	else
	{
		SDL_ShowCursor(0);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}
//======================================================================================================
void Input::Update()
{
	//variable to store SDL event data
	SDL_Event events;

	//reset window quitting flag 
	m_isXClicked = false;

	//reset mouse wheel and motion so 
	//that it's processed from scratch
	m_mouseWheel.x = 0;
	m_mouseWheel.y = 0;
	m_mouseMotion.x = 0;
	m_mouseMotion.y = 0;
	m_isWindowResized = false;

	//store state of keyboard in array
	m_keyStates = SDL_GetKeyboardState(nullptr);

	//check for events on SDL event queue
	//keep this loop running until all events have been processed
	while (SDL_PollEvent(&events))
	{
		//check which type of event occurred and process accordingly
		switch (events.type)
		{

			//something occurred with the game window
			//so check if it's a window resize event
			//and set the internal flag accordingly
		case SDL_WINDOWEVENT:
		{
			if (events.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				m_isWindowResized = true;
			}

			break;
		}

		//top right X on game window has been clicked
		case SDL_QUIT:
		{
			m_isXClicked = true;
			break;
		}

		//a key is pressed 
		case SDL_KEYUP:
		{
			m_isKeyPressed = false;
			m_keyUp = events.key.keysym.sym;
			break;
		}

		//a key is released 
		case SDL_KEYDOWN:
		{
			m_isKeyPressed = true;
			m_keyUp = events.key.keysym.sym;
			break;
		}

		//the mouse was moved 
		//set the position and mouse motion value
		case SDL_MOUSEMOTION:
		{
			m_mousePosition.x = (float)events.motion.x;
			m_mousePosition.y = (float)events.motion.y;
			m_mouseMotion.x = (float)events.motion.xrel;
			m_mouseMotion.y = (float)events.motion.yrel;
			break;
		}

		//the mouse wheel was moved 
		case SDL_MOUSEWHEEL:
		{
			m_mouseWheel.x = (float)events.wheel.x;
			m_mouseWheel.y = (float)events.wheel.y;
		}

		//a mouse button was clicked or released
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
		{

			//set position of mouse
			m_mousePosition.x = (float)events.motion.x;
			m_mousePosition.y = (float)events.motion.y;

			//temporarily store button state for assigning below
			ButtonState state = ((events.button.state == SDL_PRESSED) ? ButtonState::DOWN : ButtonState::UP);

			//based on which of the three mouse buttons was pressed 
			//or released, assign flag to button's state variable
			switch (events.button.button)
			{

			case SDL_BUTTON_LEFT:
			{
				m_leftButtonState = state;
				break;
			}

			case SDL_BUTTON_MIDDLE:
			{
				m_middleButtonState = state;
				break;
			}

			case SDL_BUTTON_RIGHT:
			{
				m_rightButtonState = state;
				break;
			}

			break;

			}

			break;

		}

		}

	}
}