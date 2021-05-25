#include <algorithm>
#include "Debug.h"
#include "SphereCollider.h"

//======================================================================================================
SphereCollider::SphereCollider()
{
	m_scale = 1.0f;
	m_radius = 1.0f;
	m_radiusScaled = 1.0f;
	m_position = glm::vec3(0.0f);
	m_color = glm::vec4(0.0f, 1.0f, 0.0f, 0.4f);
}
//======================================================================================================
float SphereCollider::GetScale() const
{
	return m_scale;
}
//======================================================================================================
float SphereCollider::GetRadius() const
{
	return m_radius;
}
//======================================================================================================
float SphereCollider::GetRadiusScaled() const
{
	return m_radiusScaled;
}
//======================================================================================================
const glm::vec3& SphereCollider::GetPosition() const
{
	return m_position;
}
//======================================================================================================
void SphereCollider::SetScale(float scale)
{
	m_scale = scale;
}
//======================================================================================================
void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}
//======================================================================================================
void SphereCollider::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
//======================================================================================================
bool SphereCollider::IsColliding(const BoxCollider& secondBox) const
{
	//make use of AABB's box-SphereCollider collision function
	return (secondBox.IsColliding(*this));
}
//======================================================================================================
bool SphereCollider::IsColliding(const SphereCollider& secondSphere) const
{
	//first calculate distance between both SphereColliders and store that temporarily
	//we have to temporarily remove the constness to make the formula below work
	float distance = glm::length(m_position - secondSphere.m_position);

	//return collision flag based on distance and radii formula  
	return (distance <= (m_radius + secondSphere.m_radius));
}
//======================================================================================================
void SphereCollider::Update()
{
	m_radiusScaled = m_radius * m_scale;
}
//======================================================================================================
void SphereCollider::Draw()
{
	//draw bound based on dimension and color set 
	//TheDebug::Instance()->DrawSphereCollider(m_dimension, m_color.r, m_color.g, m_color.b, m_color.a);
}