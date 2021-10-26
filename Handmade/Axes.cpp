#include "Axes.h"
#include "Input.h"
#include "Shader.h"

GLuint Axes::s_totalObjects = 0;
//======================================================================================================
Axes::Axes(const std::string& filenameModel)
{
	m_size = 0.0f;
	m_lineWidth = 0.0f;
	m_isPrimitive = false;
	m_arrowTipPositionX = glm::vec3(0.0f);
	m_arrowTipPositionY = glm::vec3(0.0f);
	m_arrowTipPositionZ = glm::vec3(0.0f);
	
	m_model.Load("Axes", filenameModel, true);
	m_model.SetModel("Axes");
}
//======================================================================================================
Axes::Axes(GLint size, GLfloat lineWidth)
{
	m_size = size;
	m_isPrimitive = true;
	m_lineWidth = lineWidth;
	Create();
}
//======================================================================================================
Axes::~Axes()
{
	//TODO - Unload buffer and model properly
	/*if (m_isPrimitive)
	{
		m_buffer.Destroy();
	}
	else
	{
		m_model.Unload();
	}*/
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
const glm::vec3& Axes::GetArrowTipPositionX() const
{
	return m_arrowTipPositionX;
}
//======================================================================================================
const glm::vec3& Axes::GetArrowTipPositionY() const
{
	return m_arrowTipPositionY;
}
//======================================================================================================
const glm::vec3& Axes::GetArrowTipPositionZ() const
{
	return m_arrowTipPositionZ;
}
//======================================================================================================
void Axes::Render(Shader& shader)
{
	if (m_isPrimitive)
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

	else
	{
		m_model.GetTransform() = m_transform;
		m_model.Render(shader);
	}

	m_arrowTipPositionX = m_transform.GetRotation() * glm::vec3(0.9f, 0.0f, 0.0f);
	m_arrowTipPositionY = m_transform.GetRotation() * glm::vec3(0.0f, 0.9f, 0.0f);
	m_arrowTipPositionZ = m_transform.GetRotation() * glm::vec3(0.0f, 0.0f, -0.9f);
}
//======================================================================================================
void Axes::Create()
{
	//We don't want to create new buffer 
	//objects everytime the axes are resized
	//TODO - Implement RAII properly
	/*if (!m_buffer.GetTag().empty())
	{
		m_buffer.Destroy();
	}*/

	//m_buffer.Create("Axes", 6);

	GLint vertices[] = { -m_size, 0, 0, m_size, 0, 0,
						  0, -m_size, 0, 0, m_size, 0,
						  0, 0, -m_size, 0, 0, m_size };

	GLfloat colors[] = { 1.0f, 0.0f, 0.196f, 1.0f, 1.0f, 0.0f, 0.196f, 1.0f,
						 0.196f, 1.0f, 0.0f, 1.0f, 0.196f, 1.0f, 0.0f, 1.0f,
						 0.0f, 0.564f, 1.0f, 1.0f, 0.0f, 0.564f, 1.0f, 1.0f };

	m_buffer.FillVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), Buffer::Fill::Once);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), Buffer::Fill::Once);
}