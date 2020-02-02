#include <iostream>
#include "Buffer.h"
#include "Debug.h"
#include "Shader.h"

//this allocated space remains in memory until the application ends
std::map<std::string, BufferID>* Buffer::s_bufferIDMap = new std::map<std::string, BufferID>;

//------------------------------------------------------------------------------------------------------
//static function that displays total size of buffer ID map with details (DEBUG ONLY)
//------------------------------------------------------------------------------------------------------
void Buffer::Output()
{

	//clear the console window for a fresh display
	Debug::ClearLog();

	//display total amount of buffer IDs stored in map
	Debug::Log("===============================================================");
	Debug::Log("Size of Buffer ID Map: " + std::to_string(s_bufferIDMap->size()));
	Debug::Log("===============================================================");

	//loop through map and display each buffer detailing its OpenGL IDs and tag name
	for (auto it = s_bufferIDMap->begin(); it != s_bufferIDMap->end(); it++)
	{

		Debug::Log(it->first);
		Debug::Log("---------------------------------------------------------------");

		Debug::Log((GLfloat)it->second.vaoID, "VAO ID");
		Debug::Log((GLfloat)it->second.vboID[VERTEX_BUFFER], "VERTEX VBO ID");
		Debug::Log((GLfloat)it->second.vboID[COLOR_BUFFER], "COLOR VBO ID");
		Debug::Log((GLfloat)it->second.vboID[NORMAL_BUFFER], "NORMAL VBO ID");
		Debug::Log((GLfloat)it->second.vboID[TEXTURE_BUFFER], "TEXTURE VBO ID");
		Debug::Log((GLfloat)it->second.eboID, "EBO ID");

		(it->second.hasEBO) ? Debug::Log("This buffer has an EBO")
			                : Debug::Log("This buffer has no EBO");

		Debug::Log((GLfloat)it->second.totalVertices, "Total vertices");
		Debug::Log("===============================================================");

	}

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
Buffer::Buffer()
{

	m_ID.vaoID = 0;
	m_ID.eboID = 0;
	m_ID.vboID[VERTEX_BUFFER] = 0;
	m_ID.vboID[COLOR_BUFFER] = 0;
	m_ID.vboID[NORMAL_BUFFER] = 0;
	m_ID.vboID[TEXTURE_BUFFER] = 0;

	m_ID.hasEBO = false;
	m_ID.totalVertices = 0;

}

//------------------------------------------------------------------------------------------------------
//setter function that assigns buffer IDs based on index value passed
//------------------------------------------------------------------------------------------------------
void Buffer::SetBuffers(const std::string& bufferID)
{

	Debug::Log("Setting buffers to: '" + bufferID + "'");

	//first check if buffer ID exists in map and if not display
	//error message, otherwise go ahead and assign the buffer ID

	auto it = s_bufferIDMap->find(bufferID);

	if (it == s_bufferIDMap->end())
	{
		Debug::Log("Buffer IDs not found. Please enter a valid ID.", Debug::WARNING);
		Debug::Log("===============================================================");
	}

	else
	{
		m_ID = it->second;
		Debug::Log("Buffer IDs assigned successfully.", Debug::SUCCESS);
		Debug::Log("===============================================================");
	}

}
//------------------------------------------------------------------------------------------------------
//function that creates a VAO, VBOs and an EBO and stores the ID in buffer map 
//------------------------------------------------------------------------------------------------------
bool Buffer::CreateBuffers(const std::string& bufferID, GLsizei totalVertices, bool hasEBO)
{

	Debug::Log("Creating buffers in graphics memory: '" + bufferID + "'");

	//first check if buffer ID exists in map and if it does display error message
	//and halt creation because we don't want to replace the existing buffers
	if (s_bufferIDMap->find(bufferID) != s_bufferIDMap->end())
	{
		Debug::Log("Buffers already created in graphics memory.", Debug::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	//otherwise go ahead and create an ID for the VAO, VBOs and EBO and store in map

	glGenVertexArrays(1, &m_ID.vaoID);
	glGenBuffers(4, m_ID.vboID);
	glGenBuffers(1, &m_ID.eboID);

	m_ID.hasEBO = hasEBO;
	m_ID.totalVertices = totalVertices;

	(*s_bufferIDMap)[bufferID] = m_ID;

	Debug::Log("Buffers created successfully.", Debug::SUCCESS);
	Debug::Log("===============================================================");

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that associates VAO with EBO
//------------------------------------------------------------------------------------------------------
void Buffer::BindEBO()
{

	glBindVertexArray(m_ID.vaoID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID.eboID);

	glBindVertexArray(0);

}
//------------------------------------------------------------------------------------------------------
//function that associates VAO with VBO based on passed VBO type 
//------------------------------------------------------------------------------------------------------
void Buffer::BindVBO(VBOType vboType, const std::string& vertAttrib,
					 ComponentSize componentSize, DataType dataType)
{

	//assign correct data type to enum based on type passed
	//we need to send a GL enumerated type to the function below 
	GLenum type = (dataType == FLOAT) ? GL_FLOAT : GL_UNSIGNED_INT;

	//bind VAO with either the vertex, color, normal or texture VBO
	//here we also link the VBOs with their respective shader attributes
	glBindVertexArray(m_ID.vaoID);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
		glVertexAttribPointer(Shader::Instance()->GetAttributeID(vertAttrib), 
			                  componentSize, type, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(Shader::Instance()->GetAttributeID(vertAttrib));

	glBindVertexArray(0);

}
//------------------------------------------------------------------------------------------------------
//function that fills EBO with index data 
//------------------------------------------------------------------------------------------------------
void Buffer::FillEBO(const GLuint* data, GLsizeiptr size, FillType fillType)
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID.eboID);
	fillType == STATIC_FILL ? glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)
							: glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

}
//------------------------------------------------------------------------------------------------------
//function that fills VBO with integer data 
//------------------------------------------------------------------------------------------------------
void Buffer::FillVBO(VBOType vboType, const GLint* data, GLsizeiptr size, FillType fillType)
{

	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	fillType == STATIC_FILL ? glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)
		                    : glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

}
//------------------------------------------------------------------------------------------------------
//function that fills VBO with unsigned integer data 
//------------------------------------------------------------------------------------------------------
void Buffer::FillVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, FillType fillType)
{

	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	fillType == STATIC_FILL ? glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)
							: glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

}
//------------------------------------------------------------------------------------------------------
//function that fills VBO with float data 
//------------------------------------------------------------------------------------------------------
void Buffer::FillVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, FillType fillType)
{

	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	fillType == STATIC_FILL ? glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)
							: glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

}
//------------------------------------------------------------------------------------------------------
//function that adds index data to EBO at index position passed 
//------------------------------------------------------------------------------------------------------
void Buffer::AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset)
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID.eboID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);

}
//------------------------------------------------------------------------------------------------------
//function that adds integer data to VBO at index position passed 
//------------------------------------------------------------------------------------------------------
void Buffer::AppendVBO(VBOType vboType, const GLint* data, GLsizeiptr size, GLuint offset)
{

	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

}
//------------------------------------------------------------------------------------------------------
//function that adds unsigned integer data to VBO at index position passed 
//------------------------------------------------------------------------------------------------------
void Buffer::AppendVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, GLuint offset)
{

	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

}
//------------------------------------------------------------------------------------------------------
//function that adds float data to VBO at index position passed 
//------------------------------------------------------------------------------------------------------
void Buffer::AppendVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, GLuint offset)
{

	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

}
//------------------------------------------------------------------------------------------------------
//function that sends all buffer data to the vertex shader 
//------------------------------------------------------------------------------------------------------
void Buffer::Draw(DrawMode drawMode)
{

	//variable to store OpenGL drawing mode 
	//to be passed to OpenGL during the draw call
	GLenum mode;

	//based on draw mode passed set OpenGL draw mode
	switch (drawMode)
	{
		case LINES:        { mode = GL_LINES;        break; }
		case LINE_LOOP:    { mode = GL_LINE_LOOP;    break; }
		case POINTS:       { mode = GL_POINTS;       break; }
		case TRIANGLES:    { mode = GL_TRIANGLES;    break; }
		case TRIANGLE_FAN: { mode = GL_TRIANGLE_FAN; break; }
	}

	//bind VAO and render everything based on if there are indices or not
	glBindVertexArray(m_ID.vaoID);

		(m_ID.hasEBO) ? glDrawElements(mode, m_ID.totalVertices, GL_UNSIGNED_INT, 0)
				      : glDrawArrays(mode, 0, m_ID.totalVertices);

	glBindVertexArray(0);

}
//------------------------------------------------------------------------------------------------------
//function that unloads all OpenGL buffer IDs from memory
//------------------------------------------------------------------------------------------------------
void Buffer::DestroyBuffers()
{

	Debug::Log("Unloading all buffers from memory...");

	//loop through entire buffer map in order to remove all buffer IDs
	for (auto it = s_bufferIDMap->begin(); it != s_bufferIDMap->end(); it++)
	{
		glDeleteVertexArrays(1, &(it->second.vaoID));
		glDeleteBuffers(4, it->second.vboID);
		glDeleteBuffers(1, &(it->second.eboID));
	}

	//clear the buffer ID map
	s_bufferIDMap->clear();

	Debug::Log("Buffers unloaded successfully.", Debug::SUCCESS);
	Debug::Log("===============================================================");

}
//------------------------------------------------------------------------------------------------------
//function that unloads a specific OpenGL buffer ID from memory
//------------------------------------------------------------------------------------------------------
void Buffer::DestroyBuffers(const std::string& bufferID)
{

	Debug::Log("Unloading buffers: '" + bufferID + "'");

	//check if buffer ID exists in map and if not display error message
	//otherwise remove that specific buffer ID and remove map element
	auto it = s_bufferIDMap->find(bufferID);

	if (it == s_bufferIDMap->end())
	{
		Debug::Log("Buffer IDs not found. Please enter a valid ID.", Debug::WARNING);
		Debug::Log("===============================================================");
	}

	else
	{
		glDeleteVertexArrays(1, &(it->second.vaoID));
		glDeleteBuffers(4, it->second.vboID);
		glDeleteBuffers(1, &(it->second.eboID));

		s_bufferIDMap->erase(it);

		Debug::Log("Buffers unloaded successfully.", Debug::SUCCESS);
		Debug::Log("===============================================================");
	}

}