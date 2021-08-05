#pragma once

/*===================================================================#
| 'Buffer' source files last updated on 5 August 2021                |
#===================================================================*/

#include <map>
#include <string>
#include "glad.h"

const int TOTAL_BUFFERS = 4;

class Buffer
{

public:

	enum class Fill
	{
		Once = GL_STATIC_DRAW,
		Ongoing = GL_DYNAMIC_DRAW
	};

	enum class ComponentSize
	{
		XY = 2,
		XYZ = 3,
		XYZW = 4,
		RGB = 3,
		RGBA = 4,
		UV = 2
	};

	enum class DataType
	{
		IntData = GL_INT,
		FloatData = GL_FLOAT,
		DoubleData = GL_DOUBLE,
		UintData = GL_UNSIGNED_INT
	};

	enum class VBO
	{
		VertexBuffer,
		ColorBuffer,
		TextureBuffer,
		NormalBuffer
	};

	enum class RenderMode
	{
		Lines = GL_LINES,
		Points = GL_POINTS,
		Triangles = GL_TRIANGLES,
		LineLoop = GL_LINE_LOOP,
		LineStrip = GL_LINE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN
	};

	enum class RenderStyle
	{
		Shaded = GL_FILL,
		Polygonal = GL_LINE
	};

	enum class Culling
	{
		None = 0,
		BackFace = GL_BACK,
		FrontFace = GL_FRONT,
	};

	static void SetPointSize(GLfloat size);
	static void SetLineWidth(GLfloat lineWidth);
	static void SetCullingMode(Culling culling);
	static void SetRenderStyle(RenderStyle renderStyle);

	Buffer();

	const std::string& GetTag() const;

	void SetBuffer(const std::string& tag);

	void Create(const std::string& tag, GLsizei totalVertices, bool hasEBO = false);

	void FillEBO(const GLuint* data, GLsizeiptr bufferSize, Fill fill = Fill::Once);
	void FillVBO(VBO vbo, const void* data, GLsizeiptr bufferSize, Fill fill = Fill::Once);

	void AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBO vbo, const void* data, GLsizeiptr size, GLuint offset);

	void LinkEBO();
	void LinkVBO(GLint attributeID, VBO vbo, ComponentSize componentSize, DataType dataType);

	void Render(RenderMode renderMode, GLuint index = 0, GLuint totalVertices = 0);

	void Destroy();
	void Destroy(const std::string& tag);

private:

	bool m_hasEBO;
	std::string m_tag;

	GLuint m_VAO;
	GLuint m_EBO;
	GLsizei m_totalVertices;
	GLuint m_VBOs[TOTAL_BUFFERS];

	static std::map<std::string, Buffer> s_buffers;
};