/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This class offers debugging resources to help make life a little easier when working with 
  OpenGL. It contains routines to help display OpenGL and GLSL specifications, point out errors 
  that might occur along the way, draw grids and coordinate systems to help visualize objects in
  the dark, and also draw a set of basic shapes on screen to make things easier. This class is a
  Singleton.

- There are five buffer objects that will be used to draw the grid system, coordinate system,
  the 2D cube, 2D sphere and vectors. The buffers contain all the relevant data needed to render
  the objects, and they are individually set up along the way before being drawn. For the 3D
  cube and 3D sphere, the model class is used to represent them because their vertices are not
  drawn manually, but instead loaded in from a file. The 2D cube and 2D sphere might then have
  been sprites, but then we would need sprite images or textures of geometric shapes, which
  proved unnecessary since there is no debug shader support for textures. Furthermore if the
  cube or sphere are scaled up, the texture will be scaled and at very high values will start to
  tear.

- The CreateBuffers() function will set up the VBOs needed for all rendering of debug objects. It
  will also link the buffer objects to their relevant VBOs and shader data. The DestroyBuffers()
  routine will clear and destroy all VBO buffers. 

- The function CheckError() will check for errors in OpenGL and use predefined constants to 
  display a friendly message on screen. Calling this function will return the first error that 
  occured with OpenGL since this function was last called.  

- There are a set of drawing routines to help display objects quickly on screen and assist with
  world orientation. All of these functions have a 2D and 3D version. One version could be used 
  instead but then there might arise an issue with too many if-else statements. All 2D versions
  have a pixel parameter that represents how many pixels each unit will represent. Remember
  in 2D mode the rendering is measured in pixels, but the object's size measurements are mostly 
  in units. 
  
- The DrawGrid() functions display a custom sized grid in world space. This allows the programmer
  to orient their objects around in world space and make things easier to work with instead of 
  working in a dark 2D or 3D world.
  The DrawCoordSystem() routines display a XY or XYZ colored axis to further assist with object
  orientation. The coordinate system is intended to help draw the global world and local object 
  coordinate system, which can help visualise things when many transformations are being made. 
  The DrawCube() and DrawSphere() functions will manually render a shape in 2D or 3D mode. In 2D
  mode these routines will manually create and render a cube or sphere, and their 3D counterparts
  will use a loaded model object to represent a cube or sphere in 3D space. Drawing a 3D cube or 
  sphere manually was just too much hassle. 
  
- The DrawVector() routine will render a custom sized 2D or 3D vector on screen, based on the 
  position defined in the client code. The DrawVertex() function will render a basic vertex point
  on screen, exactly where specified by the points passed to the function. This is the simplest 
  shape to render and is good for drawing coordinate points. One could actually use the DrawCube()
  functions to render a point on screen, but then they would have to first be moved into position
  in the calling code. The DrawLine() function draws a 2D or 3D line segment using a passed starting
  and ending point. The difference between this routine and the DrawVector() is that the latter will
  render a line from the origin to the end point and the DrawLine() renders from a specific starting
  point to the specified ending point.  
  The DrawVector(), DrawVertex() and DrawLine() functions all have 2D and 3D built in, because 
  creating separate routines for these simple geometric shapes was unnecessary. They all take in 
  separate X, Y and Z parameters, because taking in specific vector objects would mean either 
  templatizing the functions or overloading them in various ways.

- Only the DrawGrid() routines have a static flag to fill the buffers only once. All other buffer 
  objects are filled each call as they may change over time. The grid will always stay the same. 
  (Temporary!!)

*/

#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <glew.h>
#include "Buffer.h"
#include "Color.h"
#include "Model.h"
#include "Singleton.h"

class DebugManager
{

public:

	friend class Singleton<DebugManager>;

public :

	void CheckError();
	bool CreateBuffers();
	void DestroyBuffers();

public :

	void DrawGrid3D(int size, float lineWidth);
	void DrawGrid2D(int size, float lineWidth, int pixelsPerUnit);
	
	void DrawCoordSystem3D(float size, float lineWidth);
	void DrawCoordSystem2D(float size, float lineWidth, int pixelsPerUnit);
	
	void DrawCube3D(float width, float height, float depth, Color color);
	void DrawCube2D(float width, float height, Color color, int pixelsPerUnit);

	void DrawSphere3D(float radius, Color color);
	void DrawSphere2D(float radius, Color color, int slices, int pixelsPerUnit);

	void DrawVector(float x, float y, float z, float lineWidth, Color color, int pixelsPerUnit = 1);
	void DrawVertex(float x, float y, float z, float pointSize, Color color, int pixelsPerUnit = 1);
	void DrawLine(float x1, float y1, float z1,
	              float x2, float y2, float z2, float lineWidth, Color color, int pixelsPerUnit = 1);

private:

	DebugManager()  {}
	DebugManager(const DebugManager&);
	DebugManager& operator=(const DebugManager&);

private :

	Model m_cube3D;
	Model m_sphere3D;
	
	Buffer m_lineBuffer;
	Buffer m_gridBuffer;
	Buffer m_coordBuffer;
	Buffer m_vertexBuffer;
	Buffer m_vectorBuffer;
	Buffer m_cubeBuffer2D;
	Buffer m_sphereBuffer2D;

	GLuint m_textureFlagUniformID;
	
};

typedef Singleton<DebugManager> TheDebug;

#endif