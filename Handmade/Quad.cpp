#include "Input.h"
#include "Quad.h"
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Quad::Quad(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	m_color = glm::vec4(r, g, b, a);
	m_dimension = glm::vec2(width, height);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific size of quad 
//------------------------------------------------------------------------------------------------------
void Quad::SetDimension(GLfloat width, GLfloat height)
{

	//we need to halve the dimensions of the quad so 
	//that all vertices span out from the centre point
	glm::vec2 halfDimension = glm::vec2(width * 0.5f, height * 0.5f);

	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x, -halfDimension.y, 0.0f,
						   -halfDimension.x, -halfDimension.y, 0.0f };

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific color of quad 
//------------------------------------------------------------------------------------------------------
void Quad::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a };

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
bool Quad::Create()
{

	//create VAO and VBOs and based on the maximum amount of vertices needed
	//A quad needs 6 vertices for the 2 triangles it consists of
	if (!m_buffer.CreateBuffers("QUAD", 6, true))
	{
		return false;
	}

	//bind all VBOs and shader attributes together with VAO
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);

	//we need to halve the dimensions of the quad so 
	//that all vertices span out from the centre point
	glm::vec2 halfDimension = m_dimension * 0.5f;

	//data that represents vertices for quad 
	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x, -halfDimension.y, 0.0f,
						   -halfDimension.x, -halfDimension.y, 0.0f  };

	//data that represents colors for quad 
	GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a, 
						 m_color.r, m_color.g, m_color.b, m_color.a  };

	//data that represents indices for quad 
	GLuint indices[] = { 0, 1, 3,
						 3, 1, 2  };

	//create VBOs and fill them with the vertex and color data 
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);
	m_buffer.FillEBO(indices, sizeof(indices), Buffer::STATIC_FILL);

}
//------------------------------------------------------------------------------------------------------
//function that renders quad on screen
//------------------------------------------------------------------------------------------------------
void Quad::Draw()
{

	SendToShader(false, false);
	m_buffer.Draw(Buffer::TRIANGLES);

}
//------------------------------------------------------------------------------------------------------
//function that destroys all buffer objects
//------------------------------------------------------------------------------------------------------
void Quad::Destroy()
{

	m_buffer.DestroyBuffers("QUAD");

}