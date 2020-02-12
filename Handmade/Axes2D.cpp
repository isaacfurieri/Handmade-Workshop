#include "Axes2D.h"
#include "Screen.h"
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Axes2D::Axes2D(GLint size, GLfloat lineWidth)
{

	m_size = size;
	m_lineWidth = lineWidth;

}

void Axes2D::SetSize(GLint size)
{

	m_size = size;

}

//------------------------------------------------------------------------------------------------------
//setter function that assigns thickness of each axis line
//------------------------------------------------------------------------------------------------------
void Axes2D::SetLineWidth(GLfloat lineWidth)
{

	m_lineWidth = lineWidth;

}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
bool Axes2D::Create()
{

	//create VAO and VBOs
	if (!m_buffer.CreateBuffers("AXES_2D", 4))
	{
		return false;
	}

	//first pre-calculate the pixels per unit based on screen setup
	GLint pixelsPerUnit = Screen::Instance()->GetPixelsPerUnit();

	//data that represents vertices for XY axis lines
	GLint vertices[] = { -m_size * pixelsPerUnit, 0, m_size * pixelsPerUnit, 0,        //X axis
		                  0, -m_size * pixelsPerUnit, 0, m_size* pixelsPerUnit   };   //Y axis

	//data that represents colors for axis lines
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,         //X axis        
		                 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f   };     //Y axis

	//bind all VBOs and shader attributes together with VAO
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::INT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);
	
	//fill vertex and color VBOs with the above array data
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders all axes on screen
//------------------------------------------------------------------------------------------------------
void Axes2D::Draw()
{

	Shader::SetLineWidth(m_lineWidth);
	SendToShader(false, false);
	m_buffer.Draw(Buffer::LINES);

}

void Axes2D::Destroy()
{

	m_buffer.DestroyBuffers("AXES_2D");

}