#include <glew.h>
#include "ScreenManager.h"
#include "PipelineManager.h"
#include "Text.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Text::Text()
{

	m_text = "";
	m_charSpace = 0.0f;
	m_spriteType = DYNAMIC;

	//default font texture dimensions are set to 16x16
	//as is setup in the Bitmap Font Builder textures
	m_textureDimension.x = 16;
	m_textureDimension.y = 16;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns string text to object
//------------------------------------------------------------------------------------------------------
void Text::SetText(const std::string& text)
{

	m_text = text;

	//offsets for VBO data loading below
	//buffers have different sizes
	GLuint offsetVert = 0;
	GLuint offsetColor = 0;
	GLuint offsetText = 0;
	GLuint offsetIndex = 0;
	glm::vec2 textureCell;

	//loop through the entire text string and 
	//create buffer data for each character
	for (size_t i = 0; i < m_text.size(); i++)
	{

		//***********************
		//vertices
		//***********************

		//data that represents vertices for text image
		//they are whole number values since a pixel is whole
		GLuint vertices[] = { 0 + i, 1, 0,
							  1 + i, 1, 0,
							  1 + i, 0, 0,
							  0 + i, 0, 0 };

		//fill vertex VBO and progress offset
		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVert);
		offsetVert += sizeof(vertices);


		//***********************
		//colors
		//***********************

		//data that represents colors for text image
		//they will all be white for each letter by default
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f };

		//fill color VBO and progress offset
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);
		offsetColor += sizeof(colors);


		//***********************
		//UVs
		//***********************

		//the texture index is the actual ASCII value of the letter
		int textureIndex = m_text[i];

		//use modulo and divide with the texture index to get exact column/row 
		//index to "cut out", because with text, the texture cell is dynamic
		textureCell.x = (float)(textureIndex % (int)m_textureDimension.x);
		textureCell.y = (float)(textureIndex / m_textureDimension.y);

		//calculate the width and height of each cell relative to the entire texture 
		//this gives us a normalized dimension value for each "cell" in the sprite sheet
		glm::vec2 cellDimension(1.0f / m_textureDimension.x, 1.0f / m_textureDimension.y);

		//take the desired cell to "cut out" and multiply it by the cell's dimension value
		//this gives us a normalized texture coordinate value that is our "starting point" 
		glm::vec2 texCoordOrigin = textureCell * cellDimension;

		//create new UV data that for our texture coordinates
		GLfloat UVs[] = { texCoordOrigin.x,                   texCoordOrigin.y,
						  texCoordOrigin.x + cellDimension.x, texCoordOrigin.y,
						  texCoordOrigin.x + cellDimension.x, texCoordOrigin.y + cellDimension.y,
						  texCoordOrigin.x,                   texCoordOrigin.y + cellDimension.y };

		//fill UV VBO and progress offset
		m_buffer.AppendVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), offsetText);
		offsetText += sizeof(UVs);


		//***********************
		//indices
		//***********************

		//data that represents indeces for text image
		GLuint indices[] = { 0 + 4 * i,
							 1 + 4 * i,
							 3 + 4 * i,

							 3 + 4 * i,
							 1 + 4 * i,
							 2 + 4 * i };

		//fill UV VBO and progress offset
		m_buffer.AppendEBO(indices, sizeof(indices), offsetIndex);
		offsetIndex += sizeof(indices);

	}

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns spacing size between text letters
//------------------------------------------------------------------------------------------------------
void Text::SetCharSpace(GLfloat charSpace)
{

	m_charSpace = charSpace;

}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
bool Text::Create(const std::string bufferID)
{

	//create VAO, VBOs and EBO and if there is an error
	//it means the buffer has already been created in memory
	if (!m_buffer.CreateBuffers(bufferID, 1000, true))
	{
		return false;
	}

	//bind EBO and all VBOs and shader attributes together with VAO
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::U_INT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::TEXTURE_BUFFER, "textureIn", Buffer::UV, Buffer::FLOAT);

	//fill vertex and color VBOs with data 
	m_buffer.FillEBO((GLuint*)nullptr, 10000, Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, 10000, Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, 10000, Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, (GLfloat*)nullptr, 10000, Buffer::DYNAMIC_FILL);

	return true;

}