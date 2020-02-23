#include "Circle.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Circle::Circle(GLfloat radius, GLuint slices, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	m_slices = slices;
	m_radius = radius;
	m_color = glm::vec4(r, g, b, a);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns the radius of the circle 
//------------------------------------------------------------------------------------------------------
void Circle::SetRadius(GLfloat radius)
{

	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offset = 0;

	//divide the circle into slices based on slices amount passed
	//the more slices, the more detailed the circle is drawn 
	GLfloat tempAngle = glm::radians(360.0f / (GLfloat)m_slices);

	//loop through all slices again and regenerate new vertices, 
	//taking the radius into account this time. We will also 
	//re-fill the vertex VBO with all of the new data as well

	for (GLuint i = 0; i < m_slices + 1; i++)
	{

		GLfloat vertices[] = { radius * cos(tempAngle * (i + 1)),      //X coord
							   radius * sin(tempAngle * (i + 1)),      //Y coord
							   0.0f                                };  //Z coord

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offset);
		offset += sizeof(vertices);
		
	}

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns the color of the circle 
//------------------------------------------------------------------------------------------------------
void Circle::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offset = 0;

	//add the first color to the buffer to represent the middle vertex
	GLfloat startColor[4] = { r, g, b, a };
	m_buffer.AppendVBO(Buffer::COLOR_BUFFER, startColor, 16, offset);

	//loop through all slices again and regenerate new 
	//colors and re-fill the color VBO with the new data

	for (GLuint i = 0; i < m_slices + 1; i++)
	{

		GLfloat colors[] = { r, g, b, a };

		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);
		offset += sizeof(colors);

	}

}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data  
//------------------------------------------------------------------------------------------------------
bool Circle::Create()
{

	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offsetVertex = 0;
	GLuint offsetColor = 0;

	//we need the amount of bytes to advance by for 
	//each iteration for the vertex and color VBOs
	const int BYTES_PER_VERTEX = 3 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);

	//pre-calculate the total amount of bytes needed for the VBOs
	//we add enough bytes here to accomodate for all the slices
	//an extra vertex is added to accomodate the middle point
	const int TOTAL_BYTES_VERTEX_VBO = (m_slices + 1) * BYTES_PER_VERTEX;
	const int TOTAL_BYTES_COLOR_VBO = (m_slices + 1) * BYTES_PER_COLOR;
	
	//create the buffer object to store all circle data
	//an extra vertex is added to accomodate the middle point
	if (!m_buffer.CreateBuffers("CIRCLE", m_slices + 1))
	{
		return false;
	}
	
	//bind all VBOs and shader attributes together with VAO
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);

	//create empty VBOs to be filled below 
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::DYNAMIC_FILL);
	
	//divide the circle into slices based on slices amount passed
	//the more slices, the more detailed the circle is drawn 
	GLfloat tempAngle = glm::radians(360.0f / (GLfloat)m_slices);

	//because we are using a triangle fan for rendering, we need a starting
	//vertex point. Set starting vertex to 0, which will be relative to where
	//the sphere is positioned in client code and set the starting color too
	GLfloat startVertex[3] = { 0.0f, 0.0f, 0.0f };
	GLfloat startColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, startVertex, BYTES_PER_VERTEX, offsetVertex);
	m_buffer.AppendVBO(Buffer::COLOR_BUFFER, startColor, BYTES_PER_COLOR, offsetColor);

	//loop through the amount of slices passed and add an extra slice into 
	//the loop to close the sphere off. The loop will use sin and cos internally
	//to generate a vertex point in a circular method around the origin
	//The generated vertices and color data will be added to the sphere's buffer
	//and the offset will get updated each iteration and keep track of how many
	//bytes into each VBO we already are in order to fill the VBOs correctly

	for (GLuint i = 0; i < m_slices + 1; i++)
	{

		GLfloat vertices[] = { m_radius * cos(tempAngle * (i + 1)),      //X coord
							   m_radius * sin(tempAngle * (i + 1)),      //Y coord
							   0.0f              	                 };  //Z coord

		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		//advance vertex and color VBO offsets
		offsetVertex += BYTES_PER_VERTEX;
		offsetColor += BYTES_PER_COLOR;

	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that renders circle on screen
//------------------------------------------------------------------------------------------------------
void Circle::Draw()
{

	SendToShader(false, false);
	m_buffer.Draw(Buffer::TRIANGLE_FAN);

}
//------------------------------------------------------------------------------------------------------
//function that destroys all buffer objects
//------------------------------------------------------------------------------------------------------
void Circle::Destroy()
{

	m_buffer.DestroyBuffers("CIRCLE");

}