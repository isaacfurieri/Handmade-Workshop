#include "Light.h"

GLuint Light::s_totalLights = 0;

//======================================================================================================
Light::Light(GLfloat x, GLfloat y, GLfloat z) : m_buffer("Light", 1)
{
	m_attenuationLinear = 0.05f;
	m_attenuationConstant = 0.2f;
	m_attenuationQuadratic = 0.05f;

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
	m_transform.SetPosition(x, y, z);

	//TODO - Find a way to only create one single 
	//buffer to be shared amongst subsequent lights
	//m_buffer.Create("Light", 1);

	GLfloat vertex[] = { 0.0f, 0.0f, 0.0f };
	GLfloat color[] = { m_ambient.r, m_ambient.g, m_ambient.b, 1.0f };

	m_buffer.FillVBO(Buffer::VBO::VertexBuffer, vertex, sizeof(vertex), Buffer::Fill::Ongoing);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, color, sizeof(color), Buffer::Fill::Ongoing);

	m_lightNumber = s_totalLights++;
}
//======================================================================================================
Light::~Light()
{
	m_buffer.Destroy("Light");
	s_totalLights--;
}
//======================================================================================================
void Light::SetAttenuationLinear(GLfloat linear)
{
	m_attenuationLinear = linear;
}
//======================================================================================================
void Light::SetAttenuationConstant(GLfloat constant)
{
	m_attenuationConstant = constant;
}
//======================================================================================================
void Light::SetAttenuationQuadratic(GLfloat quadratic)
{
	m_attenuationQuadratic = quadratic;
}
//======================================================================================================
void Light::SetAttenuation(GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	m_attenuationLinear = linear;
	m_attenuationConstant = constant;
	m_attenuationQuadratic = quadratic;
}
//======================================================================================================
void Light::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient;
}
//======================================================================================================
void Light::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{
	//the ambient color will also be the color of the actual light bulb (for now)
	m_ambient.r = r;
	m_ambient.g = g;
	m_ambient.b = b;
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, &m_ambient.r, sizeof(m_ambient), Buffer::Fill::Ongoing);
}
//======================================================================================================
void Light::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse;
}
//======================================================================================================
void Light::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	m_diffuse.r = r;
	m_diffuse.g = g;
	m_diffuse.b = b;
}
//======================================================================================================
void Light::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular;
}
//======================================================================================================
void Light::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{
	m_specular.r = r;
	m_specular.g = g;
	m_specular.b = b;
}
//======================================================================================================
void Light::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"),
		Buffer::VBO::VertexBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"),
		Buffer::VBO::ColorBuffer, Buffer::ComponentSize::RGBA, Buffer::DataType::FloatData);

	Buffer::SetPointSize(25.0f);
	m_buffer.Render(Buffer::RenderMode::Points);
}
//======================================================================================================
void Light::SendToShader(Shader& shader)
{
	//Shader::Instance()->SendData("totalLights", s_totalLights);
	shader.SendData("model", m_transform.GetMatrix());
	shader.SendData("light.ambient", m_ambient);
	shader.SendData("light.diffuse", m_diffuse);
	shader.SendData("light.specular", m_specular);
	shader.SendData("light.position", m_transform.GetPosition());

	//Shader::Instance()->SendData("light.attenuationLinear", m_attenuationLinear);
	//Shader::Instance()->SendData("light.attenuationConstant", m_attenuationConstant);
	//Shader::Instance()->SendData("light.attenuationQuadratic", m_attenuationQuadratic);

	//For passing in an array of lights
	/*Shader::Instance()->SendData("light[" +
		std::to_string(m_lightNumber) + "].ambient", m_ambient);
	Shader::Instance()->SendData("light[" +
		std::to_string(m_lightNumber) + "].diffuse", m_diffuse);
	Shader::Instance()->SendData("light[" +
		std::to_string(m_lightNumber) + "].specular", m_specular);
	Shader::Instance()->SendData("light[" +
		std::to_string(m_lightNumber) + "].position", m_transform.GetPosition());

	Shader::Instance()->SendData("light[" +
		std::to_string(m_lightNumber) + "].attLinear", m_attenuationLinear);
	Shader::Instance()->SendData("light[" +
		std::to_string(m_lightNumber) + "].attConstant", m_attenuationConstant);
	Shader::Instance()->SendData("light[" +
		std::to_string(m_lightNumber) + "].attQuadratic", m_attenuationQuadratic);*/
}