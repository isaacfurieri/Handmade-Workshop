#include <algorithm>
#include "AABB3D.h"
#include "DebugManager.h"
#include "OBB3D.h"
#include "Sphere3D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
AABB3D::AABB3D()
{

	m_scale = glm::vec3(1.0f);
	m_color.A = 0.4f;
	m_color = Color::RED;
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns scale of AABB
//------------------------------------------------------------------------------------------------------
glm::vec3 AABB3D::GetScale() const
{

	return m_scale;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns dimension of AABB
//------------------------------------------------------------------------------------------------------
glm::vec3 AABB3D::GetDimension() const
{

	return m_dimension;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of AABB
//------------------------------------------------------------------------------------------------------
void AABB3D::SetScale(float x, float y, float z)
{

	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of AABB
//------------------------------------------------------------------------------------------------------
void AABB3D::SetDimension(float width, float height, float depth)
{

	m_dimension.x = width;
	m_dimension.y = height;
	m_dimension.z = depth;

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with a OBB object
//------------------------------------------------------------------------------------------------------
bool AABB3D::IsColliding(const OBB3D& secondBox) const
{

	//make use of OBB's box-box collision function
	return (secondBox.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with another AABB object
//------------------------------------------------------------------------------------------------------
bool AABB3D::IsColliding(const AABB3D& secondBox) const
{

	return ((m_max.x > secondBox.m_min.x && secondBox.m_max.x > m_min.x) &&
		    (m_max.y > secondBox.m_min.y && secondBox.m_max.y > m_min.y) &&
		    (m_max.z > secondBox.m_min.z && secondBox.m_max.z > m_min.z));

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with a sphere object
//------------------------------------------------------------------------------------------------------
bool AABB3D::IsColliding(const Sphere3D& secondSphere) const
{

	glm::vec3 distanceFromBox;

	//calculate the distance the sphere and point on box edge are apart from each other
	//this makes use of inner function that calculates the point on box edge closest to sphere 
	distanceFromBox = secondSphere.GetPosition() - PointOnBox(secondSphere.GetPosition().x,
		                                                      secondSphere.GetPosition().y, 
															  secondSphere.GetPosition().z);

	//return flag based on if box intersects with sphere
	return (glm::length(distanceFromBox) <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines point on box edge that is closest to position passed 
//------------------------------------------------------------------------------------------------------
glm::vec3 AABB3D::PointOnBox(float positionX, float positionY, float positionZ) const
{

	glm::vec3 clampValue;
	glm::vec3 distanceFromSphere;
	glm::vec3 tempPosition(positionX, positionY, positionZ);

	//first calculate distance between the box and position passed
	distanceFromSphere = m_position - tempPosition;

	//calculate the clamp value based on the distance vector 
	//and the half dimension of the box using a min/max formula  
	clampValue.x = std::max(-m_halfDimension.x, std::min(m_halfDimension.x, (distanceFromSphere.x)));
	clampValue.y = std::max(-m_halfDimension.y, std::min(m_halfDimension.y, (distanceFromSphere.y)));
	clampValue.z = std::max(-m_halfDimension.z, std::min(m_halfDimension.z, (distanceFromSphere.z)));

	//the clamp value is used to determine the exact point on the 
	//edge of the box that lines up with the passed position point
	return m_position - clampValue;

}
//------------------------------------------------------------------------------------------------------
//function that calculates min and max values of AABB for collision purposes
//------------------------------------------------------------------------------------------------------
void AABB3D::Update()
{

	//first determine the half width, height and depth based on scale value  
	m_halfDimension = m_dimension * m_scale / 2.0f;

	//calculate min and max X, Y and Z values based on 
	//bound's centre position and its half dimension
	m_min.x = m_position.x - m_halfDimension.x;
	m_min.y = m_position.y - m_halfDimension.y;
	m_min.z = m_position.z - m_halfDimension.z;
	m_max.x = m_position.x + m_halfDimension.x;
	m_max.y = m_position.y + m_halfDimension.y;
	m_max.z = m_position.z + m_halfDimension.z;

}
//------------------------------------------------------------------------------------------------------
//function that renders a AABB box 
//------------------------------------------------------------------------------------------------------
void AABB3D::Draw()
{

	//draw bound based on dimension and color set 
	TheDebug::Instance()->DrawCube3D(m_dimension.x, m_dimension.y, m_dimension.z, m_color);

}