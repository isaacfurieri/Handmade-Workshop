#pragma once

/*===================================================================#
| 'Input' source files last updated on 25 May 2021                   |
#===================================================================*/

#include <glm.hpp>
#include <SDL.h>

//TODO - Add key bindings similar to Handmade Lite
//TODO - Refine class such that it follows newer design

typedef const Uint8* KeyState;

class Input
{

public:

	enum class ButtonState
	{
		UP,
		DOWN
	};

	enum class CursorState
	{
		ON = 1,
		OFF = 0,
		SHOW = 1,
		HIDE = 0
	};

	enum class CursorType
	{
		ARROW,
		IBEAM,
		WAIT,
		CROSSHAIR,
		WAIT_ARROW,
		NO = 10,
		HAND = 11
	};

	static Input* Instance();

	bool IsXClicked();
	bool IsKeyPressed();
	bool IsWindowResized();

	KeyState GetKeyStates();

	glm::vec2 GetMousePosition();
	glm::vec2 GetMouseMotion();
	glm::vec2 GetMouseWheel();

	ButtonState GetLeftButtonState();
	ButtonState GetMiddleButtonState();
	ButtonState GetRightButtonState();

	void SetCursorPosition(int x, int y);
	void SetCursorType(CursorType cursorType = CursorType::ARROW);
	void SetCursorState(CursorState cursorEnabled = CursorState::ON, CursorState cursorVisible = CursorState::SHOW);

	void Update();

private:

	Input();
	Input(const Input&);
	Input& operator=(const Input&);

	char m_keyUp;
	char m_keyDown;

	bool m_isXClicked;
	bool m_isKeyPressed;
	bool m_isWindowResized;

	KeyState m_keyStates;
	SDL_Cursor* m_cursor;

	glm::vec2 m_mouseWheel;
	glm::vec2 m_mouseMotion;
	glm::vec2 m_mousePosition;

	ButtonState m_leftButtonState;
	ButtonState m_rightButtonState;
	ButtonState m_middleButtonState;

};