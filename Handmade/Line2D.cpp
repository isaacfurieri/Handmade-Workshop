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
	m_rotation.Rotate(0);

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
void Line2D::SetRotation(Transform rotation)
{

	m_rotation = rotation;

}
//------------------------------------------------------------------------------------------------------
//function that checks if line segment collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Line2D::IsColliding(const Sphere2D& secondSphere) const
{

	Vector2D<float> distanceFromLine;

	//calculate the distance the sphere and point on line segment are apart from each other
	//this makes use of inner function that calculates the point on line segment closest to sphere 
	distanceFromLine = secondSphere.GetPosition().Convert2D() - 
		               PointOnLine(secondSphere.GetPosition().X, secondSphere.GetPosition().Y);

	//return flag based on if line segment intersects with sphere
	return (distanceFromLine.Length() <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines point on line segment that is closest to position passed 
//------------------------------------------------------------------------------------------------------
Vector2D<float> Line2D::PointOnLine(float positionX, float positionY) const
{

	//variable to store normalized portion of line segment that point uses up
	float lineSegmentPortion;

	//first calculate distance vector between line segment's start and end point
	//also create a position vector out of the position X and Y values passed
	Vector2D<float> distance = m_endPoint - m_startPoint;
	Vector2D<float> tempPosition(positionX, positionY);
	
	//calculate the line segment portion using a dot
	//product formula and distance vector created above
	lineSegmentPortion = distance.DotProduct(tempPosition - m_startPoint) / 
		                 distance.DotProduct(distance);

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
		return 
		Vector2D<float>(m_startPoint + lineSegmentPortion * distance);
	}

}
//------------------------------------------------------------------------------------------------------
//function that calculates start and end position values of line segment for collision purposes
//------------------------------------------------------------------------------------------------------
void Line2D::Update()
{

	//convert line segment's position to a 2D object so that the calculations below will work
	Vector2D<float> position = m_position.Convert2D();

	//use the right vector to calculate line's end point below
	Vector2D<float> rightAxis = Vector2D<float>::RIGHT;

	//transform the right vector based on how line segment is rotated
	rightAxis = m_rotation.GetMatrix() * rightAxis * m_length * m_scale;

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
	TheDebug::Instance()->DrawLine(m_startPoint.X, m_startPoint.Y, 0, 
		                           m_endPoint.X, m_endPoint.Y, 0, 4, m_color, 1);

}