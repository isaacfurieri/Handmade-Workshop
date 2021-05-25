#include <iostream>
#include <vector>
#include "Debug.h"
#include "Shader.h"
#include "Screen.h"

//======================================================================================================
Screen* Screen::Instance()
{
	static Screen* screenObject = new Screen();
	return screenObject;
}
//======================================================================================================
Screen::Screen()
{
	m_window = nullptr;
	m_context = nullptr;
	m_windowHandle = 0;
	m_pixelsPerUnit = 0;
}
//======================================================================================================
GLuint Screen::GetPixelsPerUnit()
{
	return m_pixelsPerUnit;
}
//======================================================================================================
void Screen::GetResolution(int& width, int& height)
{
	SDL_GetWindowSize(m_window, &width, &height);
}
//======================================================================================================
bool Screen::SetVerticalSync(VSyncState vsyncState)
{
	if (SDL_GL_SetSwapInterval((int)vsyncState) == -1)
	{
		Debug::Log("Vertical sync not supported.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	return true;
}
//======================================================================================================
void Screen::SetViewport(GLuint x, GLuint y, GLuint width, GLuint height)
{
	glViewport(x, y, width, height);
}
//======================================================================================================
void Screen::SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
}
//======================================================================================================
bool Screen::Initialize(const std::string& windowTitle, GLuint width, GLuint height, GLuint pixelsPerUnit,
	GLuint major, GLuint minor, bool isCoreContext, bool isFullscreen)
{
	Debug::Log("Initializing SDL, OpenGL and GLAD...");

	//initialize SDL subsystem by enabling the entire SDL package
	//if SDL initialization fails, display error message and return false
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Debug::Log("SDL did not initialize properly.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	//set frame buffer attributes so that we have 32-bit color
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//set up anti-aliasing 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	//assign OpenGL profile to compatibile or core profile based on flag passed 
	GLint profile = (isCoreContext) ? SDL_GL_CONTEXT_PROFILE_CORE
		: SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;

	//set OpenGL context and profile using values assigned earlier
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

	//assign normal window or fullscreen flag based on value passed
	Uint32 screenFlag = (isFullscreen) ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
		: SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	//create a game window using caption, width, height and screen mode flag
	m_window = SDL_CreateWindow(windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height, screenFlag);

	//if game window could not be created, display error message and return false
	if (!m_window)
	{
		Debug::Log("Game window could not be created.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	//create OpenGL context using SDL window created earlier
	m_context = SDL_GL_CreateContext(m_window);

	//if OpenGL context could not be created, display error message and return false
	if (!m_context)
	{
		std::string openGLVersion = std::to_string(major) + "." + std::to_string(minor);
		Debug::Log("OpenGL context " + openGLVersion + " could not be created.", Debug::ErrorCode::FAILURE);
		Debug::Log("The context is either invalid or not supported.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	//variable to store window data in
	SDL_SysWMinfo systemInfo;

	//first store SDL version info
	SDL_VERSION(&systemInfo.version);

	//aquire main window data from SDL created game window
	SDL_GetWindowWMInfo(m_window, &systemInfo);

	//make sure that GLAD loads all extension functions into memory
	//and return a 'false' flag so that the client can deal with it
	if (!gladLoadGL())
	{
		Debug::Log("GLAD could not initialize and load extensions.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	//enable vertical syncing so that screen monitor and frame buffer refresh rate are synchronized 
	//if there was an error setting this value, display error message and return false 
	if (SDL_GL_SetSwapInterval(1) == -1)
	{
		Debug::Log("VSync not supported.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	//store pixel scale value for use with 2D applications
	m_pixelsPerUnit = pixelsPerUnit;

	//store window handle for use with Windows specific functions
	m_windowHandle = systemInfo.info.win.window;

	//display text to state that screen has been setup successfully
	Debug::Log("SDL, OpenGL and GLAD successfully initialized.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	//enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}
//======================================================================================================
void Screen::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//======================================================================================================
void Screen::Present()
{
	SDL_GL_SwapWindow(m_window);
}
//======================================================================================================
void Screen::ShutDown()
{
	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();
}