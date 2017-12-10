#include "Bound.h"

//------------------------------------------------------------------------------------------------------
//getter function that returns position of bound
//------------------------------------------------------------------------------------------------------
glm::vec3 Bound::GetPosition() const
{

	return m_position;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns position of bound
//------------------------------------------------------------------------------------------------------
void Bound::SetPosition(float x, float y, float z)
{

	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns color of bound
//------------------------------------------------------------------------------------------------------
void Bound::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	m_color = glm::vec4(r, g, b, a);

}