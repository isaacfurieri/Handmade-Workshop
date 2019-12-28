#include <iostream>
#include <vector>
#include <gtc\matrix_transform.hpp>
#include "Shader.h"
#include "Screen.h"

//------------------------------------------------------------------------------------------------------
//static function that will create an instance of this Screen object and return its address
//------------------------------------------------------------------------------------------------------
Screen* Screen::Instance()
{

	static Screen* screenObject = new Screen();
	return screenObject;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Screen::Screen()
{

	m_width = 0;
	m_height = 0;
	m_pixelsPerUnit = 0;
	
	m_windowHandle = 0;
	m_window = nullptr;
	m_context = nullptr;
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns pixel scale value
//------------------------------------------------------------------------------------------------------
GLint Screen::GetPixelsPerUnit()
{

	return m_pixelsPerUnit;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns Windows handle of SDL game window
//------------------------------------------------------------------------------------------------------
HWND Screen::GetWindowHandle()
{

	return m_windowHandle;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns SDL game window
//------------------------------------------------------------------------------------------------------
SDL_Window* Screen::GetWindow()
{

	return m_window;

}
//------------------------------------------------------------------------------------------------------
//getter function that creates screen size vector and returns it
//------------------------------------------------------------------------------------------------------
glm::vec2 Screen::GetScreenSize()
{

	return glm::vec2(m_width, m_height);

}
//------------------------------------------------------------------------------------------------------
//setter function that switches VSYNC on/off
//------------------------------------------------------------------------------------------------------
bool Screen::SetVerticalSync(VSyncState vsyncState)
{

	if (SDL_GL_SetSwapInterval((int)vsyncState) == -1)
	{
		std::cout << "Vertical sync not supported." << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets up rectangular viewport section of screen 
//------------------------------------------------------------------------------------------------------
void Screen::SetViewport(GLint x, GLint y, GLint width, GLint height)
{

	glViewport(x, y, width, height);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns a pre-defined color value for clearing the screen
//------------------------------------------------------------------------------------------------------
void Screen::SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	glClearColor(r, g, b, a);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 2D orthographic projection 
//------------------------------------------------------------------------------------------------------
void Screen::Set2DScreen(ScreenOrigin2D screenOrigin)
{

	//disable Z-buffering because in
	//2D the depth buffer isn't needed 
	glDisable(GL_DEPTH_TEST);	

	//if screen origin passed is set as top left of screen 
	//create orthographic view so that Y is positive downward 
	if (screenOrigin == TOP_LEFT)
	{
		m_projectionMatrix = glm::ortho(0.0f, (float)m_width, (float)m_height, 0.0f);
	}

	//if screen origin passed is set as bottom left of screen 
	//create orthographic view so that Y is positive upward 
	else if (screenOrigin == BOTTOM_LEFT)
	{
		m_projectionMatrix = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height);
	}

	//send projection matrix to shader
	//ThePipeline::Instance()->SendUniformData("projMatrix", m_projectionMatrix);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 3D perspective projection 
//------------------------------------------------------------------------------------------------------
void Screen::Set3DScreen(GLfloat fieldOfView, GLfloat nearClip, GLfloat farClip)
{

	//enable Z-buffering so that vertices
	//are drawn in the correct order
	glEnable(GL_DEPTH_TEST);

	//determine the aspect ratio based on width and height of screen
	GLfloat aspectRatio = (GLfloat)m_width / (GLfloat)m_height;

	//create a 3D perspective projection using passed FOV angle, aspect ratio and clipping planes
	m_projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClip, farClip);

	//send projection matrix to shader
	//ThePipeline::Instance()->SendUniformData("projMatrix", m_projectionMatrix);

}
//------------------------------------------------------------------------------------------------------
//function that initializes the screen including the SDL, OpenGL and GLEW subsystems   
//------------------------------------------------------------------------------------------------------
bool Screen::Initialize(const char* windowTitle, GLint width, GLint height, GLint pixelsPerUnit,
	                           GLint major, GLint minor, bool compatibleContext, bool fullscreen)
{

	//initialize SDL subsystem by enabling the entire SDL package
	//if SDL initialization fails, display error message and return false
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL did not initialize properly." << std::endl;
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
	int profile = (compatibleContext) ? SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
									  : SDL_GL_CONTEXT_PROFILE_CORE;

	//set OpenGL context and profile using values assigned earlier
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

	//assign normal window or fullscreen flag based on value passed
	Uint32 screenFlag = (fullscreen) ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
		                             : SDL_WINDOW_OPENGL;

	//create a game window using caption, width, height and screen mode flag
	m_window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		                        width, height, screenFlag);

	//if game window could not be created, display error message and return false
	if (m_window == 0)
	{
		std::cout << "Game window could not be created." << std::endl;
		return false;
	}

	//create OpenGL context using SDL window created earlier
	m_context = SDL_GL_CreateContext(m_window);
	
	//if OpenGL context could not be created, display error message and return false
	if (m_context == 0)
	{
		std::cout << "OpenGL context " << major << "." << minor << " could not be created. The "
			         "context is either invalid or not supported by your graphics card." << std::endl;
		return false;
	}

	//variable to store window data in
	SDL_SysWMinfo systemInfo;

	//first store SDL version info
	SDL_VERSION(&systemInfo.version);

	//aquire main window data from SDL created game window
	SDL_GetWindowWMInfo(m_window, &systemInfo);

	//initialize GLEW with full support for beta extensions
	//and if it fails, display error message and return false
	/*glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW could not be initialized.";
		return false;
	}*/

	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		system("pause");
		return 0;
	}

	//enable vertical syncing so that screen monitor and frame buffer refresh rate are synchronized 
	//if there was an error setting this value, display error message and return false 
	if (SDL_GL_SetSwapInterval(1) == -1)
	{
		std::cout << "VSync not supported." << std::endl;
		return false;
	}
	
	//store width and height properties for later 
	//use when setting up 2D and 3D projections
	m_width = width;
	m_height = height;

	//store pixel scale value for use with 2D applications
	m_pixelsPerUnit = pixelsPerUnit;

	//store window handle for use with Windows specific functions
	m_windowHandle = systemInfo.info.win.window;

	//enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that aquires and displays graphics card extensions
//------------------------------------------------------------------------------------------------------
void Screen::DisplayExtensions()
{

	//variable to store total amount of supported extensions 
	GLint totalExtensions;

	//get total number of extensions supported by our graphics card
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "The following extensions are supported by your graphics card:  " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//loop through all extensions and display them
	for (GLint i = 0; i < totalExtensions; i++)
	{
		std::cout << "Extension #" << i + 1 << " : "
			      << (const char*)glGetStringi(GL_EXTENSIONS, i) << std::endl;
	}

}
//------------------------------------------------------------------------------------------------------
//function that aquires and displays OpenGL profile data
//------------------------------------------------------------------------------------------------------
void Screen::DisplayGraphicsProfile()
{

	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "Your graphics card profile is as follows:                      " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//display the manufacturer of the graphics hardware
	std::cout << "Graphics Card Vendor : " << (const char*)(glGetString(GL_VENDOR)) << std::endl;

	//display the make and model of the graphics card
	std::cout << "Graphics Card Model  : " << (const char*)(glGetString(GL_RENDERER)) << std::endl;

	//display the current OpenGL version and mode set
	std::cout << "OpenGL Version       : " << (const char*)(glGetString(GL_VERSION)) << std::endl;

	//display which GLSL version is supported by the graphics card
	std::cout << "GLSL Version         : " << (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION))
		      << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that clears the frame buffer
//------------------------------------------------------------------------------------------------------
void Screen::ClearScreen()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
//------------------------------------------------------------------------------------------------------
//function that swaps the frame buffer
//------------------------------------------------------------------------------------------------------
void Screen::SwapBuffer()
{

	SDL_GL_SwapWindow(m_window);

}
//------------------------------------------------------------------------------------------------------
//function that closes down SDL, OpenGL and destroys the game window
//------------------------------------------------------------------------------------------------------
void Screen::ShutDown()
{

	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();

}