#include "Input.h"

//======================================================================================================
Input* Input::Instance()
{
	static Input* input = new Input();
	return input;
}
//======================================================================================================
//char Input::GetKeyUp() const
//{
//	return m_keyUp;
//}
//======================================================================================================
int Input::GetKeyDown() const
{
	return m_keyDown;
}
//======================================================================================================
void Input::SetKeyDown(int keyDown)
{
	m_keyDown = keyDown;
}
//======================================================================================================
bool Input::IsLeftButtonDown() const
{
	return m_isLeftButtonDown;
}
//======================================================================================================
bool Input::IsRightButtonDown() const
{
	return m_isRightButtonDown;
}
//======================================================================================================
bool Input::IsMiddleButtonDown() const
{
	return m_isMiddleButtonDown;
}
//======================================================================================================
void Input::IsLeftButtonDown(bool flag)
{
	m_isLeftButtonDown = flag;
}
//======================================================================================================
void Input::IsRightButtonDown(bool flag)
{
	m_isRightButtonDown = flag;
}
//======================================================================================================
void Input::IsMiddleButtonDown(bool flag)
{
	m_isMiddleButtonDown = flag;
}
//======================================================================================================
void Input::SetMousePosition(const glm::ivec2& mousePosition)
{
	m_mousePosition = mousePosition;
}
//======================================================================================================
void Input::SetMouseMotion(const glm::ivec2& mouseMotion)
{
	m_mouseMotion = mouseMotion;
}
//======================================================================================================
void Input::SetMouseWheel(const glm::ivec2& mouseWheel)
{
	m_mouseWheel = mouseWheel;
}
//======================================================================================================
const glm::ivec2& Input::GetMousePosition() const
{
	return m_mousePosition;
}
//======================================================================================================
const glm::ivec2& Input::GetMouseMotion() const
{
	return m_mouseMotion;
}
//======================================================================================================
const glm::ivec2& Input::GetMouseWheel() const
{
	return m_mouseWheel;
}
//======================================================================================================
Input::Input()
{
	//m_keyUp = 0;
	m_keyDown = 0;

	m_mouseWheel = glm::ivec2(0);
	m_mouseMotion = glm::ivec2(0);
	m_mousePosition = glm::ivec2(0);

	m_isLeftButtonDown = false;
	m_isRightButtonDown = false;
	m_isMiddleButtonDown = false;
}