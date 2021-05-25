#include "GameObject.h"
#include "Light.h"
#include "Shader.h"

GLuint Light::s_totalLights = 0;

//======================================================================================================
Light::Light()
{
	m_attLinear = 0.05f;
	m_attConstant = 0.2f;
	m_attQuadratic = 0.05f;

	m_position = glm::vec3(0.0f);

	//set light color to white by default
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);

	//assign light ID and total up the lights
	m_lightNumber = s_totalLights++;
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
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, &m_ambient[0], sizeof(m_ambient), Buffer::DYNAMIC_FILL);
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
void Light::Create(const std::string bufferID)
{
	//create VAO, VBOs and EBO
	m_buffer.CreateBuffers(bufferID, 1);

	//data that represents vertices and color for light bulb
	GLfloat vertex[] = { 0.0f, 0.0f, 0.0f };
	GLfloat color[] = { m_ambient.r, m_ambient.g, m_ambient.b };

	//bind all VBOs and shader attributes together with VAO
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);

	//fill vertex and color VBOs with data (for light bulb)
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertex, sizeof(vertex), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, color, sizeof(color), Buffer::DYNAMIC_FILL);
}
//======================================================================================================
void Light::Destroy(const std::string bufferID)
{
	m_buffer.DestroyBuffers(bufferID);
}
//======================================================================================================
void Light::Update()
{
	//FOR DEBUG ONLY
}
//======================================================================================================
void Light::Draw()
{
	//transform light in scene and apply to model matrix
	//APPLY HERE...

	//set flags in fragment shader - light bulb is not 
	//affected by lighting calculations and not textured
	//GameObject::SendToShader(false, false);

	//render light bulb in scene 
	Shader::SetPointSize(25.0f);
	m_buffer.Draw(Buffer::POINTS);
}
//======================================================================================================
void Light::SendToShader()
{
	//send total amount of lights to fragment shader so it can loop through them all
	Shader::Instance()->SendUniformData("totalLights", s_totalLights);

	//send light position and color to fragment shader
	Shader::Instance()->SendUniformData("light[" + std::to_string(m_lightNumber) + "].ambient", m_ambient);
	Shader::Instance()->SendUniformData("light[" + std::to_string(m_lightNumber) + "].diffuse", m_diffuse);
	Shader::Instance()->SendUniformData("light[" + std::to_string(m_lightNumber) + "].specular", m_specular);
	Shader::Instance()->SendUniformData("light[" + std::to_string(m_lightNumber) + "].position", m_position);

	//send light attenuation data to fragment shader
	Shader::Instance()->SendUniformData("light[" + std::to_string(m_lightNumber) + "].attLinear", m_attLinear);
	Shader::Instance()->SendUniformData("light[" + std::to_string(m_lightNumber) + "].attConstant", m_attConstant);
	Shader::Instance()->SendUniformData("light[" + std::to_string(m_lightNumber) + "].attQuadratic", m_attQuadratic);
}
//======================================================================================================
Light::~Light()
{
	s_totalLights--;
}