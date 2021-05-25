#include "GameObject.h"
#include "Shader.h"

//======================================================================================================
GameObject::GameObject()
{
	m_isLit = false;
	m_isAlive = true;
	m_isActive = true;
	m_isVisible = true;
	m_isTextured = false;

	m_tag = "";
	m_priority = 0;
	m_modelMatrix = glm::mat4(1.0f);
}
//======================================================================================================
bool GameObject::IsLit()
{
	return m_isLit;
}
//======================================================================================================
void GameObject::IsLit(bool flag)
{
	m_isLit = flag;
}
//======================================================================================================
bool GameObject::IsAlive()
{
	return m_isAlive;
}
//======================================================================================================
void GameObject::IsAlive(bool flag)
{
	m_isAlive = flag;
}
//======================================================================================================
bool GameObject::IsActive()
{
	return m_isActive;
}
//======================================================================================================
void GameObject::IsActive(bool flag)
{
	m_isActive = flag;
}
//======================================================================================================
bool GameObject::IsVisible()
{
	return m_isVisible;
}
//======================================================================================================
void GameObject::IsVisible(bool flag)
{
	m_isVisible = flag;
}
//======================================================================================================
bool GameObject::IsTextured()
{
	return m_isTextured;
}
//======================================================================================================
void GameObject::IsTextured(bool flag)
{
	m_isTextured = flag;
}
//======================================================================================================
const std::string& GameObject::GetTag()
{
	return m_tag;
}
//======================================================================================================
GLuint GameObject::GetPriority()
{
	return m_priority;
}
//======================================================================================================
void GameObject::SetTag(const std::string& tag)
{
	m_tag = tag;
}
//======================================================================================================
void GameObject::SetPriority(GLuint priority)
{
	m_priority = priority;
}
//======================================================================================================
void GameObject::SendToShader(bool isLit, bool isTextured)
{
	//pass lighting flag to fragment shader 
	//Shader::Instance()->SendUniformData("isLit", (GLint)isLit);

	//pass texturing flag to fragment shader 
	Shader::Instance()->SendUniformData("isTextured", (GLint)isTextured);

	//send model matrix to vertex shader
	Shader::Instance()->SendUniformData("model", m_modelMatrix);
}