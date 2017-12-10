#include "DebugManager.h"
#include "Line3D.h"
#include "Sphere3D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Line3D::Line3D()
{

	m_scale = 1.0f;
	m_length = 0.0f;
	m_color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of line segment
//------------------------------------------------------------------------------------------------------
void Line3D::SetScale(float scale)
{

	m_scale = scale;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns length of line segment
//------------------------------------------------------------------------------------------------------
void Line3D::SetLength(float length)
{

	m_length = length;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns rotation of line segment
//------------------------------------------------------------------------------------------------------
void Line3D::SetRotation(Quaternion rotation)
{

	m_rotation = rotation;

}
//------------------------------------------------------------------------------------------------------
//function that checks if line segment collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Line3D::IsColliding(const Sphere3D& secondSphere) const
{

	glm::vec3 distanceFromLine;

	//calculate the distance the sphere and point on line segment are apart from each other
	//this makes use of inner function that calculates the point on line segment closest to sphere 
	distanceFromLine = secondSphere.GetPosition() - PointOnLine(secondSphere.GetPosition().x, 
						                                        secondSphere.GetPosition().y, 
		                                                        secondSphere.GetPosition().z);

	//return flag based on if line segment intersects with sphere
	return (glm::length(distanceFromLine) <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines point on line segment that is closest to position passed 
//------------------------------------------------------------------------------------------------------
glm::vec3 Line3D::PointOnLine(float positionX, float positionY, float positionZ) const
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
//------------------------------------------------------------------------------------------------------
//function that calculates start and end position values of line segment for collision purposes
//------------------------------------------------------------------------------------------------------
void Line3D::Update()
{

	//use the right vector to calculate line's end point below
	glm::vec3 rightAxis = glm::vec3(1.0f, 0.0f, 0.0f); 

	//transform the right vector based on how line segment is rotated
	rightAxis = glm::vec3(m_rotation.GetMatrix() * glm::vec4(rightAxis, 1.0f)) * m_length * m_scale;

	//the line segment's starting point is nothing more than its position and its
	//end point is based on its start point with the rotated right axis added on
	m_startPoint = m_position;
	m_endPoint = m_position + rightAxis;

}
//------------------------------------------------------------------------------------------------------
//function that renders a line segment 
//------------------------------------------------------------------------------------------------------
void Line3D::Draw()
{

	//draw line based on start and end point as well as color set and remember that
	//the start and end points already have translation, rotation and scale considered!! 
	TheDebug::Instance()->DrawLine3D(m_startPoint.x, m_startPoint.y, m_startPoint.z,
		                             m_endPoint.x, m_endPoint.y, m_endPoint.z, 4, 
		                             m_color.r, m_color.g, m_color.b);

}