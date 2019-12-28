#include <algorithm>
#include "Debug.h"
#include "Sphere.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sphere::Sphere()
{

	m_scale = 1.0f;
	m_radius = 1.0f;
	m_radiusScaled = 1.0f;
	m_position = glm::vec3(0.0f);
	m_color = glm::vec4(0.0f, 1.0f, 0.0f, 0.4f);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns radius of sphere
//------------------------------------------------------------------------------------------------------
float Sphere::GetRadius() const
{

	return m_radius;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns scaled radius of sphere
//------------------------------------------------------------------------------------------------------
float Sphere::GetRadiusScaled() const
{

	return m_radiusScaled;

}

const glm::vec3& Sphere::GetPosition() const
{
	
	return m_position;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of sphere
//------------------------------------------------------------------------------------------------------
void Sphere::SetScale(float scale)
{

	m_scale = scale;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns radius of sphere
//------------------------------------------------------------------------------------------------------
void Sphere::SetRadius(float radius)
{

	m_radius = radius;

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with a AABB object
//------------------------------------------------------------------------------------------------------
bool Sphere::IsColliding(const AABB& secondBox) const
{

	//make use of AABB's box-sphere collision function
	return (secondBox.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Sphere::IsColliding(const Sphere& secondSphere) const
{

	//first calculate distance between both spheres and store that temporarily
	//we have to temporarily remove the constness to make the formula below work
	float distance = glm::length(m_position - secondSphere.m_position);

	//return collision flag based on distance and radii formula  
	return (distance <= (m_radius + secondSphere.m_radius));

}
//------------------------------------------------------------------------------------------------------
//function that calculates radius value of sphere based on scale for collision purposes
//------------------------------------------------------------------------------------------------------
void Sphere::Update()
{

	m_radiusScaled = m_radius * m_scale;

}
//------------------------------------------------------------------------------------------------------
//function that renders a sphere 
//------------------------------------------------------------------------------------------------------
void Sphere::Draw()
{

	//draw bound based on dimension and color set 
	//TheDebug::Instance()->DrawSphere(m_dimension, m_color.r, m_color.g, m_color.b, m_color.a);

}