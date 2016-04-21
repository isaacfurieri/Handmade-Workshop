#include <algorithm>
#include "DebugManager.h"
#include "Sphere2D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sphere2D::Sphere2D()
{

	m_scale = 1.0f;
	m_radius = 0.0f;
	m_color.A = 0.4f;
	m_color = Color::GREEN;
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns radius of sphere
//------------------------------------------------------------------------------------------------------
float Sphere2D::GetRadius() const
{

	return m_radius;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of sphere
//------------------------------------------------------------------------------------------------------
void Sphere2D::SetScale(float scale)
{

	m_scale = scale;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension of sphere
//------------------------------------------------------------------------------------------------------
void Sphere2D::SetDimension(float dimension)
{

	m_dimension = dimension;

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a AABB object
//------------------------------------------------------------------------------------------------------
bool Sphere2D::IsColliding(const AABB2D& secondBox) const
{

	//make use of AABB's box-sphere collision function
	return (secondBox.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a line segment
//------------------------------------------------------------------------------------------------------
bool Sphere2D::IsColliding(const Line2D& secondLine) const
{

	//make use of Line2D's line-sphere collision function
	return (secondLine.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a plane
//------------------------------------------------------------------------------------------------------
bool Sphere2D::IsColliding(const Plane2D& secondPlane) const
{

	//make use of Plane2D's plane-sphere collision function
	return (secondPlane.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Sphere2D::IsColliding(const Sphere2D& secondSphere) const
{

	//first calculate distance between both spheres and store that temporarily
	float distance = (m_position - secondSphere.m_position).Length();

	//return collision flag based on distance and radii formula  
	return (distance <= (m_radius + secondSphere.m_radius));

}
//------------------------------------------------------------------------------------------------------
//function that calculates radius value of sphere based on scale for collision purposes
//------------------------------------------------------------------------------------------------------
void Sphere2D::Update()
{

	m_radius = m_dimension * m_scale;

}
//------------------------------------------------------------------------------------------------------
//function that renders a sphere 
//------------------------------------------------------------------------------------------------------
void Sphere2D::Draw()
{
	
	//draw bound based on dimension and color set and use a spacing of 1 because
	//the pixel scale value is already integrated when the dimension is set earlier
	TheDebug::Instance()->DrawSphere2D(m_dimension, m_color, 40, 1);

}