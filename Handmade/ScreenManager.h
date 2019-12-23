/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates screen management, and is designed to set up all screen and window 
  related matters. It is there to set up all SDL, OpenGL and GLEW components, screen projections,
  viewports, and keep track of the projection matrix, which has a matrix class declared for that.
  The frame buffer is also cleared and swapped via this class. The m_width and m_height member 
  variables are separate ints because it looks clearer to identify them separately. The 
  m_pixelsPerUnit is there to determine how many pixels will represent one unit of measurement
  in 2D applications, and this value is stored here and requested by the client code when needed
  later on. There is a m_windowHandle variable that is a pointer to a Windows OS specific window
  and can be used in conjunction with the Win32 API to create Windows specific applications. This
  class is a Singleton.

- There are a few setter functions, of which the Set2DScreen() and Set3DScreen() are important to 
  note. The 2D version will set up an orthographic projection and the 3D version will also define
  the projection matrix so that a perspective view is achieved. Both functions will immediately 
  pass the projection data to the vertex shader. 

- The Initialize() routine probably does the most work in the class. It is there to set up the SDL
  subsystem, and create an OpenGL context that the programmer requests. The context might not always
  be what the programmer wants, but it will set up the next best version instead. This all depends 
  on what the graphics card limitations are and what versions are supported. A context of 3.2 or 
  higher can be set to compatibility or core profile mode, meaning that deprecated functionality 
  can or cannot be accessed respectively. By default if no specific context is set, a compatibility 
  profile supporting the latest version of OpenGL will be setup. Compatibility mode only works for 
  versions 3.2 and upwards. On some graphics cards setting a context of 3.0 or less will automatically
  default to the latest version with compatibility mode on. Mine for instance defaults to 4.5 in 
  compatibility mode.
  The function will also create the game screen window and then go ahead and initialize the GLEW 
  subsystem, which will manage all extensions for OpenGL core access beyond 1.1. This is for Windows
  OS only, because Windows only allows developer access to the OpenGL core up until version 1.1.
  Finally the function will gather the HWND window handle from the SDL created window and store it
  so that it may be used if requested in the client code. This is useful when integrating Windows
  specific functionality like Windows dialog or message boxes, because the HWND handle will always 
  reference the main SDL parent window.

- The function DisplayExtensions() will display all extensions available to the programmer based on
  their graphics card hardware. The DisplayGraphicsProfile() function helps with displaying OpenGL
  graphics and shader capabilities. It will show the programmer what graphics card type, 
  manufacturer, OpenGL version and shader version is installed and supported.

- The Update() and Draw() routines will clear and swap the frame buffer respectively, and the 
  ShutDown() function closes down the SDL and OpenGL subsystems.  

*/

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <string>
#include "glad.h"
#include <glm.hpp>
#include <SDL.h>
#include <SDL_syswm.h>
#include "Singleton.h"

class ScreenManager
{

public :

	enum VSyncState      { VSYNC_OFF, VSYNC_ON };
	enum ScreenOrigin2D  { TOP_LEFT, BOTTOM_LEFT };

public:

	friend class Singleton<ScreenManager>;

public :

	GLint GetPixelsPerUnit();
	HWND GetWindowHandle();
	SDL_Window* GetWindow();
	glm::vec2 GetScreenSize();

public :

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

	ScreenManager();
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(const ScreenManager&);

private :

	GLint m_width;
	GLint m_height;
	GLint m_pixelsPerUnit;

	HWND m_windowHandle;
	SDL_Window* m_window;
	SDL_GLContext m_context;
	
	glm::mat4 m_projectionMatrix;
	
};

typedef Singleton<ScreenManager> TheScreen;

#endif