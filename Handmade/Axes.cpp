#include "Axes.h"
#include "Input.h"
#include "Shader.h"

//======================================================================================================
Axes::Axes(GLint size, GLfloat lineWidth)
{
	m_size = size;
	m_lineWidth = lineWidth;
	Create();
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
	m_size = std::max(m_size, 1);
	Create();
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

	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"),
		Buffer::VBO::VertexBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::IntData);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"),
		Buffer::VBO::ColorBuffer, Buffer::ComponentSize::RGBA, Buffer::DataType::FloatData);

	shader.SendData("isTextured", false);
	shader.SendData("model", m_transform.GetMatrix());

	m_buffer.Render(Buffer::RenderMode::Lines);
}
//======================================================================================================
void Axes::Create()
{
	//We don't want to create new buffer 
	//objects everytime the axes are resized
	if (!m_buffer.GetTag().empty())
	{
		m_buffer.Destroy();
	}

	m_buffer.Create("Axes", 6);

	GLint vertices[] = { -m_size,     0,     0, m_size,    0,    0,           //X axis
							 0, -m_size,     0,    0, m_size,    0,           //Y axis
							 0,     0, -m_size,    0,    0, m_size };         //Z axis

	GLfloat colors[] = { 0.75f, 0.0f, 0.0f, 1.0f, 0.75f, 0.0f, 0.0f, 1.0f,    //X axis
						 0.0f, 0.75f, 0.0f, 1.0f, 0.0f, 0.75f, 0.0f, 1.0f,	  //Y axis	 
						 0.0f, 0.0f, 0.75f, 1.0f, 0.0f, 0.0f, 0.75f, 1.0f };  //Z axis

	m_buffer.FillVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), Buffer::Fill::Once);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), Buffer::Fill::Once);
}