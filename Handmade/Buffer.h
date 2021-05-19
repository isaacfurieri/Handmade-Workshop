#pragma once

/*===================================================================#
| 'Buffer' source files last updated on 19 May 2021                  |
#===================================================================*/

#include <map>
#include <string>
#include <vector>
#include "glad.h"

//TODO - Add ability to set existing buffers so that buffer objects can be shared between objects
//TODO - Refine this class so that it follows the newer structure

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

	enum DataType
	{
		FLOAT = GL_FLOAT,
		INT = GL_INT,
		U_INT = GL_UNSIGNED_INT
	};

	enum FillType
	{
		STATIC_FILL = GL_STATIC_DRAW,
		DYNAMIC_FILL = GL_DYNAMIC_DRAW
	};

	enum DrawMode
	{
		LINES = GL_LINES,
		LINE_LOOP = GL_LINE_LOOP,
		POINTS = GL_POINTS,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_FAN = GL_TRIANGLE_FAN
	};

	enum VBOType
	{
		VERTEX_BUFFER,
		COLOR_BUFFER,
		NORMAL_BUFFER,
		TEXTURE_BUFFER
	};

	enum ComponentSize
	{
		XY = 2,
		XYZ = 3,
		RGB = 3,
		RGBA = 4,
		UV = 2
	};

	static void Output();

	Buffer();

	void SetBuffers(const std::string& bufferID);

	bool CreateBuffers(const std::string& bufferID, GLsizei totalVertices = 0, bool hasEBO = false);

	void BindEBO();
	void BindVBO(VBOType vboType, const std::string& vertAttrib,
		ComponentSize componentSize, DataType dataType);

	void FillEBO(const GLuint* data, GLsizeiptr size, FillType fillType = STATIC_FILL);
	void FillVBO(VBOType vboType, const GLint* data, GLsizeiptr size, FillType fillType = STATIC_FILL);
	void FillVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, FillType fillType = STATIC_FILL);
	void FillVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, FillType fillType = STATIC_FILL);

	void AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, GLuint offset);

	void Draw(DrawMode drawMode);

	void DestroyBuffers();
	void DestroyBuffers(const std::string& bufferID);

private:

	static std::map<std::string, BufferID>* s_bufferIDMap;

	BufferID m_ID;

};