#include "DebugManager.h"
#include "Line2D.h"
#include "Sphere2D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Line2D::Line2D()
{

	m_scale = 1.0f;
	m_length = 0.0f;
	m_color.A = 0.4f;
	m_color = Color::MAGENTA;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of line segment
//------------------------------------------------------------------------------------------------------
void Line2D::SetScale(float scale)
{

	m_scale = scale;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns length of line segment
//------------------------------------------------------------------------------------------------------
void Line2D::SetLength(float length)
{

	m_length = length;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns rotation of line segment
//------------------------------------------------------------------------------------------------------
void Line2D::SetRotation(glm::mat4& rotation)
{

	m_rotation = rotation;

}
//------------------------------------------------------------------------------------------------------
//function that checks if line segment collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Line2D::IsColliding(const Sphere2D& secondSphere) const
{

	glm::vec2 distanceFromLine;

	//calculate the distance the sphere and point on line segment are apart from each other
	//this makes use of inner function that calculates the point on line segment closest to sphere 
	distanceFromLine = glm::vec2(secondSphere.GetPosition()) - 
		               PointOnLine(secondSphere.GetPosition().x, secondSphere.GetPosition().y);

	//return flag based on if line segment intersects with sphere
	return (glm::length(distanceFromLine) <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines point on line segment that is closest to position passed 
//------------------------------------------------------------------------------------------------------
glm::vec2 Line2D::PointOnLine(float positionX, float positionY) const
{

	//variable to store normalized portion of line segment that point uses up
	float lineSegmentPortion;

	//first calculate distance vector between line segment's start and end point
	//also create a position vector out of the position X and Y values passed
	glm::vec2 distance = m_endPoint - m_startPoint;
	glm::vec2 tempPosition(positionX, positionY);
	
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
void Line2D::Update()
{

	//convert line segment's position to a 2D object so that the calculations below will work
	glm::vec2 position = glm::vec2(m_position);

	//use the right vector to calculate line's end point below
	glm::vec2 rightAxis = glm::vec2(1.0f, 0.0f);

	//transform the right vector based on how line segment is rotated
	rightAxis = glm::vec2(m_rotation * glm::vec4(rightAxis, 0.0f, 1.0f)) * m_length * m_scale;

	//the line segment's starting point is nothing more than its position and its
	//end point is based on its start point with the rotated right axis added on
	m_startPoint = position;
	m_endPoint = position + rightAxis;

}
//------------------------------------------------------------------------------------------------------
//function that renders a line segment 
//------------------------------------------------------------------------------------------------------
void Line2D::Draw()
{

	//draw line based on start and end point as well as color set and use a spacing of 1
	//because the pixel scale value is already integrated when the line points are set earlier
	//the start and end points already have translation, rotation and scale considered!! 
	TheDebug::Instance()->DrawLine(m_startPoint.x, m_startPoint.y, 0, 
		                           m_endPoint.x, m_endPoint.y, 0, 4, m_color, 1);

}