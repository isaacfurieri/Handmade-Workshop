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

	m_scale = 1;
	m_color.A = 0.4f;
	m_color = Color::RED;
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns scale of AABB
//------------------------------------------------------------------------------------------------------
Vector3D<float> AABB3D::GetScale() const
{

	return m_scale;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns dimension of AABB
//------------------------------------------------------------------------------------------------------
Vector3D<float> AABB3D::GetDimension() const
{

	return m_dimension;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of AABB
//------------------------------------------------------------------------------------------------------
void AABB3D::SetScale(float x, float y, float z)
{

	m_scale.X = x;
	m_scale.Y = y;
	m_scale.Z = z;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of AABB
//------------------------------------------------------------------------------------------------------
void AABB3D::SetDimension(float width, float height, float depth)
{

	m_dimension.X = width;
	m_dimension.Y = height;
	m_dimension.Z = depth;

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

	return ((m_max.X > secondBox.m_min.X && secondBox.m_max.X > m_min.X) &&
		    (m_max.Y > secondBox.m_min.Y && secondBox.m_max.Y > m_min.Y) &&
		    (m_max.Z > secondBox.m_min.Z && secondBox.m_max.Z > m_min.Z));

}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with a sphere object
//------------------------------------------------------------------------------------------------------
bool AABB3D::IsColliding(const Sphere3D& secondSphere) const
{

	Vector3D<float> distanceFromBox;

	//calculate the distance the sphere and point on box edge are apart from each other
	//this makes use of inner function that calculates the point on box edge closest to sphere 
	distanceFromBox = secondSphere.GetPosition() - PointOnBox(secondSphere.GetPosition().X,
		                                                      secondSphere.GetPosition().Y, 
															  secondSphere.GetPosition().Z);

	//return flag based on if box intersects with sphere
	return (distanceFromBox.Length() <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines point on box edge that is closest to position passed 
//------------------------------------------------------------------------------------------------------
Vector3D<float> AABB3D::PointOnBox(float positionX, float positionY, float positionZ) const
{

	Vector3D<float> clampValue;
	Vector3D<float> distanceFromSphere;
	Vector3D<float> tempPosition(positionX, positionY);

	//first calculate distance between the box and position passed
	distanceFromSphere = m_position - tempPosition;

	//calculate the clamp value based on the distance vector 
	//and the half dimension of the box using a min/max formula  
	clampValue.X = std::max(-m_halfDimension.X, std::min(m_halfDimension.X, (distanceFromSphere.X)));
	clampValue.Y = std::max(-m_halfDimension.Y, std::min(m_halfDimension.Y, (distanceFromSphere.Y)));
	clampValue.Z = std::max(-m_halfDimension.Z, std::min(m_halfDimension.Z, (distanceFromSphere.Z)));

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
	m_halfDimension = m_dimension * m_scale / 2;

	//calculate min and max X, Y and Z values based on 
	//bound's centre position and its half dimension
	m_min.X = m_position.X - m_halfDimension.X;
	m_min.Y = m_position.Y - m_halfDimension.Y;
	m_min.Z = m_position.Z - m_halfDimension.Z;
	m_max.X = m_position.X + m_halfDimension.X;
	m_max.Y = m_position.Y + m_halfDimension.Y;
	m_max.Z = m_position.Z + m_halfDimension.Z;

}
//------------------------------------------------------------------------------------------------------
//function that renders a AABB box 
//------------------------------------------------------------------------------------------------------
void AABB3D::Draw()
{

	//draw bound based on dimension and color set 
	TheDebug::Instance()->DrawCube3D(m_dimension.X, m_dimension.Y, m_dimension.Z, m_color);

}