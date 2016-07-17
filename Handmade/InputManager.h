/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2015

  -----------------------------------------------------------------------------------------------

- This is a Singleton Manager class that controls all the input from the mouse and keyboard (More
  controls later!!) It uses a set of SDL library tools to manage the input and stores the mouse 
  and keyboard values in various property variables. The class as a whole can determine what keys
  have been pressed and what state the mouse buttons are in, and these states can be queried from
  external code at any time.

- An enumerated type has been created to be used when storing the button states of the mouse buttons.

- The class variables store all the details of the mouse and keyboard and the m_isXClicked and 
  m_isKeyPressed variables store whether the X in the top right corner of the game window has been 
  clicked or whether a keyboard key has been pressed or not respectively. The m_isKeyPressed
  variable is handy if you want to quickly check if a random key has been pressed or released as 
  opposed to checking each key's state. For that there is a separate variable called m_keyStates.
  The m_keyStates variable, which is a pointer to an array of Uint8 values, is filled each time a key
  is pressed and will store a kind of binary snapshot of the keyboard, stating which keys are pressed,
  and which are not. Each individual element in the array represents a key on the keyboard and can be 
  queried in the client code as to whether that key is pressed or not.
  Three button state variables store the pressed state of the three mouse buttons. This is perfect 
  for mouse functions, but for keyboard keys there are too many keys to individually set their state
  so for that there is a separate keystate array variable.

- For each class property variable there is a getter function for when mouse and keyboard states are
  queried in the client code. No setters are neccessary as only the Input Manager can set them.

- The Update() function is the core of the Input Manager class. It will process all SDL events that
  build up on the event queue and will store particular keyboard and mouse property values in the 
  relevant variables. These values can then be used at any time in the client code. This routine will
  need to be called once per frame in the client code.

*/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>
#include "Singleton.h"
#include "Vector2D.h"

class InputManager
{

public :

	enum ButtonState { UP, DOWN };
	enum CursorState { CURSOR_ON, CURSOR_OFF };

public :

	friend class Singleton<InputManager>;

public :

	bool IsXClicked();
	bool IsKeyPressed();
	const Uint8* GetKeyStates();

public :

	ButtonState GetLeftButtonState();
	ButtonState GetMiddleButtonState();
	ButtonState GetRightButtonState();

	Vector2D<Sint32> GetMousePosition();
	Vector2D<Sint32> GetMouseMotion();
	Vector2D<Sint32> GetMouseWheel();	
	
	void SetMouseCursor(CursorState mouseCursor);

public :

	void Update();

private :

	InputManager();
	InputManager(const InputManager&);
	InputManager& operator=(const InputManager&);

private :

	bool m_isXClicked;
	bool m_isKeyPressed;
	
	const Uint8* m_keyStates;

	ButtonState m_leftButtonState;
	ButtonState m_middleButtonState;
	ButtonState m_rightButtonState;

	Vector2D<Sint32> m_mousePosition;
	Vector2D<Sint32> m_mouseMotion;
	Vector2D<Sint32> m_mouseWheel;
	
};

typedef Singleton<InputManager> TheInput;

#endif