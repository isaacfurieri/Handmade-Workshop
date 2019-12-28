#ifndef SCREEN_H
#define SCREEN_H

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
| 'Screen' source files last updated in December 2019       								    |
#==============================================================================================*/

#include <string>
#include "glad.h"
#include <glm.hpp>
#include <SDL.h>
#include <SDL_syswm.h>

class Screen
{

public:

	enum VSyncState      { VSYNC_OFF, VSYNC_ON };
	enum ScreenOrigin2D  { TOP_LEFT, BOTTOM_LEFT };

public:

    static Screen* Instance();

public:

	GLint GetPixelsPerUnit();
	HWND GetWindowHandle();
	SDL_Window* GetWindow();
	glm::vec2 GetScreenSize();

public:

	bool SetVerticalSync(VSyncState vsyncState);
	void SetViewport(GLint x, GLint y, GLint width, GLint height);
	void SetClearColor(GLfloat r = 1.0f, GLfloat g = 1.0f, 
		               GLfloat b = 1.0f, GLfloat a = 1.0f);

	void Set2DScreen(ScreenOrigin2D screenOrigin);
	void Set3DScreen(GLfloat fieldOfView, GLfloat nearClip, GLfloat farClip);
	
public:

	bool Initialize(const char* windowTitle, GLint width = 1024, GLint height = 768, GLint pixelsPerUnit = 1,
		            GLint major = 4, GLint minor = 0, bool compatibleContext = false, bool fullscreen = false);
	
	void DisplayExtensions();
	void DisplayGraphicsProfile();
	
	void ClearScreen();
	void SwapBuffer();

	void ShutDown();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

private:

	GLint m_width;
	GLint m_height;
	GLint m_pixelsPerUnit;

	HWND m_windowHandle;
	SDL_Window* m_window;
	SDL_GLContext m_context;
	
	glm::mat4 m_projectionMatrix;
	
};

#endif