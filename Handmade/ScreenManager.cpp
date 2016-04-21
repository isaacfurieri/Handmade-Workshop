#include <iostream>
#include <math.h>
#include <OpenGL.h>
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
ScreenManager::ScreenManager()
{

	m_width = 0;
	m_height = 0;
	m_pixelsPerUnit = 0;

	m_window = 0;
	m_screen = 0;
	m_context = 0;
	
}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to modelview matrix
//------------------------------------------------------------------------------------------------------
Matrix4D& ScreenManager::ModelViewMatrix()
{

	return m_modelViewMatrix;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to projection matrix
//------------------------------------------------------------------------------------------------------
Matrix4D& ScreenManager::ProjectionMatrix()
{

	return m_projectionMatrix;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pixel scale value
//------------------------------------------------------------------------------------------------------
int ScreenManager::GetPixelsPerUnit()
{

	return m_pixelsPerUnit;

}
//------------------------------------------------------------------------------------------------------
//getter function that creates screen size vector and returns it
//------------------------------------------------------------------------------------------------------
Vector2D<int> ScreenManager::GetScreenSize()
{

	return Vector2D<int>(m_width, m_height);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns a pre-defined color value for clearing the screen...
//------------------------------------------------------------------------------------------------------
void ScreenManager::SetClearColor(Color& color)
{

	glClearColor(color.R, color.G, color.B, color.A);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets up rectangular viewport section of screen 
//------------------------------------------------------------------------------------------------------
void ScreenManager::SetViewport(int x, int y, int width, int height)
{

	glViewport(x, y, width, height);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 2D orthographic projection using formula described below : 
//https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
//------------------------------------------------------------------------------------------------------
void ScreenManager::Set2DScreen(ScreenOrigin2D screenOrigin)
{

	//first reset projection matrix
	m_projectionMatrix = Matrix4D::IDENTITY;

	//disable Z-buffering because 
	//in 2D the depth buffer isn't needed 
	glDisable(GL_DEPTH_TEST);

	//enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//assign specific components of matrix for 2D projection
	m_projectionMatrix[0] = 2.0f / m_width; 
	m_projectionMatrix[10] = -1.0f; 
	m_projectionMatrix[12] = -1.0f; 
	m_projectionMatrix[14] = 0.0f; 
	m_projectionMatrix[15] = 1.0f; 

	//if screen origin passed is set as top left of screen 
	//adjust matrix components so that Y is positive downward 
	if (screenOrigin == TOP_LEFT)
	{
		m_projectionMatrix[5] = 2.0f / -m_height;
		m_projectionMatrix[13] = 1.0f;
	}

	//if screen origin passed is set as bottom left of screen 
	//adjust matrix components so that Y is positive upward 
	else if (screenOrigin == BOTTOM_LEFT)
	{
		m_projectionMatrix[5] = 2.0f / m_height;
		m_projectionMatrix[13] = -1.0f;
	}

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 3D perspective projection using formula described below : 
//https://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
//------------------------------------------------------------------------------------------------------
void ScreenManager::Set3DScreen(float fieldOfView, float nearClip, float farClip)
{

	//first reset projection matrix
	m_projectionMatrix = Matrix4D::IDENTITY;

	//enable Z-buffering so that 
	//vertices are drawn in the correct order
	glEnable(GL_DEPTH_TEST);

	//enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//first convert field of view angle passed to radians 
	//so that the tan function can use it later on
	float radian = fieldOfView / 180.0f * 3.14159265359f;

	//define a special formula that will be used in matrix
	float formula = 1.0f / tan(radian / 2);

	//calculate aspect ratio
	float aspectRatio = (float)(m_width / m_height);

	//assign specific components of matrix for 3D projection
	m_projectionMatrix[0] = formula / aspectRatio;
	m_projectionMatrix[5] = formula;
	m_projectionMatrix[10] = (farClip + nearClip) / (nearClip - farClip);
	m_projectionMatrix[11] = -1.0f;
	m_projectionMatrix[14] = (2.0f * farClip * nearClip) / (nearClip - farClip);
	m_projectionMatrix[15] = 0.0f;

}
//------------------------------------------------------------------------------------------------------
//function that initializes the screen including the SDL, OpenGL and GLEW subsystems   
//------------------------------------------------------------------------------------------------------
bool ScreenManager::Initialize(const char* windowTitle, int width, int height, int pixelsPerUnit,
	                           double context, bool compatibleContext, bool fullscreen)
{

	//store OpenGL context in two separate variables 
	//these will be used later to request a OpenGL context
	double major;
	double minor;

	//initialize SDL subsystem by enabling the entire SDL package
	//if SDL initialization fails, display error message and return false
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL did not initialize properly." << std::endl;
		return false;
	}

	//convert context value passed into whole and fractional part
	//this will be used to create OpenGL context using a major and minor number
	minor = modf(context, &major);
	minor *= 10;

	//set up anti-aliasing 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	//assign OpenGL profile to compatibile or core profile based on flag passed 
	int profile = (compatibleContext) ? SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
		                              : SDL_GL_CONTEXT_PROFILE_CORE;
	
	//set OpenGL context and profile using values assigned earlier
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, (int)major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, (int)minor);
	
	//assign normal window or fullscreen flag based on value passed
	Uint32 screenFlag = (fullscreen) ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
		                             : SDL_WINDOW_OPENGL;

	//create a game window using caption, width, height and screen mode flag
	m_window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
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
		std::cout << "OpenGL context " << context << " could not be created. The context is either "
			         "invalid or not supported by your graphics card." << std::endl;
		return false;
	}

	//initialize GLEW and if it fails, display error message and return false
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW could not be initialized.";
		return false;
	}

	//disable mouse cursor so that it won't interfere when rotating the camera
	//if there was an error disabling the mouse, display error message and return false 
	if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
	{
		std::cout << "Unable to disable mouse cursor." << std::endl;
		return false;
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

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that clears the frame buffer
//------------------------------------------------------------------------------------------------------
void ScreenManager::Update()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
//------------------------------------------------------------------------------------------------------
//function that swaps the frame buffer
//------------------------------------------------------------------------------------------------------
void ScreenManager::Draw()
{

	SDL_GL_SwapWindow(m_window);

}
//------------------------------------------------------------------------------------------------------
//function that closes down SDL, OpenGL and destroys the game window
//------------------------------------------------------------------------------------------------------
void ScreenManager::ShutDown()
{

	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();

}