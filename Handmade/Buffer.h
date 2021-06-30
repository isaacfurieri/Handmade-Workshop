#pragma once

/*===================================================================#
| 'Buffer' source files last updated on 23 June 2021                 |
#===================================================================*/

#include <map>
#include <string>
#include "glad.h"

class Buffer
{

public:

	enum FillFrequency
	{
		FILL_ONCE = GL_STATIC_DRAW,
		FILL_MANY = GL_DYNAMIC_DRAW
	};

	enum ComponentSize
	{
		XY = 2,
		XYZ = 3,
		RGB = 3,
		RGBA = 4,
		UV = 2
	};

	enum DataType
	{
		INT = GL_INT,
		FLOAT = GL_FLOAT,
		UNSIGNED_INT = GL_UNSIGNED_INT
	};

	enum VBOType
	{
		VERTEX_BUFFER,
		COLOR_BUFFER,
		TEXTURE_BUFFER,
		NORMAL_BUFFER,
		TOTAL_BUFFERS
	};

	enum RenderMode
	{
		LINES = GL_LINES,
		POINTS = GL_POINTS,
		TRIANGLES = GL_TRIANGLES,
		LINE_LOOP = GL_LINE_LOOP,
		LINE_STRIP = GL_LINE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN
	};

	enum RenderStyle
	{
		FULL_SHADE = GL_FILL,
		POLYGON_MODE = GL_LINE
	};

	static void SetPointSize(GLfloat size);
	static void SetLineWidth(GLfloat lineWidth);
	static void SetRenderStyle(RenderStyle renderStyle);

	Buffer();

	void SetBuffer(const std::string& bufferID);

	void Create(const std::string& bufferID, GLsizei totalVertices, bool hasEBO = false);

	void FillVBO(VBOType vboType, const GLint* data, GLsizeiptr bufferSize, FillFrequency fillFrequency = FILL_ONCE);
	void FillVBO(VBOType vboType, const GLuint* data, GLsizeiptr bufferSize, FillFrequency fillFrequency = FILL_ONCE);
	void FillVBO(VBOType vboType, const GLfloat* data, GLsizeiptr bufferSize, FillFrequency fillFrequency = FILL_ONCE);

	void FillEBO(const GLuint* data, GLsizeiptr bufferSize, FillFrequency fillFrequency = FILL_ONCE);

	void AppendVBO(VBOType vboType, const GLint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, GLuint offset);

	void AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset);

	void LinkEBO();

	void LinkVBO(GLint attributeID, VBOType vboType, ComponentSize componentSize, DataType dataType);

	void Render(RenderMode renderMode);

	void Destroy();
	void Destroy(const std::string& bufferID);

private:

	static std::map<std::string, Buffer> s_buffers;
	
	bool m_hasEBO;

	GLuint m_VAO;
	GLuint m_EBO;
	GLsizei m_totalVertices;
	GLuint m_VBOs[TOTAL_BUFFERS];
	
};