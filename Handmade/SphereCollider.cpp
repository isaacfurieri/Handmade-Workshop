#include <algorithm>
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
void SphereCollider::SetScale(GLfloat scale)
{
	m_scale = scale;
}
//======================================================================================================
void SphereCollider::SetRadius(GLfloat radius)
{
	m_radius = radius;
}
//======================================================================================================
void SphereCollider::SetPosition(const glm::vec3& position)
{
	m_position = position;
}
//======================================================================================================
void SphereCollider::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
//======================================================================================================
bool SphereCollider::IsColliding(const BoxCollider& secondBox) const
{
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