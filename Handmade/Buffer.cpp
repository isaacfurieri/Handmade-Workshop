#include <assert.h>
#include "Buffer.h"

//TODO - create this map on the heap
std::map<std::string, Buffer> Buffer::s_buffers;

//======================================================================================================
void Buffer::SetPointSize(GLfloat size)
{
	glPointSize(size);
}
//======================================================================================================
void Buffer::SetLineWidth(GLfloat lineWidth)
{
	glLineWidth(lineWidth);
}
//======================================================================================================
void Buffer::SetRenderStyle(RenderStyle renderStyle)
{
	glPolygonMode(GL_FRONT_AND_BACK, renderStyle == POLYGON_MODE ? GL_LINE : GL_FILL);
}
//======================================================================================================
Buffer::Buffer()
{
	m_EBO = 0;
	m_VAO = 0;
	m_hasEBO = false;
	m_totalVertices = 0;
	m_VBOs[VERTEX_BUFFER] = 0;
	m_VBOs[COLOR_BUFFER] = 0;
	m_VBOs[TEXTURE_BUFFER] = 0;
	m_VBOs[NORMAL_BUFFER] = 0;
}
//======================================================================================================
void Buffer::SetBuffer(const std::string& bufferID)
{
	//Debug::Log("Setting buffers to: '" + bufferID + "'");

	//first check if buffer ID exists in map and if not display
	//error message, otherwise go ahead and assign the buffer ID

	auto it = s_buffers.find(bufferID);

	if (it == s_buffers.end())
	{
		//Debug::Log("Buffer IDs not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		//Debug::Log("===============================================================");
	}

	else
	{
		*this = it->second;
		//Debug::Log("Buffer IDs assigned successfully.", Debug::ErrorCode::SUCCESS);
		//Debug::Log("===============================================================");
	}
}
//======================================================================================================
void Buffer::Create(const std::string& bufferID, GLsizei totalVertices, bool hasEBO)
{
	//If buffer ID exists in map halt creation because 
	//we don't want to replace the existing buffers
	assert(s_buffers.find(bufferID) == s_buffers.end());

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(TOTAL_BUFFERS, m_VBOs);

	if (hasEBO)
	{
		glGenBuffers(1, &m_EBO);
	}

	m_hasEBO = hasEBO;
	m_totalVertices = totalVertices;
}
//======================================================================================================
void Buffer::FillVBO(VBOType vboType, const GLint* data, GLsizeiptr bufferSize, FillFrequency fillFrequency)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[vboType]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, static_cast<GLenum>(fillFrequency));
}
//======================================================================================================
void Buffer::FillVBO(VBOType vboType, const GLuint* data, GLsizeiptr bufferSize, FillFrequency fillFrequency)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[vboType]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, static_cast<GLenum>(fillFrequency));
}
//======================================================================================================
void Buffer::FillVBO(VBOType vboType, const GLfloat* data, GLsizeiptr bufferSize, FillFrequency fillFrequency)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[vboType]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, static_cast<GLenum>(fillFrequency));
}
//======================================================================================================
void Buffer::FillEBO(const GLuint* data, GLsizeiptr bufferSize, FillFrequency fillFrequency)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, data, static_cast<GLenum>(fillFrequency));
}
//======================================================================================================
void Buffer::AppendVBO(VBOType vboType, const GLint* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::AppendVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::AppendVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::LinkEBO()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(0);
}
//======================================================================================================
void Buffer::LinkVBO(GLint attributeID, VBOType vboType, ComponentSize componentSize, DataType dataType)
{
	if (attributeID > -1)
	{
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[vboType]);

		glVertexAttribPointer(attributeID, static_cast<GLint>(componentSize),
			static_cast<GLenum>(dataType), GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(attributeID);

		glBindVertexArray(0);
	}
}
//======================================================================================================
void Buffer::Render(RenderMode renderMode)
{
	glBindVertexArray(m_VAO);

	if (m_hasEBO)
	{
		glDrawElements(renderMode, m_totalVertices, GL_UNSIGNED_INT, nullptr);
	}

	else
	{
		glDrawArrays(renderMode, 0, m_totalVertices);
	}

	glBindVertexArray(0);
}
//======================================================================================================
void Buffer::Destroy()
{
	if (m_hasEBO)
	{
		glDeleteBuffers(1, &m_EBO);
	}

	glDeleteBuffers(TOTAL_BUFFERS, m_VBOs);
	glDeleteVertexArrays(1, &m_VAO);
}
//======================================================================================================
void Buffer::Destroy(const std::string& bufferID)
{
	//TODO - Destroy a specific buffer element (make this static?)
	//TODO - Destroy THIS buffer (and remove it from the map
	//TODO - Destroy ALL buffers (make this static?)
}