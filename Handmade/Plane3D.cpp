#include "DebugManager.h"
#include "Plane3D.h"
#include "Sphere3D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Plane3D::Plane3D()
{

	m_size = 500.0f;
	m_sideOfPlane = 0.0f;
	m_distanceFromOrigin = 0.0f;

	m_color.A = 0.4f;
	m_color = Color::BLUE;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns size of plane (for visual purposes only!)
//------------------------------------------------------------------------------------------------------
void Plane3D::SetSize(float size)
{

	m_size = size;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns rotation of plane
//------------------------------------------------------------------------------------------------------
void Plane3D::SetRotation(Quaternion rotation)
{

	m_rotation = rotation;

}
//------------------------------------------------------------------------------------------------------
//function that checks if plane collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Plane3D::IsColliding(const Sphere3D& secondSphere) const
{

	//calculate distance the sphere is from the plane by using 
	//a dot product formula and the plane's distance from the origin
	float distanceFromPlane = m_normal.DotProduct(secondSphere.GetPosition()) - m_distanceFromOrigin;

	//return flag based on if plane intersects with sphere
	return (abs(distanceFromPlane) <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines what side of plane the position passed is on
//------------------------------------------------------------------------------------------------------
Plane3D::PlaneSide Plane3D::SideOfPlane(float positionX, float positionY, float positionZ) const
{

	//create a position vector out of the position X, Y and Z values passed
	Vector3D<float> tempPosition(positionX, positionY, positionZ);

	//calculate distance the passed position is from the plane by using 
	//a dot product formula and the plane's distance from the origin
	float distanceFromPlane = m_normal.DotProduct(tempPosition) - m_distanceFromOrigin;

	//return enum flag based on if distance value is positive, negative or 0
	return (distanceFromPlane > 0.0f ? POSITIVE_SIDE :
		   (distanceFromPlane < 0.0f ? NEGATIVE_SIDE : ON_PLANE));

}
//------------------------------------------------------------------------------------------------------
//function that calculates plane normal and distance from origin for collision purposes
//------------------------------------------------------------------------------------------------------
void Plane3D::Update()
{

	//use the right and forward vectors to calculate the plane surface
	Vector3D<float> rightAxis = Vector3D<float>::RIGHT;
	Vector3D<float> forwardAxis = Vector3D<float>::FORWARD;

	//transform the right and forward vectors based on how plane is rotated
	rightAxis = m_rotation.GetMatrix() * rightAxis;
	forwardAxis = m_rotation.GetMatrix() * forwardAxis;

	//calculate plane's normal by creating a vector perpedicular to plane's right and forward vectors
	//the right and forward vectors are essentially the boundary vectors of the flat plane surface 
	m_normal = rightAxis.CrossProduct(forwardAxis);

	//calculate distance the plane is from the origin by using 
	//a dot product formula and the plane's normal and position
	m_distanceFromOrigin = m_normal.DotProduct(m_position);

}
//------------------------------------------------------------------------------------------------------
//function that renders a plane
//------------------------------------------------------------------------------------------------------
void Plane3D::Draw()
{

	//draw large cube with no height based on size and color set to create a flat surface
	//the cube transforms based on translation and rotation set in client code!!
	TheDebug::Instance()->DrawCube3D(m_size, 0.001f, m_size, m_color);

}