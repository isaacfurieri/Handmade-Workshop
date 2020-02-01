#include "GameObject.h"
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults 
//------------------------------------------------------------------------------------------------------
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

bool GameObject::IsLit()
{
	return m_isLit;
}

void GameObject::IsLit(bool isLit)
{
	m_isLit = isLit;
}

bool GameObject::IsAlive()
{
	return m_isAlive;
}

void GameObject::IsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

bool GameObject::IsActive()
{
	return m_isActive;
}

void GameObject::IsActive(bool isActive)
{
	m_isActive = isActive;
}

bool GameObject::IsVisible()
{
	return m_isVisible;
}

void GameObject::IsVisible(bool isVisible)
{
	m_isVisible = isVisible;
}

bool GameObject::IsTextured()
{
	return m_isTextured;
}

void GameObject::IsTextured(bool isTextured)
{
	m_isTextured = isTextured;
}

const std::string& GameObject::GetTag()
{
	return m_tag;
}

unsigned int GameObject::GetPriority()
{
	return m_priority;
}

void GameObject::SetTag(const std::string& tag)
{
	m_tag = tag;
}

void GameObject::SetPriority(unsigned int priority)
{
	m_priority = priority;
}
//------------------------------------------------------------------------------------------------------
//function that sends all game object's main properties to shaders
//------------------------------------------------------------------------------------------------------
void GameObject::SendToShader(bool isLit, bool isTextured)
{

	//pass lighting flag to fragment shader 
	//Shader::Instance()->SendUniformData("isLit", (GLint)isLit);

	//pass texturing flag to fragment shader 
	Shader::Instance()->SendUniformData("isTextured", (GLint)isTextured);

	//send model matrix to vertex shader
	Shader::Instance()->SendUniformData("model", m_modelMatrix);

}