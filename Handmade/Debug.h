/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class offers debugging resources to help make life a little easier when working with 
  OpenGL. It contains routines to help display OpenGL errors in a more detailed manner, as well
  as draw grids and coordinate systems, to help visualize objects in the dark. There are also 
  a set of functions that will render some basic shapes, lines and vectors on screen to make
  things easier to visualize. This class is a Singleton and even though it's a controversial
  design pattern, it makes the most sense to use here, as this class and its helper routines 
  need to be accessed and used anywhere. Furthermore, we only ever need one of these helper 
  classes.

- Since this class can be called accessed from anywhere, it is relatively easy to simply create
  a line or shape on screen when desired. Furthermore, when visualizing collision bounds, the 
  cube, sphere and lines come in useful and are called into from the collision classes.

- For each helper function that renders a basic shape, there is a 2D and a 3D version available
  because there are some specific things being done in either mode. If only one version is used 
  then there might arise an issue with too many if-else statements. All 2D versions have a pixel
  per unit parameter that represents how many pixels each OpenGL unit of measurement will 
  represent. Remember in 2D mode the rendering is measured in pixels, but the object's size
  measurements are mostly in units. Granted, overall there is still a lot of repetition going 
  on, however I am still working on ways to improve this class and its member functions. 
  Another thing to note is that even though 2D coordinates are measured in pixels, we still work
  with units when passing data to the DrawLine2D() or DrawVector2D() functions, because it is 
  easier to work with units when rendering primitive shapes and lines on a grid. 

- For the 3D cube and 3D sphere, the model class is used to represent them because their 
  vertices are not drawn manually, but instead loaded in from a file. The 2D cube and 2D sphere
  could have been sprites, but then we would need sprite images or textures of geometric shapes,
  which is not really ideal for a basic shape. Furthermore if the 2D cube or sphere are scaled 
  up, the texture will be scaled and at very high values will start to tear.

- The big difference between the DrawVector() and DrawLine() functions is that the former will
  render a displacement from a (0,0) origin, based on client transformations. The latter will
  draw a line segment from the given starting point to the given ending point. These points in
  space are also dependant on client transformations.

- Future improvements include adding a "Logging/Messaging" system in here that displays error
  and warning messages on the console. 

*/

#ifndef DEBUG_H
#define DEBUG_H

#include "glad.h"
#include "Buffer.h"
#include "Model.h"

class Debug
{

public:

	static Debug* Instance();

public:

	void CheckError();
	bool CreateDebugObjects(GLint size);
	void DestroyDebugObjects();

public:

	void DrawGrid2D(GLfloat lineWidth = 2.0f);
	void DrawGrid3D(GLfloat lineWidth = 2.0f);
	
	void DrawCoordSystem2D(GLfloat size, GLfloat lineWidth = 5.0f);
	void DrawCoordSystem3D(GLfloat size, GLfloat lineWidth = 5.0f);
		
	void DrawCube2D(GLfloat width, GLfloat height,
	  	            GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);

	void DrawCube3D(GLfloat width, GLfloat height, GLfloat depth, 
		            GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);
	
	void DrawSphere2D(GLfloat radius, GLfloat r = 1.0f, GLfloat g = 1.0f, 
		              GLfloat b = 1.0f, GLfloat a = 1.0f, GLint slices = 10);

	void DrawSphere3D(GLfloat radius, GLfloat r = 1.0f, GLfloat g = 1.0f, 
		              GLfloat b = 1.0f, GLfloat a = 1.0f);
	
	void DrawVector2D(GLfloat x, GLfloat y, GLfloat lineWidth = 2.0f,
					  GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

	void DrawVector3D(GLfloat x, GLfloat y, GLfloat z, GLfloat lineWidth = 2.0f, 
		              GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);
	
	void DrawVertex2D(GLfloat x, GLfloat y, GLfloat pointSize = 10.0f,
					  GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

	void DrawVertex3D(GLfloat x, GLfloat y, GLfloat z, GLfloat pointSize = 10.0f,
					  GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

	void DrawLine2D(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
					GLfloat lineWidth = 2.0f, GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

	void DrawLine3D(GLfloat x1, GLfloat y1, GLfloat z1,
		            GLfloat x2, GLfloat y2, GLfloat z2, GLfloat lineWidth = 2.0f, 
		            GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

private:

	void CreateGrid2D(GLint size);
	void CreateGrid3D(GLint size);

private:

	Debug()  {}
	Debug(const Debug&);
	Debug& operator=(const Debug&);

private:

	Model m_cube3D;
	Model m_sphere3D;
	
	Buffer m_lineBuffer;
	Buffer m_gridBuffer2D;
	Buffer m_gridBuffer3D;
	Buffer m_coordBuffer;
	Buffer m_vertexBuffer;
	Buffer m_vectorBuffer;
	Buffer m_cubeBuffer2D;
	Buffer m_sphereBuffer2D;
	
};

#endif