#include "Shader.h"
#include "Sphere.h"

//======================================================================================================
Sphere::Sphere(GLfloat radius, GLuint segments, GLuint slices,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a) : m_buffer("Sphere", segments * (slices - 1) * 6, true)
{
	m_slices = slices;
	m_radius = radius;
	m_segments = segments;
	m_color = glm::vec4(r, g, b, a);

	GLuint offsetVertex = 0;
	GLuint offsetColor = 0;
	GLuint offsetIndex = 0;

	const auto BYTES_PER_VERTEX =
		static_cast<GLuint>(Buffer::ComponentSize::XYZ) * sizeof(GLfloat);
	const auto BYTES_PER_COLOR =
		static_cast<GLuint>(Buffer::ComponentSize::RGBA) * sizeof(GLfloat);
	const auto BYTES_PER_TRIANGLE =
		static_cast<GLuint>(Buffer::ComponentSize::XYZ) * sizeof(GLuint);

	const auto TOTAL_BYTES_EBO = (m_slices - 1) * m_segments * BYTES_PER_TRIANGLE * 2;
	const auto TOTAL_BYTES_VERTEX_VBO = (m_slices + 1) * (m_segments + 1) * BYTES_PER_VERTEX;
	const auto TOTAL_BYTES_COLOR_VBO = (m_slices + 1) * (m_segments + 1) * BYTES_PER_COLOR;

	//We multiply by 6 because each slice creates 1 quad (2 triangles)
	//m_buffer.Create("Sphere", m_segments * (m_slices - 1) * 6, true);
	m_buffer.LinkEBO();

	m_buffer.FillEBO(nullptr, TOTAL_BYTES_EBO, Buffer::Fill::Ongoing);
	m_buffer.FillVBO(Buffer::VBO::VertexBuffer,
		nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::Fill::Ongoing);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer,
		nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::Fill::Ongoing);

	//Use this as a reference for sphere equation:
	//http://mathworld.wolfram.com/Sphere.html

	//We first need to calculate the longitude and latitude angle
	GLfloat angleLongitude = glm::radians(360.0f / static_cast<GLfloat>(m_segments));
	GLfloat angleLatitude = glm::radians(180.0f / static_cast<GLfloat>(m_slices));

	for (GLuint i = 0; i < m_segments + 1; i++)
	{
		for (GLuint j = 0; j <= m_slices; j++)
		{
			GLfloat vertices[] = { m_radius * cos(angleLongitude * i) * sin(angleLatitude * j),  //X 
								   m_radius * sin(angleLongitude * i) * sin(angleLatitude * j),  //Y 
								   m_radius * cos(angleLatitude * j) };                          //Z 

			GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a };

			m_buffer.AppendVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), offsetVertex);
			m_buffer.AppendVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), offsetColor);

			offsetVertex += BYTES_PER_VERTEX;
			offsetColor += BYTES_PER_COLOR;
		}
	}

	for (GLuint i = 0; i < m_segments; i++)
	{
		for (GLuint j = 0; j < m_slices - 1; j++)
		{
			GLuint indices[] = { (i * (m_slices + 1)) + j,                           //triangle 1 - X
								 (i * (m_slices + 1)) + j + 1,						 //triangle 1 - Y
								 (i * (m_slices + 1)) + j + m_slices + 2,            //triangle 1 - Z

								 (i * (m_slices + 1)) + ((m_slices * 2) + 1) - j,    //triangle 2 - X
								 (i * (m_slices + 1)) + ((m_slices * 2)) - j,		 //triangle 2 - Y
								 (i * (m_slices + 1)) + ((m_slices - 1)) - j };	     //triangle 2 - Z

			m_buffer.AppendEBO(indices, sizeof(indices), offsetIndex);
			offsetIndex += BYTES_PER_TRIANGLE * 2;
		}
	}
}
//======================================================================================================
Sphere::~Sphere()
{
	m_buffer.Destroy("Sphere");
}
//======================================================================================================
void Sphere::SetRadius(GLfloat radius)
{
	GLuint offset = 0;
	GLfloat angleLongitude = glm::radians(360.0f / static_cast<GLfloat>(m_segments));
	GLfloat angleLatitude = glm::radians(180.0f / static_cast<GLfloat>(m_slices));

	for (GLuint i = 0; i < m_segments + 1; i++)
	{
		for (GLuint j = 0; j <= m_slices; j++)
		{
			GLfloat vertices[] = { radius * cos(angleLongitude * i) * sin(angleLatitude * j),   //X 
								   radius * sin(angleLongitude * i) * sin(angleLatitude * j),   //Y 
								   radius * cos(angleLatitude * j) };                           //Z 

			m_buffer.AppendVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), offset);
			offset += sizeof(vertices);
		}
	}
}
//======================================================================================================
void Sphere::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Sphere::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLuint offset = 0;

	for (GLuint i = 0; i < m_segments + 1; i++)
	{
		for (GLuint j = 0; j <= m_slices; j++)
		{
			GLfloat colors[] = { r, g, b, a };
			m_buffer.AppendVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), offset);
			offset += sizeof(colors);
		}
	}
}
//======================================================================================================
void Sphere::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"),
		Buffer::VBO::VertexBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"),
		Buffer::VBO::ColorBuffer, Buffer::ComponentSize::RGBA, Buffer::DataType::FloatData);

	shader.SendData("model", m_transform.GetMatrix());
	shader.SendData("isTextured", static_cast<GLuint>(m_isTextured));

	m_buffer.Render(Buffer::RenderMode::Triangles);
}