#pragma once

/*===================================================================#
| 'Screen' source files last updated on 19 May 2021                  |
#===================================================================*/

#include <string>
#include "glad.h"
#include <glm.hpp>
#include <SDL.h>
#include <SDL_syswm.h>

//TODO - Refine class such that it follows newer design

class Screen
{

public:

	enum VSyncState
	{
		VSYNC_OFF,
		VSYNC_ON
	};

	enum ScreenOrigin2D
	{
		TOP_LEFT,
		BOTTOM_LEFT
	};

	static Screen* Instance();

	GLuint GetPixelsPerUnit();
	void GetResolution(int& width, int& height);

	bool SetVerticalSync(VSyncState vsyncState);
	void SetViewport(GLuint x, GLuint y, GLuint width, GLuint height);
	void SetClearColor(GLfloat r = 1.0f, GLfloat g = 1.0f,
		GLfloat b = 1.0f, GLfloat a = 1.0f);

	bool Initialize(const std::string& windowTitle,
		GLuint width = 1280, GLuint height = 720,
		GLuint pixelsPerUnit = 1, GLuint major = 4, GLuint minor = 5,
		bool isCoreContext = false, bool isFullscreen = false);

	void Clear();
	void Present();
	void ShutDown();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

	HWND m_windowHandle;
	SDL_Window* m_window;
	SDL_GLContext m_context;
	GLuint m_pixelsPerUnit;

};