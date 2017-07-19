#include "GameObject.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------
//static member variable initializations
//------------------------------------------------------------------------------------------------------
GLuint GameObject::s_modelUniformID = 0;
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
//static function that sends game object's model matrix data to the vertex shader
//------------------------------------------------------------------------------------------------------
void GameObject::ApplyMatrix()
{

	TheShader::Instance()->SetUniformMatrix(s_modelUniformID, &s_modelMatrix.back()[0][0]);

}
//------------------------------------------------------------------------------------------------------
//static setter function that assigns model matrix's shader uniform ID  
//------------------------------------------------------------------------------------------------------
void GameObject::SetModelUniformID(std::string uniformID)
{

	s_modelUniformID = TheShader::Instance()->GetUniformID(uniformID.c_str());

}
//------------------------------------------------------------------------------------------------------
//static function that transforms model matrix with passed quaternion rotation 
//------------------------------------------------------------------------------------------------------
void GameObject::MultiplyMatrix(Quaternion& quaternion)
{

	s_modelMatrix.back() = s_modelMatrix.back() * quaternion.GetMatrix();

}
//------------------------------------------------------------------------------------------------------
//static function that transforms model matrix with passed matrix transformation 
//------------------------------------------------------------------------------------------------------
void GameObject::MultiplyMatrix(glm::mat4& transformation)
{

	s_modelMatrix.back() = s_modelMatrix.back() * transformation;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults 
//------------------------------------------------------------------------------------------------------
GameObject::GameObject()
{

	m_isAlive = true;
	m_isActive = true;
	m_isVisible = true;

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