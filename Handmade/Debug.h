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