#include "LineCollider.h"
#include "SphereCollider.h"

//======================================================================================================
LineCollider::LineCollider()
{
	m_scale = 1.0f;
	m_length = 0.0f;
	m_endPoint = glm::vec3(0.0f);
	m_startPoint = glm::vec3(0.0f);
	m_color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
//======================================================================================================
//void LineCollider::SetScale(float scale)
//{
//	m_scale = scale;
//}
//======================================================================================================
//void LineCollider::SetLength(float length)
//{
//	m_length = length;
//}
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
	glm::vec3 distanceFromLine;

	//calculate the distance the sphere and point on line segment are apart from each other
	//this makes use of inner function that calculates the point on line segment closest to sphere 
	distanceFromLine = secondSphere.GetPosition() - PointOnLine(secondSphere.GetPosition().x,
		secondSphere.GetPosition().y,
		secondSphere.GetPosition().z);

	//TODO - Should the radius not be scaled?
	return (glm::length(distanceFromLine) <= secondSphere.GetRadius());
}
//======================================================================================================
glm::vec3 LineCollider::PointOnLine(GLfloat positionX, GLfloat positionY, GLfloat positionZ) const
{
	//variable to store normalized portion of line segment that point uses up
	float lineSegmentPortion;

	//first calculate distance vector between line segment's start and end point
	//also create a position vector out of the position X, Y and Z values passed
	glm::vec3 distance = m_endPoint - m_startPoint;
	glm::vec3 tempPosition(positionX, positionY, positionZ);

	//calculate the line segment portion using a dot
	//product formula and distance vector created above
	lineSegmentPortion = glm::dot(distance, (tempPosition - m_startPoint)) /
		glm::dot(distance, distance);

	//if the line segment portion is zero or less the
	//point closest to the sphere is the line's start point
	if (lineSegmentPortion <= 0.0f)
	{
		return m_startPoint;
	}

	//if the line segment portion is one or more the
	//point closest to the sphere is the line's end point
	else if (lineSegmentPortion >= 1.0f)
	{
		return m_endPoint;
	}

	//otherwise the line segment portion is a value between 0 and 1 
	//meaning that the point closest to the sphere is on the line 
	//somewhere, so use another formula to calculate that point exactly
	else
	{
		return (m_startPoint + lineSegmentPortion * distance);
	}
}
//======================================================================================================
void LineCollider::Update()
{
	////use the right vector to calculate line's end point below
	//glm::vec3 rightAxis = glm::vec3(1.0f, 0.0f, 0.0f); 

	////transform the right vector based on how line segment is rotated
	//rightAxis = glm::vec3(m_rotation.GetMatrix() * glm::vec4(rightAxis, 1.0f)) * m_length * m_scale;

	////the line segment's starting point is nothing more than its position and its
	////end point is based on its start point with the rotated right axis added on
	//m_startPoint = m_position;
	//m_endPoint = m_position + rightAxis;
}