#include <algorithm>
#include "BoxCollider.h"
#include "OBBCollider.h"
#include "SphereCollider.h"

//======================================================================================================
BoxCollider::BoxCollider()
{
	m_min = glm::vec3(0.0f);
	m_max = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f);
	m_dimension = glm::vec3(1.0f);
	m_halfDimension = glm::vec3(0.5f);
	m_color = glm::vec4(1.0f, 0.0f, 0.0f, 0.4f);
}
//======================================================================================================
const glm::vec3& BoxCollider::GetScale() const
{
	return m_scale;
}
//======================================================================================================
const glm::vec3& BoxCollider::GetPosition() const
{
	return m_position;
}
//======================================================================================================
const glm::vec3& BoxCollider::GetDimension() const
{
	return m_dimension;
}
//======================================================================================================
void BoxCollider::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
}
//======================================================================================================--
void BoxCollider::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}
//======================================================================================================
void BoxCollider::SetPosition(const glm::vec3& position)
{
	m_position = position;
}
//======================================================================================================
void BoxCollider::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
//======================================================================================================
void BoxCollider::SetDimension(const glm::vec3& dimension)
{
	m_dimension = dimension;
}
//======================================================================================================
void BoxCollider::SetDimension(GLfloat width, GLfloat height, GLfloat depth)
{
	m_dimension.x = width;
	m_dimension.y = height;
	m_dimension.z = depth;
}
//======================================================================================================
bool BoxCollider::IsColliding(const glm::vec3& point) const
{
	return IsColliding(point.x, point.y, point.z);
}
//======================================================================================================
bool BoxCollider::IsColliding(GLfloat x, GLfloat y, GLfloat z) const
{
	return ((x >= m_min.x && x <= m_max.x) &&
		(y >= m_min.y && y <= m_max.y) &&
		(z >= m_min.z && z <= m_max.z));
}
//======================================================================================================
bool BoxCollider::IsColliding(const OBBCollider& secondBox) const
{
	return secondBox.IsColliding(*this);
}
//======================================================================================================
bool BoxCollider::IsColliding(const BoxCollider& secondBox) const
{
	return ((m_max.x > secondBox.m_min.x && secondBox.m_max.x > m_min.x) &&
		(m_max.y > secondBox.m_min.y && secondBox.m_max.y > m_min.y) &&
		(m_max.z > secondBox.m_min.z && secondBox.m_max.z > m_min.z));
}
//======================================================================================================
bool BoxCollider::IsColliding(const SphereCollider& secondSphere) const
{
	return (glm::length(secondSphere.GetPosition() - PointOnBox(secondSphere.GetPosition())) <=
		secondSphere.GetRadius());
}
//======================================================================================================
glm::vec3 BoxCollider::PointOnBox(const glm::vec3& point) const
{
	return PointOnBox(point.x, point.y, point.z);
}
//======================================================================================================
glm::vec3 BoxCollider::PointOnBox(GLfloat x, GLfloat y, GLfloat z) const
{
	return m_position -
		glm::clamp((m_position - glm::vec3(x, y, z)), -m_halfDimension, m_halfDimension);
}
//======================================================================================================
void BoxCollider::Update()
{
	m_halfDimension = m_dimension * m_scale * 0.5f;

	m_min.x = m_position.x - m_halfDimension.x;
	m_min.y = m_position.y - m_halfDimension.y;
	m_min.z = m_position.z - m_halfDimension.z;
	m_max.x = m_position.x + m_halfDimension.x;
	m_max.y = m_position.y + m_halfDimension.y;
	m_max.z = m_position.z + m_halfDimension.z;
}