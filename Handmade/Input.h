#ifndef INPUT_H
#define INPUT_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Input' source files last updated in December 2019								            |
#==============================================================================================*/

#include <glm.hpp>
#include <SDL.h>

class Input
{

public:

	enum ButtonState { UP, DOWN };
	enum CursorState { ON = 1, OFF = 0, SHOW = 1, HIDE = 0 };
	enum CursorType  { ARROW, IBEAM, WAIT, CROSSHAIR, WAIT_ARROW, NO = 10, HAND = 11 };

public:

    static Input* Instance();

public:

	bool IsXClicked();
	bool IsKeyPressed();
	const Uint8* GetKeyStates();
	//bool IsMouseColliding(const AABB2D& bound);
	//bool IsMouseColliding(const Sphere2D& bound);

public:

	glm::vec2 GetMousePosition();
	glm::vec2 GetMouseMotion();
	glm::vec2 GetMouseWheel();	
	
	ButtonState GetLeftButtonState();
	ButtonState GetMiddleButtonState();
	ButtonState GetRightButtonState();

	void SetMousePosition(int x, int y);
	void SetMouseCursorType(CursorType cursorType = ARROW);
	void SetMouseCursorState(CursorState cursorEnabled = ON, CursorState cursorVisible = SHOW);

public:

	void Update();

private:

	Input();
	Input(const Input&);
	Input& operator=(const Input&);

private:

	bool m_isXClicked;
	bool m_isKeyPressed;
	const Uint8* m_keyStates;

	SDL_Cursor* m_cursor;

	glm::vec2 m_mousePosition;
	glm::vec2 m_mouseMotion;
	glm::vec2 m_mouseWheel;
	
	ButtonState m_leftButtonState;
	ButtonState m_middleButtonState;
	ButtonState m_rightButtonState;

};

#endif