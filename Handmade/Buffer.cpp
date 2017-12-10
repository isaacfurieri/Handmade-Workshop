#include <iostream>
#include "Buffer.h"
#include "PipelineManager.h"

//this allocated space remains in memory until the application ends
std::map<std::string, BufferID>* Buffer::s_bufferIDMap = new std::map<std::string, BufferID>;

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
//setter function that sets thickness of primitive line for rendering
//------------------------------------------------------------------------------------------------------
void Buffer::SetLineWidth(GLfloat lineWidth)
{

	glLineWidth(lineWidth);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets size of primitive vertex for rendering
//------------------------------------------------------------------------------------------------------
void Buffer::SetPointSize(GLfloat pointSize)
{

	glPointSize(pointSize);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns buffer IDs based on index value passed
//------------------------------------------------------------------------------------------------------
void Buffer::SetBuffers(const std::string& bufferID)
{

	std::cout << "Setting buffers to : " << "\"" << bufferID << "\"" << std::endl;

	//first check if buffer ID exists in map and if not display
	//error message, otherwise go ahead and assign the buffer ID

	auto it = s_bufferIDMap->find(bufferID);

	if (it == s_bufferIDMap->end())
	{
		std::cout << "Buffer IDs not found. Please enter a valid ID." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

	else
	{
		m_ID = it->second;
		std::cout << "Buffer IDs assigned successfully." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

}
//------------------------------------------------------------------------------------------------------
//function that creates a VAO, VBOs and an EBO and stores the ID in buffer map 
//------------------------------------------------------------------------------------------------------
bool Buffer::CreateBuffers(const std::string& bufferID, GLsizei totalVertices, bool hasEBO)
{

	std::cout << "Creating buffers in graphics memory : " << "\"" << bufferID << "\"" << std::endl;

	//first check if buffer ID exists in map and if it does display error message
	//and halt creation because we don't want to replace the existing buffers
	if (s_bufferIDMap->find(bufferID) != s_bufferIDMap->end())
	{
		std::cout << "Buffers already created in graphics memory." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//otherwise go ahead and create an ID for the VAO, VBOs and EBO and store in map

	glGenVertexArrays(1, &m_ID.vaoID);
	glGenBuffers(4, m_ID.vboID);
	glGenBuffers(1, &m_ID.eboID);

	m_ID.hasEBO = hasEBO;
	m_ID.totalVertices = totalVertices;

	(*s_bufferIDMap)[bufferID] = m_ID;

	std::cout << "Buffers created successfully."<< std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

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
		glVertexAttribPointer(ThePipeline::Instance()->GetShaderAttribute(vertAttrib), 
			                  componentSize, type, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(ThePipeline::Instance()->GetShaderAttribute(vertAttrib));

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

	std::cout << "Unloading all buffers from memory." << std::endl;

	//loop through entire buffer map in order to remove all buffer IDs
	for (auto it = s_bufferIDMap->begin(); it != s_bufferIDMap->end(); it++)
	{
		glDeleteVertexArrays(1, &(it->second.vaoID));
		glDeleteBuffers(4, it->second.vboID);
		glDeleteBuffers(1, &(it->second.eboID));
	}

	//clear the buffer ID map
	s_bufferIDMap->clear();

	std::cout << "---------------------------------------------------------------" << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that unloads a specific OpenGL buffer ID from memory
//------------------------------------------------------------------------------------------------------
void Buffer::DestroyBuffers(const std::string& bufferID)
{

	std::cout << "Unloading buffers : " << "\"" << bufferID << "\"" << std::endl;

	//check if buffer ID exists in map and if not display error message
	//otherwise remove that specific buffer ID and remove map element
	auto it = s_bufferIDMap->find(bufferID);

	if (it == s_bufferIDMap->end())
	{
		std::cout << "Buffer IDs not found. Please enter a valid ID." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

	else
	{
		glDeleteVertexArrays(1, &(it->second.vaoID));
		glDeleteBuffers(4, it->second.vboID);
		glDeleteBuffers(1, &(it->second.eboID));

		s_bufferIDMap->erase(it);

		std::cout << "Buffers unloaded successfully." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

}
//------------------------------------------------------------------------------------------------------
//function that displays total size of buffer ID map with details (FOR DEBUG ONLY)
//------------------------------------------------------------------------------------------------------
void Buffer::Output()
{

	//clear the console window for a fresh display
	system("cls");

	//display total amount of buffer IDs stored in map
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "Size of Buffer ID Map : " << s_bufferIDMap->size() << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//loop through map and display each buffer detailing its OpenGL IDs and tag name
	for (auto it = s_bufferIDMap->begin(); it != s_bufferIDMap->end(); it++)
	{
		std::cout << "\"" << it->first << "\"" << std::endl;

		std::cout << "VAO (ID " << it->second.vaoID << ")" << std::endl;
		std::cout << "VBO (IDs " << it->second.vboID[VERTEX_BUFFER] << ", "  
							     << it->second.vboID[COLOR_BUFFER] << ", " 
							     << it->second.vboID[NORMAL_BUFFER] << ", "
							     << it->second.vboID[TEXTURE_BUFFER] << ")" << std::endl;
		std::cout << "EBO (ID " << it->second.eboID << ")" << std::endl;
		std::cout << (it->second.hasEBO ? "This buffer has an EBO" : "No EBO") << std::endl;
		std::cout << it->second.totalVertices << " total vertices" << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

}