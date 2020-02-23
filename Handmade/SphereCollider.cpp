#include <algorithm>
#include "Debug.h"
#include "SphereCollider.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
SphereCollider::SphereCollider()
{

	m_scale = 1.0f;
	m_radius = 1.0f;
	m_radiusScaled = 1.0f;
	m_position = glm::vec3(0.0f);
	m_color = glm::vec4(0.0f, 1.0f, 0.0f, 0.4f);

}

float SphereCollider::GetScale() const
{
	return m_scale;
}
//------------------------------------------------------------------------------------------------------
//getter function that returns radius of SphereCollider
//------------------------------------------------------------------------------------------------------
float SphereCollider::GetRadius() const
{

	return m_radius;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns scaled radius of SphereCollider
//------------------------------------------------------------------------------------------------------
float SphereCollider::GetRadiusScaled() const
{

	return m_radiusScaled;

}

const glm::vec3& SphereCollider::GetPosition() const
{
	
	return m_position;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of SphereCollider
//------------------------------------------------------------------------------------------------------
void SphereCollider::SetScale(float scale)
{

	m_scale = scale;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns radius of SphereCollider
//------------------------------------------------------------------------------------------------------
void SphereCollider::SetRadius(float radius)
{

	m_radius = radius;

}

void SphereCollider::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

//------------------------------------------------------------------------------------------------------
//function that checks if SphereCollider collides with a AABB object
//------------------------------------------------------------------------------------------------------
bool SphereCollider::IsColliding(const BoxCollider& secondBox) const
{

	//make use of AABB's box-SphereCollider collision function
	return (secondBox.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if SphereCollider collides with another SphereCollider object
//------------------------------------------------------------------------------------------------------
bool SphereCollider::IsColliding(const SphereCollider& secondSphere) const
{

	//first calculate distance between both SphereColliders and store that temporarily
	//we have to temporarily remove the constness to make the formula below work
	float distance = glm::length(m_position - secondSphere.m_position);

	//return collision flag based on distance and radii formula  
	return (distance <= (m_radius + secondSphere.m_radius));

}
//------------------------------------------------------------------------------------------------------
//function that calculates radius value of SphereCollider based on scale for collision purposes
//------------------------------------------------------------------------------------------------------
void SphereCollider::Update()
{

	m_radiusScaled = m_radius * m_scale;

}
//------------------------------------------------------------------------------------------------------
//function that renders a SphereCollider 
//------------------------------------------------------------------------------------------------------
void SphereCollider::Draw()
{

	//draw bound based on dimension and color set 
	//TheDebug::Instance()->DrawSphereCollider(m_dimension, m_color.r, m_color.g, m_color.b, m_color.a);

}