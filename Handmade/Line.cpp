#include "Line.h"

//======================================================================================================
Line::Line(GLfloat lineWidth, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_lineWidth = lineWidth;
	m_buffer.Create("Line", 2);

	GLfloat color[] = { r, g, b, a, r, g, b, a };
	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, color, sizeof(color), Buffer::FILL_MANY);
}
//======================================================================================================
Line::~Line()
{
	m_buffer.Destroy();
}
//======================================================================================================
void Line::SetEndPoints(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
	GLfloat vertices[] = { x1, y1, z1, x2, y2, z2 };
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_MANY);
}
//======================================================================================================
void Line::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Line::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a };

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
}
//======================================================================================================
void Line::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	Buffer::SetLineWidth(m_lineWidth);
	m_buffer.Render(Buffer::LINES);
}