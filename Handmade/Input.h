#pragma once

/*===================================================================#
| 'Input' source files last updated on 23 June 2021                  |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <glm.hpp>

//All MFC triggered events will feed this class with keyboard and mouse data
//All objects will request data from this class to manage their entities
//Instead of using raw Win32 key names, there will exist HM key bindings

//These are the Win32 virtual key codes used for keyboard input
//Only the numpad numeric values do not link to ASCII codes 
//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#define HM_KEY_A 0x41
#define HM_KEY_B 0x42
#define HM_KEY_C 0x43
#define HM_KEY_D 0x44
#define HM_KEY_E 0x45
#define HM_KEY_F 0x46
#define HM_KEY_G 0x47
#define HM_KEY_H 0x48
#define HM_KEY_I 0x49
#define HM_KEY_J 0x4A
#define HM_KEY_K 0x4B
#define HM_KEY_L 0x4C
#define HM_KEY_M 0x4D
#define HM_KEY_N 0x4E
#define HM_KEY_O 0x4F
#define HM_KEY_P 0x50
#define HM_KEY_Q 0x51
#define HM_KEY_R 0x52
#define HM_KEY_S 0x53
#define HM_KEY_T 0x54
#define HM_KEY_U 0x55
#define HM_KEY_V 0x56
#define HM_KEY_W 0x57
#define HM_KEY_X 0x58
#define HM_KEY_Y 0x59
#define HM_KEY_Z 0x5A

//======================================================================================================

class Input
{

public:

	static Input* Instance();

	//char GetKeyUp() const;
	int GetKeyDown() const;
	void SetKeyDown(int keyDown);

	bool IsLeftButtonDown() const;
	bool IsRightButtonDown() const;
	bool IsMiddleButtonDown() const;

	const glm::ivec2& GetMousePosition() const;
	const glm::ivec2& GetMouseMotion() const;
	const glm::ivec2& GetMouseWheel() const;

	void IsLeftButtonDown(bool flag);
	void IsRightButtonDown(bool flag);
	void IsMiddleButtonDown(bool flag);

	void SetMousePosition(const glm::ivec2& mousePosition);
	void SetMouseMotion(const glm::ivec2& mouseMotion);
	void SetMouseWheel(const glm::ivec2& mouseWheel);

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

	//char m_keyUp;
	int m_keyDown;

	glm::ivec2 m_mouseWheel;
	glm::ivec2 m_mouseMotion;
	glm::ivec2 m_mousePosition;

	bool m_isLeftButtonDown;
	bool m_isRightButtonDown;
	bool m_isMiddleButtonDown;

};