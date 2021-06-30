#include "Shader.h"
#include "Sphere.h"

//======================================================================================================
Sphere::Sphere(GLfloat radius, GLuint segments, GLuint slices,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_slices = slices;
	m_radius = radius;
	m_segments = segments;
	m_color = glm::vec4(r, g, b, a);

	GLuint offsetVertex = 0;
	GLuint offsetColor = 0;
	GLuint offsetIndex = 0;

	const int BYTES_PER_VERTEX = 3 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);
	const int BYTES_PER_TRIANGLE = 3 * sizeof(GLuint);

	const int TOTAL_BYTES_VERTEX_VBO = (m_slices + 1) * (m_segments + 1) * BYTES_PER_VERTEX;
	const int TOTAL_BYTES_COLOR_VBO = (m_slices + 1) * (m_segments + 1) * BYTES_PER_COLOR;
	const int TOTAL_BYTES_EBO = (m_slices - 1) * (m_segments)*BYTES_PER_TRIANGLE * 2;

	//We multiply by 6 because each slice creates 1 quad (2 triangles)
	//This is slightly different to the cuboid which has a static 36 vertices
	m_buffer.Create("Sphere", m_segments * (m_slices - 1) * 6, true);
	m_buffer.LinkEBO();

	m_buffer.FillEBO((GLuint*)nullptr, TOTAL_BYTES_EBO, Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::FILL_MANY);

	//use this as a reference for sphere equation:
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

			m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
			m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

			offsetVertex += BYTES_PER_VERTEX;
			offsetColor += BYTES_PER_COLOR;
		}
	}

	for (GLuint i = 0; i < m_segments; i++)
	{
		for (GLuint j = 0; j < m_slices - 1; j++)
		{
			//triangle 1
			GLuint indices[] = { (i * (m_slices + 1)) + j,                               //X
								 (i * (m_slices + 1)) + j + 1,						     //Y
								 (i * (m_slices + 1)) + j + m_slices + 2,                //Z

								 //triangle 2
								 (i * (m_slices + 1)) + ((m_slices * 2) + 1) - j,        //X
								 (i * (m_slices + 1)) + ((m_slices * 2)) - j,		     //Y
								 (i * (m_slices + 1)) + ((m_slices - 1)) - j };	         //Z

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

			m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offset);
			offset += sizeof(vertices);
		}
	}
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
			m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);
			offset += sizeof(colors);
		}
	}
}
//======================================================================================================
void Sphere::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	//SendToShader(false, false);
	m_buffer.Render(Buffer::TRIANGLES);
}