#include <gtc\matrix_transform.hpp>
#include "GameObject.h"
#include "PipelineManager.h"
#include "ScreenManager.h"

glm::mat3 GameObject::s_normalMatrix;
glm::mat4 GameObject::s_textureMatrix;
std::vector<glm::mat4> GameObject::s_modelMatrix;

//------------------------------------------------------------------------------------------------------
//static setter function that resets model matrix to the identity 
//------------------------------------------------------------------------------------------------------
void GameObject::SetIdentity()
{

	s_modelMatrix.back() = glm::mat4(1.0f);

}
//------------------------------------------------------------------------------------------------------
//static function that adds a new transformation to the matrix stack
//------------------------------------------------------------------------------------------------------
void GameObject::PushMatrix()
{

	s_modelMatrix.push_back(s_modelMatrix.back());

}
//------------------------------------------------------------------------------------------------------
//static function that removes last transformation from matrix stack
//------------------------------------------------------------------------------------------------------
void GameObject::PopMatrix()
{

	//only remove transformation if there are multiple ones available
	//there always needs to be at least one transformation present!
	if (s_modelMatrix.size() > 1)
	{
		s_modelMatrix.pop_back();
	}

}
//------------------------------------------------------------------------------------------------------
//static function that sends all game object's main properties to shaders
//------------------------------------------------------------------------------------------------------
void GameObject::SendToShader(bool isLit, bool isTextured)
{

	//pass lighting flag to fragment shader 
	ThePipeline::Instance()->SendUniformData("isLit", (GLint)isLit);

	//pass texturing flag to fragment shader 
	ThePipeline::Instance()->SendUniformData("isTextured", (GLint)isTextured);

	//convert model matrix to 3x3 and invert it for normals to use in shader
	s_normalMatrix = glm::inverse(glm::mat3(s_modelMatrix.back()));

	//send model matrix to vertex shader
	ThePipeline::Instance()->SendUniformData("modelMatrix", s_modelMatrix.back());

	//send normal matrix to vertex shader (transposed)
	ThePipeline::Instance()->SendUniformData("normMatrix", s_normalMatrix, true);

	//send texture matrix to vertex shader
	ThePipeline::Instance()->SendUniformData("texMatrix", s_textureMatrix);

}
//------------------------------------------------------------------------------------------------------
//static function that applies passed translation values to model matrix
//------------------------------------------------------------------------------------------------------
void GameObject::Translate(GLfloat x, GLfloat y, GLfloat z)
{

	s_modelMatrix.back() = glm::translate(s_modelMatrix.back(), glm::vec3(x, y, z));

}
//------------------------------------------------------------------------------------------------------
//static function that applies passed quaternion rotation to model matrix
//------------------------------------------------------------------------------------------------------
void GameObject::Rotate(Quaternion& quaternion)
{

	s_modelMatrix.back() = s_modelMatrix.back() * quaternion.GetMatrix();

}
//------------------------------------------------------------------------------------------------------
//static function that applies passed euler angle values to model matrix
//------------------------------------------------------------------------------------------------------
void GameObject::Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{

	s_modelMatrix.back() = glm::rotate(s_modelMatrix.back(), glm::radians(angle), glm::vec3(x, y, z));

}
//------------------------------------------------------------------------------------------------------
//static function that applies passed scale values to model matrix
//------------------------------------------------------------------------------------------------------
void GameObject::Scale(GLfloat x, GLfloat y, GLfloat z)
{

	s_modelMatrix.back() = glm::scale(s_modelMatrix.back(), glm::vec3(x, y, z));

}
//------------------------------------------------------------------------------------------------------
//static function that applies passed scale values to texture matrix
//------------------------------------------------------------------------------------------------------
void GameObject::ScaleUV(GLfloat x, GLfloat y)
{

	s_textureMatrix = glm::mat4(1.0f);

	//scale texture matrix based on scale factor set (if any) 
	s_textureMatrix = glm::scale(s_textureMatrix, glm::vec3(x, y, 1.0f));

}
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

	//add the initial model transformation into the vector so that
	//there is always at least one transformation present and only  
	//do this if vector is empty (the first game object to be created)
	if (s_modelMatrix.empty())
	{
		s_modelMatrix.push_back(glm::mat4(1.0f));
	}

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag reference
//------------------------------------------------------------------------------------------------------
bool& GameObject::IsLit()
{

	return m_isLit;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns memory flag reference
//------------------------------------------------------------------------------------------------------
bool& GameObject::IsAlive()
{

	return m_isAlive;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns active flag reference
//------------------------------------------------------------------------------------------------------
bool& GameObject::IsActive()
{

	return m_isActive;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns visibility flag reference
//------------------------------------------------------------------------------------------------------
bool& GameObject::IsVisible()
{

	return m_isVisible;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag reference
//------------------------------------------------------------------------------------------------------
bool& GameObject::IsTextured()
{

	return m_isTextured;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns game object's tag variable
//------------------------------------------------------------------------------------------------------
std::string GameObject::GetTag()
{

	return m_tag;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns game object's priority variable
//------------------------------------------------------------------------------------------------------
unsigned int GameObject::GetPriority()
{

	return m_priority;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns game object's tag variable
//------------------------------------------------------------------------------------------------------
void GameObject::SetTag(std::string tag)
{

	m_tag = tag;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns game object's priority variable
//------------------------------------------------------------------------------------------------------
void GameObject::SetPriority(unsigned int priority)
{

	m_priority = priority;

}