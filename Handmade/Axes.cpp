#include "Axes.h"
#include "Input.h"
#include "Shader.h"

//======================================================================================================
Axes::Axes(const std::string& filenameModel)
{
	m_isPrimitive = false;
	m_model.Load(filenameModel);

	//Not currently used
	//m_arrowTipPositionX = glm::vec3(0.0f);
	//m_arrowTipPositionY = glm::vec3(0.0f);
	//m_arrowTipPositionZ = glm::vec3(0.0f);
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
	if (m_isPrimitive)
	{
		m_buffer.Destroy();
	}
	else
	{
		m_model.Unload();
	}
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
//Not currently used
//const glm::vec3& Axes::GetArrowTipPositionX()
//{
//	return m_arrowTipPositionX;
//}
//
//const glm::vec3& Axes::GetArrowTipPositionY()
//{
//	return m_arrowTipPositionY;
//}
//
//const glm::vec3& Axes::GetArrowTipPositionZ()
//{
//	return m_arrowTipPositionZ;
//}
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

	if (m_isPrimitive)
	{
		m_buffer.Render(Buffer::RenderMode::Lines);
	}

	//Not currently used
	//else
	//{
	//	//We disable the depth testing so that the axes and labels always 
	////render in the front which means they are never obscured by anything 
	//	Screen::Instance()->IsDepthTestEnabled(false);

	//	//===========================================================================

	//	//This is the accumulated x-axis rotation made into a quaternion
	//	glm::quat rotationX = glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	//		glm::radians(m_eulerAngles.x),
	//		glm::vec3(1.0f, 0.0f, 0.0f));

	//	//This is the accumulated y-axis rotation made into a quaternion
	//	glm::quat rotationY = glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	//		glm::radians(m_eulerAngles.y),
	//		glm::vec3(0.0f, 1.0f, 0.0f));

	//	//===========================================================================
	//	//Rotation and display of the x-axis arrow and label
	//	//===========================================================================

	//	//The x-axis arrow must always begin with an initial rotation of 90 degrees around the z-axis 
	//	glm::quat initialRotationX = glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	//		glm::radians(-90.0f),
	//		glm::vec3(0.0f, 0.0f, 1.0f));

	//	//We use the total x and y rotation and multiply those in a specific order by the initial x rotation
	//	//This creates GLOBAL x and LOCAL y rotations. Swapping the order around will create different results
	//	m_transform.SetRotation(rotationX * rotationY * initialRotationX);

	//	shader.SendData("isTextured", false);
	//	shader.SendData("model", m_transform.GetMatrix());

	//	m_model.SetColor(2.0f, 0.0f, 0.0f, 0.25f);
	//	m_model.Render(shader);

	//	//===========================================================================
	//	//Rotation and display of the y-axis arrow and label
	//	//===========================================================================

	//	m_transform.SetRotation(rotationX * rotationY);

	//	shader.SendData("isTextured", false);
	//	shader.SendData("model", m_transform.GetMatrix());

	//	m_model.SetColor(0.0f, 2.0f, 0.0f, 0.25f);
	//	m_model.Render(shader);

	//	//===========================================================================
	//	//Rotation and display of the z-axis arrow and label
	//	//===========================================================================

	//	//The z-axis arrow must always begin with an initial rotation of 90 degrees around the x-axis 
	//	glm::quat initialRotationZ = glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	//		glm::radians(-90.0f),
	//		glm::vec3(1.0f, 0.0f, 0.0f));

	//	//We use the total x and y rotation and multiply those in a specific order by the initial z rotation
	//	//This creates GLOBAL x and LOCAL y rotations. Swapping the order around will create different results
	//	m_transform.SetRotation(rotationX * rotationY * initialRotationZ);

	//	shader.SendData("isTextured", false);
	//	shader.SendData("model", m_transform.GetMatrix());

	//	m_model.SetColor(0.0f, 0.0f, 2.0f, 0.25f);
	//	m_model.Render(shader);

	//	//===========================================================================

	//	m_arrowTipPositionX = rotationX * rotationY * glm::vec3(0.75f, 0.0f, 0.0f);
	//	m_arrowTipPositionY = rotationX * rotationY * glm::vec3(0.0f, 0.75f, 0.0f);
	//	m_arrowTipPositionZ = rotationX * rotationY * glm::vec3(0.0f, 0.0f, -0.75f);

	//	//===========================================================================

	//	Screen::Instance()->IsDepthTestEnabled(true);
	//}
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

	GLint vertices[] = { -m_size, 0, 0, m_size, 0, 0,
						  0, -m_size, 0, 0, m_size, 0,
						  0, 0, -m_size, 0, 0, m_size };

	GLfloat colors[] = { 1.0f, 0.0f, 0.196f, 1.0f, 1.0f, 0.0f, 0.196f, 1.0f,
						 0.196f, 1.0f, 0.0f, 1.0f, 0.196f, 1.0f, 0.0f, 1.0f,
						 0.0f, 0.564f, 1.0f, 1.0f, 0.0f, 0.564f, 1.0f, 1.0f };

	m_buffer.FillVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), Buffer::Fill::Once);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), Buffer::Fill::Once);
}