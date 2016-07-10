#include <algorithm>
#include "DebugManager.h"
#include "Sphere3D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sphere3D::Sphere3D()
{

	m_scale = 1.0f;
	m_radius = 0.0f;
	m_color.A = 0.4f;
	m_color = Color::GREEN;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns radius of sphere
//------------------------------------------------------------------------------------------------------
float Sphere3D::GetRadius() const
{

	return m_radius;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of sphere
//------------------------------------------------------------------------------------------------------
void Sphere3D::SetScale(float scale)
{

	m_scale = scale;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension of sphere
//------------------------------------------------------------------------------------------------------
void Sphere3D::SetDimension(float dimension)
{

	m_dimension = dimension;

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a OBB object
//------------------------------------------------------------------------------------------------------
bool Sphere3D::IsColliding(const OBB3D& secondBox) const
{

	//make use of OBB's box-sphere collision function
	return (secondBox.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a AABB object
//------------------------------------------------------------------------------------------------------
bool Sphere3D::IsColliding(const AABB3D& secondBox) const
{

	//make use of AABB's box-sphere collision function
	return (secondBox.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a line segment
//------------------------------------------------------------------------------------------------------
bool Sphere3D::IsColliding(const Line3D& secondLine) const
{

	//make use of Line3D's line-sphere collision function
	return (secondLine.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a plane
//------------------------------------------------------------------------------------------------------
bool Sphere3D::IsColliding(const Plane3D& secondPlane) const
{

	//make use of Plane3D's plane-sphere collision function
	return (secondPlane.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Sphere3D::IsColliding(const Sphere3D& secondSphere) const
{

	//first calculate distance between both spheres and store that temporarily
	//we have to temporarily remove the constness to make the formula below work
	float distance = (m_position - secondSphere.m_position).Length();

	//return collision flag based on distance and radii formula  
	return (distance <= (m_radius + secondSphere.m_radius));

}
//------------------------------------------------------------------------------------------------------
//function that calculates radius value of sphere based on scale for collision purposes
//------------------------------------------------------------------------------------------------------
void Sphere3D::Update()
{

	m_radius = m_dimension * m_scale;

}
//------------------------------------------------------------------------------------------------------
//function that renders a sphere 
//------------------------------------------------------------------------------------------------------
void Sphere3D::Draw()
{

	//draw bound based on dimension and color set 
	TheDebug::Instance()->DrawSphere3D(m_dimension, m_color);

}