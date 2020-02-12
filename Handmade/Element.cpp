#include "Element.h"
#include "Shader.h"

bool Element::Create()
{
	
	//pre-calculate the total amount of bytes needed for the VBOs  
	//At a maximum we need enough space for 2 vertices (XYZ / RGBA)
	const int BYTES_PER_VERTEX = 3 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);

	//pre-calculate the total amount of bytes needed for the VBOs  
	const int TOTAL_BYTES_VERTEX_VBO = 2 * BYTES_PER_VERTEX;
	const int TOTAL_BYTES_COLOR_VBO =  2 * BYTES_PER_COLOR;

	//create VAO and VBOs and based on the maximum amount of vertices needed
	//A vertex needs only one slot while a vector or line segment use two
	if (!m_buffer.CreateBuffers("ELEMENT", 2))
	{
		return false;
	}

	//bind all VBOs and shader attributes together with VAO
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);

	//create empty VBOs to be filled later 
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::DYNAMIC_FILL);

	//store the buffer ID so that we can destroy the correct one later
	//m_bufferID = bufferID;

	return true;

}

//------------------------------------------------------------------------------------------------------
//function that renders a simple vertex on screen
//------------------------------------------------------------------------------------------------------
void Element::DrawVertex(GLfloat x, GLfloat y, GLfloat z,
	                     GLfloat r, GLfloat g, GLfloat b, GLfloat pointSize)
{

	//vertex and color data for a simple dot on the screen 
	//we add an extra vertex and color component because our
	//buffer has two slots and will render two points, so
	//this cheap hack will draw two points in the same place
	GLfloat vertices[] = { x, y, z, x, y, z };
	GLfloat colors[] = { r, g, b, r, g, b };

	//fill vertex and color buffer with above array data
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//set size of vertex and render it
	Shader::SetPointSize(pointSize);
	m_buffer.Draw(Buffer::POINTS);

}
//------------------------------------------------------------------------------------------------------
//function that renders a vector on screen
//------------------------------------------------------------------------------------------------------
void Element::DrawVector(GLfloat x, GLfloat y, GLfloat z,
	                     GLfloat r, GLfloat g, GLfloat b, GLfloat lineWidth)
{

	//data for vertex and color of vector which starts at an origin 
	//point and extends out at a size based on values passed in
	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f, x, y, z };
	GLfloat colors[] = { r, g, b, r, g, b };

	//fill vertex and color buffer with above array data
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//set width of vector and render it
	Shader::SetLineWidth(lineWidth);
	m_buffer.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that renders a line segment on screen
//------------------------------------------------------------------------------------------------------
void Element::DrawLineSegment(GLfloat x1, GLfloat y1, GLfloat z1,
	                          GLfloat x2, GLfloat y2, GLfloat z2,
	                          GLfloat r, GLfloat g, GLfloat b, GLfloat lineWidth)
{

	//data for vertex and color of vector which 
	//starts and ends at specified point passed in 
	GLfloat vertices[] = { x1, y1, z1, x2, y2, z2 };
	GLfloat colors[] = { r, g, b, r, g, b };

	//fill vertex and color buffer with above array data
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//set width of line segment and render it
	Shader::SetLineWidth(lineWidth);
	m_buffer.Draw(Buffer::LINES);

}

void Element::Destroy()
{

	m_buffer.DestroyBuffers("ELEMENT");

}