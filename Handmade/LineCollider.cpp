#include "LineCollider.h"
#include "SphereCollider.h"

//======================================================================================================
LineCollider::LineCollider()
{
	m_scale = 1.0f;
	m_endPoint = glm::vec3(0.0f);
	m_startPoint = glm::vec3(0.0f);
	m_color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
//======================================================================================================
void LineCollider::SetScale(GLfloat scale)
{
	m_scale = scale;
}
//======================================================================================================
void LineCollider::SetStartPoint(const glm::vec3& startPoint)
{
	m_startPoint = startPoint;
}
//======================================================================================================
void LineCollider::SetStartPoint(GLfloat x, GLfloat y, GLfloat z)
{
	m_startPoint.x = x;
	m_startPoint.y = y;
	m_startPoint.z = z;
}
//======================================================================================================
void LineCollider::SetEndPoint(const glm::vec3& endPoint)
{
	m_endPoint = endPoint;
}
//======================================================================================================
void LineCollider::SetEndPoint(GLfloat x, GLfloat y, GLfloat z)
{
	m_endPoint.x = x;
	m_endPoint.y = y;
	m_endPoint.z = z;
}
//======================================================================================================
bool LineCollider::IsColliding(const SphereCollider& secondSphere) const
{
	//TODO - Should the radius not be scaled?
	return (glm::length(secondSphere.GetPosition() - PointOnLine(secondSphere.GetPosition())) <= 
		secondSphere.GetRadius());
}
//======================================================================================================
glm::vec3 LineCollider::PointOnLine(const glm::vec3& point) const
{
	return PointOnLine(point.x, point.y, point.z);
}
//======================================================================================================
glm::vec3 LineCollider::PointOnLine(GLfloat x, GLfloat y, GLfloat z) const
{
	glm::vec3 lineSegment = m_endPoint - m_startPoint;
	
	GLfloat dot = glm::dot(lineSegment, 
		(glm::vec3(x, y, z) - m_startPoint)) / glm::dot(lineSegment, lineSegment);

	if (dot <= 0.0f)
	{
		return m_startPoint;
	}

	else if (dot >= 1.0f)
	{
		return m_endPoint;
	}

	else
	{
		return (m_startPoint + dot * lineSegment);
	}
}
//======================================================================================================
void LineCollider::Update()
{
	//TODO - Figure out what is still required and clean this up 
	////use the right vector to calculate line's end point below
	//glm::vec3 rightAxis = glm::vec3(1.0f, 0.0f, 0.0f); 

	////transform the right vector based on how line segment is rotated
	//rightAxis = glm::vec3(m_rotation.GetMatrix() * glm::vec4(rightAxis, 1.0f)) * m_length * m_scale;

	////the line segment's starting point is nothing more than its position and its
	////end point is based on its start point with the rotated right axis added on
	//m_startPoint = m_position;
	//m_endPoint = m_position + rightAxis;
}