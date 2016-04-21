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

	m_scale = 1;
	m_color.A = 0.4f;
	m_color = Color::RED;
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns scale of AABB
//------------------------------------------------------------------------------------------------------
Vector2D<float> AABB2D::GetScale() const
{

	return m_scale; 

}
//------------------------------------------------------------------------------------------------------
//getter function that returns dimension of AABB
//------------------------------------------------------------------------------------------------------
Vector2D<float> AABB2D::GetDimension() const
{ 
	
	return m_dimension; 

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of AABB
//------------------------------------------------------------------------------------------------------
void AABB2D::SetScale(float x, float y)
{

	m_scale.X = x;
	m_scale.Y = y;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of AABB
//------------------------------------------------------------------------------------------------------
void AABB2D::SetDimension(float width, float height)
{

	m_dimension.X = width;
	m_dimension.Y = height;

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

	return ((m_max.X > secondBox.m_min.X && secondBox.m_max.X > m_min.X) &&
		    (m_max.Y > secondBox.m_min.Y && secondBox.m_max.Y > m_min.Y));

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with a sphere object
//------------------------------------------------------------------------------------------------------
bool AABB2D::IsColliding(const Sphere2D& secondSphere) const
{

	Vector2D<float> distanceFromBox;

	//calculate the distance the sphere and point on box edge are apart from each other
	//this makes use of inner function that calculates the point on box edge closest to sphere 
	distanceFromBox = secondSphere.GetPosition().Convert2D() - PointOnBox(secondSphere.GetPosition().X, 
					                                                      secondSphere.GetPosition().Y);

	//return flag based on if box intersects with sphere
	return (distanceFromBox.Length() <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines point on box edge that is closest to position passed 
//------------------------------------------------------------------------------------------------------
Vector2D<float> AABB2D::PointOnBox(float positionX, float positionY) const
{

	Vector2D<float> clampValue;
	Vector2D<float> distanceFromSphere;
	Vector2D<float> tempPosition(positionX, positionY);

	//first calculate distance between the box and position passed
	distanceFromSphere = m_position.Convert2D() - tempPosition;

	//calculate the clamp value based on the distance vector 
	//and the half dimension of the box using a min/max formula  
	clampValue.X = std::max(-m_halfDimension.X, std::min(m_halfDimension.X, (distanceFromSphere.X)));
	clampValue.Y = std::max(-m_halfDimension.Y, std::min(m_halfDimension.Y, (distanceFromSphere.Y)));

	//the clamp value is used to determine the exact point on the 
	//edge of the box that lines up with the passed position point
	return m_position.Convert2D() - clampValue;

}
//------------------------------------------------------------------------------------------------------
//function that calculates min and max values of AABB for collision purposes
//------------------------------------------------------------------------------------------------------
void AABB2D::Update()
{

	//first determine the half width and height of bound based on scale value  
	m_halfDimension = m_dimension * m_scale / 2;
	
	//calculate min and max X and Y values based on 
	//bound's centre position and its half dimension
	m_min.X = m_position.X - m_halfDimension.X;
	m_min.Y = m_position.Y - m_halfDimension.Y;
	m_max.X = m_position.X + m_halfDimension.X;
	m_max.Y = m_position.Y + m_halfDimension.Y;

}
//------------------------------------------------------------------------------------------------------
//function that renders a AABB box 
//------------------------------------------------------------------------------------------------------
void AABB2D::Draw()
{

	//draw bound based on dimension and color set and use a spacing of 1 because
	//the pixel scale value is already integrated when the dimension is set earlier
	TheDebug::Instance()->DrawCube2D(m_dimension.X, m_dimension.Y, m_color, 1);

}