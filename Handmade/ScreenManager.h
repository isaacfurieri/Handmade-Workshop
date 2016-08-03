/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2016

  -----------------------------------------------------------------------------------------------

- This class encapsulates screen management, and is designed to set up all screen and window 
  related matters. It is there to set up all SDL, OpenGL and GLEW components, screen projections,
  viewports, and keep track of the modelview and projection matrices. A matrix class object has 
  been assigned for the projection matrix, and a vector of matrices is being used for the 
  modelview matrix, so that multiple modelview transformations can be added, giving the push and
  pop functionality for parent/child object transformations.
  The frame buffer is also cleared and swapped via this class. The m_width and m_height member 
  variables are separate ints because it looks clearer to identify them separately. The 
  m_pixelsPerUnit is there to determine how many pixels will represent one unit of measurement
  in 2D applications, and this value is stored here and requested by the client code when needed
  later on. This class is a Singleton.

- Two getter/setter combo functions have been created to return references of the projection and 
  modelview matrix objects. This makes accessing and assigning the matrices easier in the calling 
  client code. The ModelViewMatrix() getter will always return the last modelview matrix
  transformation, because the last one is the current active one that will be used in the client
  code.

- There are a few setter functions, of which the Set2DScreen() and Set3DScreen() are important to 
  note. The 2D version will set up an orthographic projection and use a formula to define individual
  components of the projection matrix. The 3D version will also define the projection matrix so that
  a perspective view is achieved.

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

- The PushMatrix() and PopMatrix() functions add push and pop functionality, respectively, to the
  modelview matrix. Therefore when parent and child objects are being transformed, multiple matrix
  transformations can exist at any one time, allowing for transformations to be "bookmarked". This
  works exactly like push/pop worked in legacy OpenGL.

- The Update() and Draw() routines will clear and swap the frame buffer respectively, and the ShutDown()
  function closes down the SDL and OpenGL subsystems.  

*/

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_syswm.h>
#include "Color.h"
#include "Matrix4D.h"
#include "Singleton.h"
#include "Vector2D.h"

class ScreenManager
{

public :

	enum ScreenOrigin2D  { TOP_LEFT, BOTTOM_LEFT };

public:

	friend class Singleton<ScreenManager>;

public:

	Matrix4D& ModelViewMatrix();
	Matrix4D& ProjectionMatrix();

public :

	int GetPixelsPerUnit();
	HWND GetWindowHandle();
	Vector2D<int> GetScreenSize();

public :

	void SetClearColor(Color& color);
	void SetViewport(int x, int y, int width, int height);
	void Set2DScreen(ScreenOrigin2D screenOrigin);
	void Set3DScreen(float fieldOfView, float nearClip, float farClip);
	
public:

	bool Initialize(const char* windowTitle, int width = 1024, int height = 768, int pixelsPerUnit = 0,
		            double context = 3.2, bool compatibleContext = true, bool fullscreen = false);

	void PushMatrix();
	void PopMatrix();

	void Update();
	void Draw();

	void ShutDown();

private:

	ScreenManager();
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(const ScreenManager&);

private :

	int m_width;
	int m_height;
	int m_pixelsPerUnit;

	HWND m_windowHandle;

	SDL_Window* m_window;
	SDL_Surface* m_screen;
	SDL_GLContext m_context;
	
	Matrix4D m_projectionMatrix;
	std::vector<Matrix4D> m_modelViewMatrix;
	
};

typedef Singleton<ScreenManager> TheScreen;

#endif