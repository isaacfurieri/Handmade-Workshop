#include "Grid2D.h"
#include "Screen.h"
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Grid2D::Grid2D(GLuint size, GLfloat lineWidth)
{

	m_size = size;
	m_lineWidth = lineWidth;

}

void Grid2D::SetSize(GLuint size)
{

	m_size = size;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns thickness of grid lines
//------------------------------------------------------------------------------------------------------
void Grid2D::SetLineWidth(GLfloat lineWidth)
{

	m_lineWidth = lineWidth;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns color of grid lines
//------------------------------------------------------------------------------------------------------
void Grid2D::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offset = 0;

	//loop through all elements in color VBO and fill with the RGB 
	//values. We multiply grid size by 4 to account for the quadrants 
	for (int i = 0; i < m_size * 4; i++)
	{

		GLfloat colors[] = { r, g, b, a, r, g, b, a };

		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);
		offset += sizeof(colors);

	}

}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data  
//------------------------------------------------------------------------------------------------------
bool Grid2D::Create()
{

	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offsetColor = 0;
	GLuint offsetVertex = 0;

	//constants to help clarify different calculations below
	const int QUADRANTS = 4;
	const int BYTES_PER_VERTEX = 2 * sizeof(GLint);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);

	//pre-calculate the total amount of bytes needed for the VBOs  
	//the vertex VBO has 2 vertices, each one with an XY component
	//the color VBO also has 2 vertices, each with a RGBA component
	const int TOTAL_BYTES_VERTEX_VBO = m_size * QUADRANTS * BYTES_PER_VERTEX * 2;
	const int TOTAL_BYTES_COLOR_VBO = m_size * QUADRANTS * BYTES_PER_COLOR * 2;

	//create VAO and VBOs which is based on the total amount of
	//lines and quadrants and multiplied by 2 to represent each vertex
	if (!m_buffer.CreateBuffers("GRID_2D", m_size * QUADRANTS * 2))
	{
		return false;
	}

	//bind all VBOs and shader attributes together with VAO
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::INT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);

	//create empty VBOs to be filled below 
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLint*)nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::STATIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::STATIC_FILL);

	//first pre-calculate the pixels per unit based on screen setup
	GLuint pixelsPerUnit = Screen::Instance()->GetPixelsPerUnit();

	//now we create the grid one quadrant at a time	and fill each vertex and
	//color VBO with the line's vertex and color data accordingly. The offset
	//will get updated each iteration and keep track of how many bytes into
	//each VBO we already are in order to fill the VBOs in the right place

	//**********************************
	//create all negative X lines
	//**********************************

	for (int i = 0; i < m_size; i++)
	{

		GLint vertices[] = { (-m_size * pixelsPerUnit) + (i * pixelsPerUnit),
							 (-m_size * pixelsPerUnit),                            //first vertex
							 (-m_size * pixelsPerUnit) + (i * pixelsPerUnit),
							   m_size * pixelsPerUnit };                           //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;

	}

	//**********************************
	//create all positive X lines
	//**********************************

	for (int i = 1; i < m_size + 1; i++)
	{

		GLint vertices[] = {  0 + (i * pixelsPerUnit), -m_size * pixelsPerUnit,     //first vertex
							  0 + (i * pixelsPerUnit),  m_size * pixelsPerUnit  };  //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;

	}

	//**********************************
	//create all negative Y lines
	//**********************************

	for (int i = 0; i < m_size; i++)
	{

		GLint vertices[] = {  -m_size * pixelsPerUnit,
							 (-m_size * pixelsPerUnit) + (i * pixelsPerUnit),      //first vertex
							   m_size * pixelsPerUnit,
							 (-m_size * pixelsPerUnit) + (i * pixelsPerUnit)   };  //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;

	}

	//**********************************
	//create all positive Y lines
	//**********************************

	for (int i = 1; i < m_size + 1; i++)
	{

		GLint vertices[] = { -m_size * pixelsPerUnit, 0 + (i * pixelsPerUnit),      //first vertex
							  m_size * pixelsPerUnit, 0 + (i * pixelsPerUnit)   };  //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;

	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sets the grid line thickness and renders the grid on screen
//------------------------------------------------------------------------------------------------------
void Grid2D::Draw()
{

	Shader::SetLineWidth(m_lineWidth);
	m_buffer.Draw(Buffer::LINES);

}

void Grid2D::Destroy()
{

	m_buffer.DestroyBuffers("GRID_2D");

}