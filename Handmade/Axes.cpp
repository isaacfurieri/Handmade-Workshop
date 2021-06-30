#include "Axes.h"
#include "Screen.h"
#include "Shader.h"

//======================================================================================================
Axes::Axes(GLint size, GLfloat lineWidth)
{
	m_size = size;
	m_lineWidth = lineWidth;

	m_buffer.Create("Axes", 6);

	GLint vertices[] = { -m_size,     0,     0, m_size,    0,    0,      //X axis
							 0, -m_size,     0,    0, m_size,    0,      //Y axis
							 0,     0, -m_size,    0,    0, m_size };   //Z axis

	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,         //X axis
						 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,		 //Y axis	 
						 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };	     //Z axis

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_ONCE);
}
//======================================================================================================
Axes::~Axes()
{
	m_buffer.Destroy();
}
//======================================================================================================
void Axes::SetSize(GLint size)
{
	m_size = size;
}
//======================================================================================================
void Axes::SetLineWidth(GLfloat lineWidth)
{
	m_lineWidth = lineWidth;
}
//======================================================================================================
void Axes::Render(Shader& shader)
{
	Buffer::SetLineWidth(m_lineWidth);

	//SendToShader(false, false);

	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::INT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	m_buffer.Render(Buffer::LINES);
}

//=======================================================================================================
//OLD code to generate a 2D Axis (taken from Axes2D.cpp)
//=======================================================================================================

//bool Axes2D::Create()
//{
//
//	//create VAO and VBOs
//	if (!m_buffer.CreateBuffers("AXES_2D", 4))
//	{
//		return false;
//	}
//
//	//first pre-calculate the pixels per unit based on screen setup
//	GLint pixelsPerUnit = Screen::Instance()->GetPixelsPerUnit();
//
//	//data that represents vertices for XY axis lines
//	GLint vertices[] = { -m_size * pixelsPerUnit, 0, m_size * pixelsPerUnit, 0,        //X axis
//						  0, -m_size * pixelsPerUnit, 0, m_size * pixelsPerUnit };   //Y axis
//
//	//data that represents colors for axis lines
//	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,         //X axis        
//						 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };     //Y axis
//
//	//bind all VBOs and shader attributes together with VAO
//	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::INT);
//	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);
//
//	//fill vertex and color VBOs with the above array data
//	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
//	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);
//
//	return true;
//
//}