#include <algorithm>
#include "AABB2D.h"
#include "DebugManager.h"
#include "OBB2D.h"
#include "Sphere2D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
AABB2D::AABB2D()
{

	m_scale = glm::vec2(1.0f);
	m_color.A = 0.4f;
	m_color = Color::RED;
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns scale of AABB
//------------------------------------------------------------------------------------------------------
glm::vec2 AABB2D::GetScale() const
{

	return m_scale; 

}
//------------------------------------------------------------------------------------------------------
//getter function that returns dimension of AABB
//------------------------------------------------------------------------------------------------------
glm::vec2 AABB2D::GetDimension() const
{ 
	
	return m_dimension; 

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of AABB
//------------------------------------------------------------------------------------------------------
void AABB2D::SetScale(float x, float y)
{

	m_scale.x = x;
	m_scale.y = y;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of AABB
//------------------------------------------------------------------------------------------------------
void AABB2D::SetDimension(float width, float height)
{

	m_dimension.x = width;
	m_dimension.y = height;

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with a OBB object
//------------------------------------------------------------------------------------------------------
bool AABB2D::IsColliding(const OBB2D& secondBox) const
{

	//make use of OBB's box-box collision function
	return (secondBox.IsColliding(*this));

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with another AABB object
//------------------------------------------------------------------------------------------------------
bool AABB2D::IsColliding(const AABB2D& secondBox) const
{

	return ((m_max.x > secondBox.m_min.x && secondBox.m_max.x > m_min.x) &&
		    (m_max.y > secondBox.m_min.y && secondBox.m_max.y > m_min.y));

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with a sphere object
//------------------------------------------------------------------------------------------------------
bool AABB2D::IsColliding(const Sphere2D& secondSphere) const
{

	glm::vec2 distanceFromBox;

	//calculate the distance the sphere and point on box edge are apart from each other
	//this makes use of inner function that calculates the point on box edge closest to sphere 
	distanceFromBox = glm::vec2(secondSphere.GetPosition()) - PointOnBox(secondSphere.GetPosition().x, 
					                                                     secondSphere.GetPosition().y);

	//return flag based on if box intersects with sphere
	return (glm::length(distanceFromBox) <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines point on box edge that is closest to position passed 
//------------------------------------------------------------------------------------------------------
glm::vec2 AABB2D::PointOnBox(float positionX, float positionY) const
{

	glm::vec2 clampValue;
	glm::vec2 distanceFromSphere;
	glm::vec2 tempPosition(positionX, positionY);

	//first calculate distance between the box and position passed
	distanceFromSphere = glm::vec2(m_position) - tempPosition;

	//calculate the clamp value based on the distance vector 
	//and the half dimension of the box using a min/max formula  
	clampValue.x = std::max(-m_halfDimension.x, std::min(m_halfDimension.x, (distanceFromSphere.x)));
	clampValue.y = std::max(-m_halfDimension.y, std::min(m_halfDimension.y, (distanceFromSphere.y)));

	//the clamp value is used to determine the exact point on the 
	//edge of the box that lines up with the passed position point
	return glm::vec2(m_position) - clampValue;

}
//------------------------------------------------------------------------------------------------------
//function that calculates min and max values of AABB for collision purposes
//------------------------------------------------------------------------------------------------------
void AABB2D::Update()
{

	//first determine the half width and height of bound based on scale value  
	m_halfDimension = m_dimension * m_scale / 2.0f;
	
	//calculate min and max X and Y values based on 
	//bound's centre position and its half dimension
	m_min.x = m_position.x - m_halfDimension.x;
	m_min.y = m_position.y - m_halfDimension.y;
	m_max.x = m_position.x + m_halfDimension.x;
	m_max.y = m_position.y + m_halfDimension.y;

}
//------------------------------------------------------------------------------------------------------
//function that renders a AABB box 
//------------------------------------------------------------------------------------------------------
void AABB2D::Draw()
{

	//draw bound based on dimension and color set and use a spacing of 1 because
	//the pixel scale value is already integrated when the dimension is set earlier
	TheDebug::Instance()->DrawCube2D(m_dimension.x, m_dimension.y, m_color, 1);

}