#include "Circle.h"

//======================================================================================================
Circle::Circle(GLfloat radius, GLuint slices, GLfloat r, GLfloat g, GLfloat b, GLfloat a) 
	: m_buffer("Circle", slices + 1)
{
	m_slices = slices;
	m_radius = radius;

	GLuint offsetVertex = 0;
	GLuint offsetColor = 0;

	const int BYTES_PER_VERTEX = 3 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);

	//We add enough bytes here to accomodate for all the slices
	//An extra vertex is added to accomodate the middle point
	const int TOTAL_BYTES_VERTEX_VBO = (m_slices + 1) * BYTES_PER_VERTEX;
	const int TOTAL_BYTES_COLOR_VBO = (m_slices + 1) * BYTES_PER_COLOR;

	//An extra vertex is added to accomodate the middle point
	//m_buffer.Create("Circle", m_slices + 1);

	m_buffer.FillVBO(Buffer::VBO::VertexBuffer, 
		nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::Fill::Ongoing);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, 
		nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::Fill::Ongoing);

	//The more slices, the more detailed the circle is drawn 
	GLfloat tempAngle = glm::radians(360.0f / static_cast<GLfloat>(m_slices));

	//Because we are using a triangle fan for rendering, we need a starting
	//vertex point. Set starting vertex to 0, which will be relative to where
	//the sphere is positioned in client code and set the starting color too
	glm::vec3 startVertex = glm::vec3(0.0f);
	glm::vec4 startColor = glm::vec4(1.0f);

	m_buffer.AppendVBO(Buffer::VBO::VertexBuffer, 
		&startVertex.x, BYTES_PER_VERTEX, offsetVertex);
	m_buffer.AppendVBO(Buffer::VBO::ColorBuffer, 
		&startColor.r, BYTES_PER_COLOR, offsetColor);

	//Loop through the amount of slices passed and add an extra slice into 
	//the loop to close the sphere off. The loop will use sin and cos internally
	//to generate a vertex point in a circular method around the origin
	//The generated vertices and color data will be added to the sphere's buffer
	//and the offset will get updated each iteration and keep track of how many
	//bytes into each VBO we already are in order to fill the VBOs correctly

	for (GLuint i = 0; i < m_slices + 1; i++)
	{
		GLfloat vertices[] = { m_radius * cos(tempAngle * (i + 1)),      //X coord
							   m_radius * sin(tempAngle * (i + 1)),      //Y coord
							   0.0f };  //Z coord

		GLfloat colors[] = { r, g, b, a };

		m_buffer.AppendVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX;
		offsetColor += BYTES_PER_COLOR;
	}
}
//======================================================================================================
Circle::~Circle()
{
	m_buffer.Destroy("Circle");
}
//======================================================================================================
void Circle::SetRadius(GLfloat radius)
{
	GLuint offset = 0;
	GLfloat tempAngle = glm::radians(360.0f / static_cast<GLfloat>(m_slices));

	for (GLuint i = 0; i < m_slices + 1; i++)
	{
		GLfloat vertices[] = { radius * cos(tempAngle * (i + 1)),
							   radius * sin(tempAngle * (i + 1)),
							   0.0f };

		m_buffer.AppendVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), offset);
		offset += sizeof(vertices);
	}
}
//======================================================================================================
void Circle::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Circle::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLuint offset = 0;
	glm::vec4 startColor = glm::vec4(r, g, b, a);
	m_buffer.AppendVBO(Buffer::VBO::ColorBuffer, &startColor.r, 16, offset);

	for (GLuint i = 0; i < m_slices + 1; i++)
	{
		GLfloat colors[] = { r, g, b, a };
		m_buffer.AppendVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), offset);
		offset += sizeof(colors);
	}
}
//======================================================================================================
void Circle::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), 
		Buffer::VBO::VertexBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), 
		Buffer::VBO::ColorBuffer, Buffer::ComponentSize::RGBA, Buffer::DataType::FloatData);
	
	m_buffer.Render(Buffer::RenderMode::TriangleFan);
}