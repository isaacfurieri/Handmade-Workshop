#include "Point.h"

//======================================================================================================
Point::Point(GLfloat pointSize, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_pointSize = pointSize;
	m_buffer.Create("Point", 1);	
	m_color = glm::vec4(r, g, b, a);

	glm::vec3 vertex = glm::vec3(0.0f);

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, &vertex.x, sizeof(vertex), Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, &m_color.r, sizeof(m_color), Buffer::FILL_MANY);
}
//======================================================================================================
Point::~Point()
{
	m_buffer.Destroy("Point");
}
//======================================================================================================
void Point::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a };

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
}
//======================================================================================================
void Point::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	Buffer::SetPointSize(m_pointSize);
	m_buffer.Render(Buffer::POINTS);
}