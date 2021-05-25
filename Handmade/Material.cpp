#include "Material.h"
#include "Shader.h"

//======================================================================================================
Material::Material()
{
	m_shininess = 1.0f;
	m_ambient = glm::vec3(0.1f);
	m_diffuse = glm::vec3(0.1f);
	m_specular = glm::vec3(0.0f);
}
//======================================================================================================
void Material::SetShininess(GLfloat shininess)
{
	m_shininess = shininess;
}
//======================================================================================================
void Material::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{
	m_ambient = glm::vec3(r, g, b);
}
//======================================================================================================
void Material::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	m_diffuse = glm::vec3(r, g, b);
}
//======================================================================================================
void Material::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{
	m_specular = glm::vec3(r, g, b);
}
//======================================================================================================
void Material::SendToShader()
{
	Shader::Instance()->SendUniformData("material.ambient", m_ambient);
	Shader::Instance()->SendUniformData("material.diffuse", m_diffuse);
	Shader::Instance()->SendUniformData("material.specular", m_specular);
	Shader::Instance()->SendUniformData("material.shininess", m_shininess);
}