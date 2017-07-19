#include "Buffer.h"
#include "BufferManager.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
Buffer::Buffer()
{

	m_vertexBufferID = 0;
	m_colorBufferID = 0;
	m_normalBufferID = 0;
	m_textureBufferID = 0;

	m_vertexAttributeID = 0;
	m_colorAttributeID = 0;
	m_normalAttributeID = 0;
	m_textureAttributeID = 0;

	m_vertexComponentSize = XYZ;
	m_colorComponentSize = RGB;
	m_normalComponentSize = XYZ;
	m_textureComponentSize = UV;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to vector of vertices 
//------------------------------------------------------------------------------------------------------
std::vector<GLfloat>& Buffer::Vertices()
{

	return m_vertices;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to vector of colors 
//------------------------------------------------------------------------------------------------------
std::vector<GLfloat>& Buffer::Colors()
{

	return m_colors;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to vector of normals 
//------------------------------------------------------------------------------------------------------
std::vector<GLfloat>& Buffer::Normals()
{

	return m_normals;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to vector of texture coordinates 
//------------------------------------------------------------------------------------------------------
std::vector<GLfloat>& Buffer::Textures()
{

	return m_textures;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns OpenGL VBO ID value to buffer object
//------------------------------------------------------------------------------------------------------
void Buffer::SetBufferID(BufferType bufferType, const std::string& mapIndex)
{

	//based on which type of VBO ID needs to be assigned get the ID 
	//from the Buffer Manager based on index value passed and assign it 
	switch (bufferType)
	{

		case VERTEX_BUFFER:
		{
			m_vertexBufferID = TheBuffer::Instance()->
							   GetBufferID(BufferManager::VERTEX_BUFFER, mapIndex);
			break;
		}

		case COLOR_BUFFER:
		{
			m_colorBufferID = TheBuffer::Instance()->
					          GetBufferID(BufferManager::COLOR_BUFFER, mapIndex);
			break;
		}

		case NORMAL_BUFFER:
		{
			m_normalBufferID = TheBuffer::Instance()->
					           GetBufferID(BufferManager::NORMAL_BUFFER, mapIndex);
			break;
		}

		case TEXTURE_BUFFER:
		{
			m_textureBufferID = TheBuffer::Instance()->
					            GetBufferID(BufferManager::TEXTURE_BUFFER, mapIndex);
			break;
		}

	}

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns shader attribute ID value to buffer object
//------------------------------------------------------------------------------------------------------
void Buffer::SetAttributeID(BufferType bufferType, const std::string& mapIndex)
{

	//based on which type of shader attribute ID needs to be assigned get the ID 
	//from the Shader Manager based on index value passed and assign it 
	//the correct shaders need to be attached and linked before using them here!
	switch (bufferType)
	{

		case VERTEX_BUFFER:
		{
			m_vertexAttributeID = TheShader::Instance()->GetAttributeID(mapIndex);
			break;
		}

		case COLOR_BUFFER:
		{
			m_colorAttributeID = TheShader::Instance()->GetAttributeID(mapIndex);
			break;
		}

		case NORMAL_BUFFER:
		{
			m_normalAttributeID = TheShader::Instance()->GetAttributeID(mapIndex);
			break;
		}

		case TEXTURE_BUFFER:
		{
			m_textureAttributeID = TheShader::Instance()->GetAttributeID(mapIndex);
			break;
		}

	}

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns vertex, color, normal and texture data component size
//------------------------------------------------------------------------------------------------------
void Buffer::SetComponentSize(BufferType bufferType, ComponentSize componentSize)
{

	//based on which type of component needs to be assigned, 
	//assign the correct one using the value passed
	switch (bufferType)
	{

		case VERTEX_BUFFER:
		{
			m_vertexComponentSize = componentSize;
			break;
		}

		case COLOR_BUFFER:
		{
			m_colorComponentSize = componentSize;
			break;
		}

		case NORMAL_BUFFER:
		{
			m_normalComponentSize = componentSize;
			break;
		}

		case TEXTURE_BUFFER:
		{
			m_textureComponentSize = componentSize;
			break;
		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that adds buffer object's data to the OpenGL VBO 
//------------------------------------------------------------------------------------------------------
void Buffer::FillData(BufferType bufferType)
{

	//based on which type of VBO needs to be filled send 
	//the Buffer Manager all the data that needs to be added to the VBO 
	switch (bufferType)
	{

		case VERTEX_BUFFER:
		{
			TheBuffer::Instance()->Fill(m_vertexBufferID, m_vertices);
			break;
		}

		case COLOR_BUFFER:
		{
			TheBuffer::Instance()->Fill(m_colorBufferID, m_colors);
			break;
		}

		case NORMAL_BUFFER:
		{
			TheBuffer::Instance()->Fill(m_normalBufferID, m_normals);
			break;
		}

		case TEXTURE_BUFFER:
		{
			TheBuffer::Instance()->Fill(m_textureBufferID, m_textures);
			break;
		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that sends all the vertex, color, normal and texture coord buffer data to the shader
//------------------------------------------------------------------------------------------------------
void Buffer::DrawData(DrawMode drawMode)
{

	//variable to store OpenGL drawing mode 
	//to be passed to OpenGL during the draw call
	GLenum mode;

	//based on draw mode passed set OpenGL draw mode
	switch (drawMode)
	{
		case LINES:        { mode = GL_LINES; break; }
		case LINE_LOOP:    { mode = GL_LINE_LOOP; break; }
		case POINTS:       { mode = GL_POINTS; break; }
		case TRIANGLES:    { mode = GL_TRIANGLES; break; }
		case TRIANGLE_FAN: { mode = GL_TRIANGLE_FAN; break; }
	}

	//enable both VBO and shader attribute associated with vertex data of buffer object
	//link shader vertex attribute with the VBO buffer data as well
	TheBuffer::Instance()->Enable(m_vertexBufferID);
	TheShader::Instance()->EnableAttribute(m_vertexAttributeID);
	TheShader::Instance()->SetAttribute(m_vertexAttributeID, m_vertexComponentSize);
	
	//first check if there is any color data associated with buffer object
	//enable both VBO and shader attribute associated with color data of buffer object
	//link shader color attribute with the VBO buffer data as well
	if (m_colors.size() > 0)
	{
		TheBuffer::Instance()->Enable(m_colorBufferID);
		TheShader::Instance()->EnableAttribute(m_colorAttributeID);
		TheShader::Instance()->SetAttribute(m_colorAttributeID, m_colorComponentSize);
	}

	//first check if there is any normal data associated with buffer object
	//enable both VBO and shader attribute associated with normal data of buffer object
	//link shader normal attribute with the VBO buffer data as well
	if (m_normals.size() > 0)
	{
		TheBuffer::Instance()->Enable(m_normalBufferID);
		TheShader::Instance()->EnableAttribute(m_normalAttributeID);
		TheShader::Instance()->SetAttribute(m_normalAttributeID, m_normalComponentSize);
	}

	//first check if there is any texture coordinate data associated with buffer object
	//enable both VBO and shader attribute associated with texture data of buffer object
	//link shader texture coordinate attribute with the VBO buffer data as well
	if (m_textures.size() > 0)
	{
		TheBuffer::Instance()->Enable(m_textureBufferID);
		TheShader::Instance()->EnableAttribute(m_textureAttributeID);
		TheShader::Instance()->SetAttribute(m_textureAttributeID, m_textureComponentSize);
	}

	//pass all vertex, color, normal and texture coordinate 
	//data to shader to be drawn on screen, using the draw mode set earlier. 
	glDrawArrays(mode, 0, m_vertices.size() / m_vertexComponentSize);

	//disable all shader attributes
	TheShader::Instance()->DisableAttribute(m_vertexAttributeID);
	TheShader::Instance()->DisableAttribute(m_colorAttributeID);
	TheShader::Instance()->DisableAttribute(m_normalAttributeID);
	TheShader::Instance()->DisableAttribute(m_textureAttributeID);

	//unbind VBO so that there are no left over links
	TheBuffer::Instance()->Disable();

}