#include "InputManager.h"
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
InputManager::InputManager()
{

	m_isXClicked = false;
	m_isKeyPressed = false;

	m_keyStates = 0;

	m_leftButtonState = UP;
	m_middleButtonState = UP;
	m_rightButtonState = UP;
	
}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if X has been clicked
//------------------------------------------------------------------------------------------------------
bool InputManager::IsXClicked()
{

	return m_isXClicked;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if a key has been pressed
//------------------------------------------------------------------------------------------------------
bool InputManager::IsKeyPressed()
{

	return m_isKeyPressed;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to array of key states
//------------------------------------------------------------------------------------------------------
const Uint8* InputManager::GetKeyStates()
{

	return m_keyStates;

}
//------------------------------------------------------------------------------------------------------
//predicate function that checks if mouse cursor collides with passed box bound
//------------------------------------------------------------------------------------------------------
bool InputManager::IsMouseColliding(const AABB2D& bound)
{

	//create a temporary bounding box to represent mouse cursor
	AABB2D tempBound;

	//set mouse cursor bounds of 1x1 based on mouse position
	//flip Y axis as mouse coordinates run from top to bottom
	tempBound.SetPosition(m_mousePosition.X,
					      TheScreen::Instance()->GetScreenSize().Y - m_mousePosition.Y);
	tempBound.SetDimension(1, 1);
	tempBound.Update();

	//return flag based on if mouse collides with bound
	return tempBound.IsColliding(bound);

}
//------------------------------------------------------------------------------------------------------
//predicate function that checks if mouse cursor collides with passed sphere bound
//------------------------------------------------------------------------------------------------------
bool InputManager::IsMouseColliding(const Sphere2D& bound)
{

	//create a temporary sphere bound to represent mouse cursor
	Sphere2D tempBound;

	//set mouse cursor radius of 1 based on mouse position
	//flip Y axis as mouse coordinates run from top to bottom
	tempBound.SetPosition(m_mousePosition.X,
		                  TheScreen::Instance()->GetScreenSize().Y - m_mousePosition.Y);
	tempBound.SetDimension(1);
	tempBound.Update();

	//return flag based on if mouse collides with bound
	return tempBound.IsColliding(bound);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of left mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetLeftButtonState()
{

	return m_leftButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of middle mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetMiddleButtonState()
{

	return m_middleButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of right mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetRightButtonState()
{

	return m_rightButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns position of mouse
//------------------------------------------------------------------------------------------------------
Vector2D<Sint32> InputManager::GetMousePosition()
{

	return m_mousePosition;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse movement
//------------------------------------------------------------------------------------------------------
Vector2D<Sint32> InputManager::GetMouseMotion()
{

	return m_mouseMotion;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse wheel movement
//------------------------------------------------------------------------------------------------------
Vector2D<Sint32> InputManager::GetMouseWheel()
{

	return m_mouseWheel;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets flag of mouse cursor to either display or hide it
//------------------------------------------------------------------------------------------------------
void InputManager::SetMouseCursor(CursorState mouseCursor)
{

	SDL_SetRelativeMouseMode((SDL_bool)mouseCursor);
	
}
//------------------------------------------------------------------------------------------------------
//function that processes all keyboard and mouse events
//------------------------------------------------------------------------------------------------------
void InputManager::Update()
{

	//variable to store SDL event data
	SDL_Event events;

	//if no events are occuring, then put CPU to sleep for a millisecond
	//this prevents CPU from running too much 
	if(!SDL_PollEvent(&events)) 
	{
		SDL_Delay(1);
	}
	
	//if previous event was valid, push it back on queue to be processed
	else 
	{
		SDL_PushEvent(&events);
	}

	//reset window quitting flag 
	m_isXClicked = false;

	//reset mouse motion so that it's processed from scratch
	m_mouseMotion = Vector2D<Sint32>::ZERO;

	//reset mouse wheel so that it's processed from scratch
	m_mouseWheel = Vector2D<Sint32>::ZERO;

	//store state of keyboard in array
	m_keyStates = SDL_GetKeyboardState(0);

	//check for events on SDL event queue
	//keep this loop running until all events have been processed
	while(SDL_PollEvent(&events))
	{
			
		//check which type of event occurred and process accordingly
		switch(events.type)
		{
		
			//top right X on game window has been clicked
			case SDL_QUIT :
			{
				m_isXClicked = true;
				break;
			}
		
			//a key is pressed 
			case SDL_KEYUP : 
			{
				m_isKeyPressed = false;
				break;
			}
		
			//a key is released 
			case SDL_KEYDOWN:
			{
				m_isKeyPressed = true;
				break;
			}

			//the mouse was moved 
			//set the position and mouse motion value
			case SDL_MOUSEMOTION :
			{
				m_mousePosition.X = events.motion.x;
				m_mousePosition.Y = events.motion.y;
				m_mouseMotion.X = events.motion.xrel;
				m_mouseMotion.Y = events.motion.yrel;
				break;
			}

			//the mouse wheel was moved 
			case SDL_MOUSEWHEEL :
			{
				m_mouseWheel.X = events.wheel.x;
				m_mouseWheel.Y = events.wheel.y;
			}

			//a mouse button was clicked or released
			case SDL_MOUSEBUTTONUP : case SDL_MOUSEBUTTONDOWN :
			{
				
				//set position of mouse
				m_mousePosition.X = events.motion.x;
				m_mousePosition.Y = events.motion.y;
				
				//temporarily store button state for assigning below
				ButtonState state = ((events.button.state == SDL_PRESSED) ? DOWN : UP);

				//based on which of the three mouse buttons was pressed 
				//or released, assign flag to button's state variable
				switch(events.button.button)
				{
				
					case SDL_BUTTON_LEFT :
					{
						m_leftButtonState = state;
						break;
					}
				
					case SDL_BUTTON_MIDDLE :
					{
						m_middleButtonState = state;
						break;
					}

					case SDL_BUTTON_RIGHT :
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