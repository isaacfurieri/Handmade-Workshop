#include <assert.h>
#include "Buffer.h"

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
	glPolygonMode(GL_FRONT_AND_BACK, renderStyle == RenderStyle::Polygonal ? GL_LINE : GL_FILL);
}
//======================================================================================================
Buffer::Buffer()
{
	m_EBO = 0;
	m_VAO = 0;
	m_hasEBO = false;
	m_totalVertices = 0;

	for (auto i = 0; i < TOTAL_BUFFERS; i++)
	{
		m_VBOs[i] = 0;
	}
}
//======================================================================================================
const std::string& Buffer::GetTag() const
{
	return m_tag;
}
//======================================================================================================
void Buffer::SetBuffer(const std::string& tag)
{
	auto it = s_buffers.find(tag);
	assert(it != s_buffers.end());
	*this = it->second;
}
//======================================================================================================
void Buffer::Create(const std::string& tag, GLsizei totalVertices, bool hasEBO)
{
	//If buffer ID exists in map halt creation because 
	//we don't want to replace the existing buffers
	assert(s_buffers.find(tag) == s_buffers.end());

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(TOTAL_BUFFERS, m_VBOs);

	if (hasEBO)
	{
		glGenBuffers(1, &m_EBO);
	}

	m_hasEBO = hasEBO;
	m_totalVertices = totalVertices;

	m_tag = tag;
	s_buffers[tag] = *this;
}
//======================================================================================================
void Buffer::FillEBO(const GLuint* data, GLsizeiptr bufferSize, Fill fill)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, data, static_cast<GLenum>(fill));
}
//======================================================================================================
void Buffer::FillVBO(VBO vbo, const void* data, GLsizeiptr bufferSize, Fill fill)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<int>(vbo)]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, static_cast<GLenum>(fill));
}
//======================================================================================================
void Buffer::AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::AppendVBO(VBO vbo, const void* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<int>(vbo)]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::LinkEBO()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(0);
}
//======================================================================================================
void Buffer::LinkVBO(GLint attributeID, VBO vbo, ComponentSize componentSize, DataType dataType)
{
	assert(attributeID > -1);
	
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<int>(vbo)]);

	glVertexAttribPointer(attributeID, static_cast<GLint>(componentSize),
		static_cast<GLenum>(dataType), GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(attributeID);
	glBindVertexArray(0);
}
//======================================================================================================
void Buffer::Render(RenderMode renderMode, GLuint index, GLuint totalVertices)
{
	glBindVertexArray(m_VAO);

	if (m_hasEBO)
	{
		if (index > 0)
		{
			glDrawElements(static_cast<GLenum>(renderMode),
				totalVertices > 0 ? totalVertices : m_totalVertices,
				GL_UNSIGNED_INT, (const void*)(index));
		}

		else
		{
			glDrawElements(static_cast<GLenum>(renderMode), 
				m_totalVertices, GL_UNSIGNED_INT, (const void*)(nullptr));
		}
	}

	else
	{
		glDrawArrays(static_cast<GLenum>(renderMode), 0, m_totalVertices);
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

	s_buffers.erase(s_buffers.find(m_tag));
}
//======================================================================================================
void Buffer::Destroy(const std::string& tag)
{
	//TODO - Destroy a specific buffer element (make this static?)
	//TODO - Destroy THIS buffer (and remove it from the map)
	//TODO - Destroy ALL buffers (make this static?)
}