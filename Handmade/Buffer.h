/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This buffer class is designed to contain the VAO, vertex, color, normal and texture VBO, and 
  EBO IDs all in one place. Ideally every game object or any generic object in the client code
  can use this class as a component to store the buffer IDs. It is through these IDs that the 
  OpenGL buffers in VRAM are used to store all vertex, color, etc data for each object, 3D
  model, etc in the scene. 

- Buffers are meant to be created once only and stored in the given map. If that same buffer is
  required by another object, instead of creating it again, we simply use SetBuffers() to set an
  existing buffer to the object. This models around the Flyweight pattern a little bit. When
  buffers are created or set, the m_ID variable is assigned the IDs of that buffer.

- There are functions to create the buffers, bind them together and fill them with data. Buffers
  may also be appended so that existing VBOs have data added on to the ends. 
  
*/

#ifndef BUFFER_H
#define BUFFER_H

#include <map>
#include <string>
#include <vector>
#include <glew.h>

struct BufferID
{
	bool hasEBO;
	GLuint vaoID;
	GLuint vboID[4];
	GLuint eboID;
	GLsizei totalVertices;
};

class Buffer
{

public:

	enum DataType       { FLOAT, U_INT };
	enum FillType       { STATIC_FILL, DYNAMIC_FILL };
	enum ComponentSize  { XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2 };
	enum DrawMode       { LINES, LINE_LOOP, POINTS, TRIANGLES, TRIANGLE_FAN };
	enum VBOType        { VERTEX_BUFFER, COLOR_BUFFER, NORMAL_BUFFER, TEXTURE_BUFFER };

public:

	Buffer();

public:

	void SetLineWidth(GLfloat lineWidth);
	void SetPointSize(GLfloat pointSize);
	void SetBuffers(const std::string& bufferID);

public:

	bool CreateBuffers(const std::string& bufferID, GLsizei totalVertices = 0, bool hasEBO = false);

	void BindEBO();
	void BindVBO(VBOType vboType, const std::string& vertAttrib,
		         ComponentSize componentSize, DataType dataType);

	void FillEBO(const GLuint* data, GLsizeiptr size, FillType fillType = STATIC_FILL);
	void FillVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, FillType fillType = STATIC_FILL);
	void FillVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, FillType fillType = STATIC_FILL);

	void AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, GLuint offset);

	void Draw(DrawMode drawMode);

	void DestroyBuffers();
	void DestroyBuffers(const std::string& bufferID);

public:

	void Output();

private:

	static std::map<std::string, BufferID>* s_bufferIDMap;

private:

	BufferID m_ID;

};

#endif