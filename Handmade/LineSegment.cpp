#include <assert.h>
#include "LineSegment.h"
#include "Plane.h"
#include "SphereCollider.h"

//======================================================================================================
LineSegment::LineSegment()
{
	m_scale = 1.0f;
	m_endPoint = glm::vec3(0.0f);
	m_startPoint = glm::vec3(0.0f);
	m_color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
//======================================================================================================
void LineSegment::SetScale(GLfloat scale)
{
	m_scale = scale;
}
//======================================================================================================
void LineSegment::SetStartPoint(const glm::vec3& startPoint)
{
	m_startPoint = startPoint;
}
//======================================================================================================
void LineSegment::SetStartPoint(GLfloat x, GLfloat y, GLfloat z)
{
	m_startPoint.x = x;
	m_startPoint.y = y;
	m_startPoint.z = z;
}
//======================================================================================================
void LineSegment::SetEndPoint(const glm::vec3& endPoint)
{
	m_endPoint = endPoint;
}
//======================================================================================================
void LineSegment::SetEndPoint(GLfloat x, GLfloat y, GLfloat z)
{
	m_endPoint.x = x;
	m_endPoint.y = y;
	m_endPoint.z = z;
}
//======================================================================================================
bool LineSegment::IsColliding(const SphereCollider& secondSphere) const
{
	//TODO - Should the radius not be scaled?
	return (glm::length(secondSphere.GetPosition() - PointOnLine(secondSphere.GetPosition())) <= 
		secondSphere.GetRadius());
}
//======================================================================================================
bool LineSegment::IsColliding(const Plane& secondPlane) const
{
	//TODO - Complete this
	//The line seg intersects the plane if the end points
	//are on different sides, (or are on the plane)
	return false;
}
//======================================================================================================
glm::vec3 LineSegment::PointOnLine(const glm::vec3& point) const
{
	return PointOnLine(point.x, point.y, point.z);
}
//======================================================================================================
glm::vec3 LineSegment::PointOnLine(GLfloat x, GLfloat y, GLfloat z) const
{
	auto lineSegment = m_endPoint - m_startPoint;
	assert(lineSegment != glm::vec3(0.0f));

	auto dot = glm::dot(lineSegment, 
		(glm::vec3(x, y, z) - m_startPoint)) / glm::dot(lineSegment, lineSegment);

	//Either the point is on either end of the 
	//line segment or its a value between 0 and 1 
	//meaning that its on the line somewhere

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