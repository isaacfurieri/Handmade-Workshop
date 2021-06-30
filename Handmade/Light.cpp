#include "Light.h"

GLuint Light::s_totalLights = 0;

//======================================================================================================
Light::Light()
{
	m_attLinear = 0.05f;
	m_attConstant = 0.2f;
	m_attQuadratic = 0.05f;

	m_position = glm::vec3(0.0f);

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);

	m_buffer.Create("Light", 1);

	GLfloat vertex[] = { 0.0f, 0.0f, 0.0f };
	GLfloat color[] = { m_ambient.r, m_ambient.g, m_ambient.b };

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertex, sizeof(vertex), Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, color, sizeof(color), Buffer::FILL_MANY);

	m_lightNumber = s_totalLights++;
}
//======================================================================================================
Light::~Light()
{
	m_buffer.Destroy("Light");
	s_totalLights--;
}
//======================================================================================================
void Light::SetAttenuationLinear(GLfloat attLinear)
{
	m_attLinear = attLinear;
}
//======================================================================================================
void Light::SetAttenuationConstant(GLfloat attConstant)
{
	m_attConstant = attConstant;
}
//======================================================================================================
void Light::SetAttenuationQuadratic(GLfloat attQuadratic)
{
	m_attQuadratic = attQuadratic;
}
//======================================================================================================
void Light::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{
	//the ambient color will also be the color of the actual light bulb (for now)
	m_ambient = glm::vec3(r, g, b);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, &m_ambient[0], sizeof(m_ambient), Buffer::FILL_MANY);
}
//======================================================================================================
void Light::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	m_diffuse = glm::vec3(r, g, b);
}
//======================================================================================================
void Light::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{
	m_specular = glm::vec3(r, g, b);
}
//======================================================================================================
void Light::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position = glm::vec3(x, y, z);
}
//======================================================================================================
void Light::Render(Shader& shader)
{
	//transform light in scene and apply to model matrix
	//APPLY HERE...

	//set flags in fragment shader - light bulb is not 
	//affected by lighting calculations and not textured
	//GameObject::SendToShader(false, false);

	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	//render light bulb in scene 
	Buffer::SetPointSize(25.0f);
	m_buffer.Render(Buffer::POINTS);
}
//======================================================================================================
void Light::SendToShader()
{
	//send total amount of lights to fragment shader so it can loop through them all
	Shader::Instance()->SendData("totalLights", s_totalLights);

	//send light position and color to fragment shader
	Shader::Instance()->SendData("light[" + std::to_string(m_lightNumber) + "].ambient", m_ambient);
	Shader::Instance()->SendData("light[" + std::to_string(m_lightNumber) + "].diffuse", m_diffuse);
	Shader::Instance()->SendData("light[" + std::to_string(m_lightNumber) + "].specular", m_specular);
	Shader::Instance()->SendData("light[" + std::to_string(m_lightNumber) + "].position", m_position);

	//send light attenuationo fragment shader
	Shader::Instance()->SendData("light[" + std::to_string(m_lightNumber) + "].attLinear", m_attLinear);
	Shader::Instance()->SendData("light[" + std::to_string(m_lightNumber) + "].attConstant", m_attConstant);
	Shader::Instance()->SendData("light[" + std::to_string(m_lightNumber) + "].attQuadratic", m_attQuadratic);
}