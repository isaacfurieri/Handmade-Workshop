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
}
//======================================================================================================
void Sphere::SetRadius(GLfloat radius)
{
	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offset = 0;

	//we first need to calculate the longitude and latitude angle
	GLfloat angleLongitude = glm::radians(360.0f / (GLfloat)m_segments);
	GLfloat angleLatitude = glm::radians(180.0f / (GLfloat)m_slices);

	//loop through all segments and slices again and regenerate 
	//new vertices, taking the radius into account this time
	//re-fill the vertex VBO with all of the new data as well

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
	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offset = 0;

	//loop through all segments and slices again and regenerate 
	//new colors, and re-fill the color VBO with the new data

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
bool Sphere::Create()
{
	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offsetVertex = 0;
	GLuint offsetColor = 0;
	GLuint offsetIndex = 0;

	//constants to help clarify different calculations below
	const int BYTES_PER_VERTEX = 3 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);
	const int BYTES_PER_TRIANGLE = 3 * sizeof(GLuint);

	//pre-calculate the total amount of bytes needed for the VBOs and EBO 
	const int TOTAL_BYTES_VERTEX_VBO = (m_slices + 1) * (m_segments + 1) * BYTES_PER_VERTEX;
	const int TOTAL_BYTES_COLOR_VBO = (m_slices + 1) * (m_segments + 1) * BYTES_PER_COLOR;
	const int TOTAL_BYTES_EBO = (m_slices - 1) * (m_segments)*BYTES_PER_TRIANGLE * 2;

	//create buffer object to store all sphere data and return false if failed
	//the amount of vertices depends on the segments and slices generated
	//we multiply by 6 because each slice creates 1 quad (2 triangles)
	//this is slightly different to the cuboid which has a static 36 vertices
	if (!m_buffer.CreateBuffers("SPHERE", m_segments * (m_slices - 1) * 6, true))
	{
		return false;
	}

	//bind EBO and all VBOs and shader attributes together with VAO
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);

	//create empty EBO and VBOs to be filled below 
	m_buffer.FillEBO((GLuint*)nullptr, TOTAL_BYTES_EBO, Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::DYNAMIC_FILL);

	//use this as a reference for sphere equation:
	//http://mathworld.wolfram.com/Sphere.html

	//we first need to calculate the longitude and latitude angle
	GLfloat angleLongitude = glm::radians(360.0f / (GLfloat)m_segments);
	GLfloat angleLatitude = glm::radians(180.0f / (GLfloat)m_slices);

	//loop through all segments of the sphere and for each segment loop through all slices
	//For each iteration we will generate vertices using the sphere formula and all vertices
	//and colors are then added to the VBO. The offset will get updated each iteration and keep
	//track of how many bytes into each VBO we already are in order to fill the VBOs correctly

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

	//loop through all segments and slices again and generate the indices 
	//that will make up the triangles that will fill the edge of the sphere

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
								 (i * (m_slices + 1)) + ((m_slices * 2)) - j,		 //Y
								 (i * (m_slices + 1)) + ((m_slices - 1)) - j };	 //Z

			m_buffer.AppendEBO(indices, sizeof(indices), offsetIndex);
			offsetIndex += BYTES_PER_TRIANGLE * 2;
		}
	}
}
//======================================================================================================
void Sphere::Draw()
{
	SendToShader(false, false);
	m_buffer.Draw(Buffer::TRIANGLES);
}
//======================================================================================================
void Sphere::Destroy()
{
	m_buffer.DestroyBuffers("SPHERE");
}