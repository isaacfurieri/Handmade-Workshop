#include "Plane.h"

//======================================================================================================
Plane::Plane()
{
	m_normal = glm::vec3(0.0f);
	m_distanceFromOrigin = 0.0f;
	m_position = glm::vec3(0.0f);
	m_color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
//======================================================================================================
void Plane::SetPoint1(const glm::vec3& point1)
{
	SetPoint1(point1.x, point1.y, point1.z);
}
//======================================================================================================
void Plane::SetPoint1(GLfloat x, GLfloat y, GLfloat z)
{
	m_planePoints.point1.x = x;
	m_planePoints.point1.y = y;
	m_planePoints.point1.z = z;
}
//======================================================================================================
void Plane::SetPoint2(const glm::vec3& point2)
{
	SetPoint2(point2.x, point2.y, point2.z);
}
//======================================================================================================
void Plane::SetPoint2(GLfloat x, GLfloat y, GLfloat z)
{
	m_planePoints.point2.x = x;
	m_planePoints.point2.y = y;
	m_planePoints.point2.z = z;
}
//======================================================================================================
void Plane::SetPoint3(const glm::vec3& point3)
{
	SetPoint3(point3.x, point3.y, point3.z);
}
//======================================================================================================
void Plane::SetPoint3(GLfloat x, GLfloat y, GLfloat z)
{
	m_planePoints.point3.x = x;
	m_planePoints.point3.y = y;
	m_planePoints.point3.z = z;
}
//======================================================================================================
void Plane::SetPoint4(const glm::vec3& point4)
{
	SetPoint4(point4.x, point4.y, point4.z);
}
//======================================================================================================
void Plane::SetPoint4(GLfloat x, GLfloat y, GLfloat z)
{
	m_planePoints.point4.x = x;
	m_planePoints.point4.y = y;
	m_planePoints.point4.z = z;
}
//======================================================================================================
void Plane::SetPosition(const glm::vec3& position)
{
	m_position = position;
}
//======================================================================================================
void Plane::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
//======================================================================================================
bool Plane::IsColliding(const SphereCollider& secondSphere) const
{
	return (abs(DistanceFromPlane(secondSphere.GetPosition())) <= secondSphere.GetRadius());
}
//======================================================================================================
Plane::PlaneSide Plane::SideOfPlane(const glm::vec3& point) const
{
	return SideOfPlane(point.x, point.y, point.z);
}
//======================================================================================================
Plane::PlaneSide Plane::SideOfPlane(GLfloat x, GLfloat y, GLfloat z) const
{
	auto distanceFromPlane = DistanceFromPlane(x, y, z);

	if (distanceFromPlane < 0.0f)
	{
		return PlaneSide::Negative;
	}

	if (distanceFromPlane > 0.0f)
	{
		return PlaneSide::Positive;
	}

	return PlaneSide::OnPlane;
}
//======================================================================================================
GLfloat Plane::DistanceFromPlane(const LineSegment& lineSegment) const
{
	//TODO - Complete this
	//If the line seg intersects the plane, the dist is zero. 
	//Else, it's the minimum of the two endpoint distances
	return 0.0f;
}
//======================================================================================================
GLfloat Plane::DistanceFromPlane(const glm::vec3& point) const
{
	return DistanceFromPlane(point.x, point.y, point.z);
}
//======================================================================================================
GLfloat Plane::DistanceFromPlane(GLfloat x, GLfloat y, GLfloat z) const
{
	return glm::dot(m_normal, glm::vec3(x, y, z)) - m_distanceFromOrigin;
}
//======================================================================================================
void Plane::Update()
{
	glm::vec3 edge1 = m_planePoints.point1 - m_planePoints.point2;
	glm::vec3 edge2 = m_planePoints.point3 - m_planePoints.point2;

	m_normal = glm::normalize(glm::cross(edge1, edge2));
	m_distanceFromOrigin = glm::dot(m_normal, m_planePoints.point1);
}