#include "DebugManager.h"
#include "Plane2D.h"
#include "Sphere2D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Plane2D::Plane2D()
{

	m_sideOfPlane = 0.0f;
	m_distanceFromOrigin = 0.0f;

	m_color.A = 0.4f;
	m_color = Color::BLUE;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns rotation of plane
//------------------------------------------------------------------------------------------------------
void Plane2D::SetRotation(glm::mat4& rotation)
{

	m_rotation = rotation;

}
//------------------------------------------------------------------------------------------------------
//function that checks if plane collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Plane2D::IsColliding(const Sphere2D& secondSphere) const
{

	//calculate distance the sphere is from the plane by using 
	//a dot product formula and the plane's distance from the origin
	float distanceFromPlane = 
	glm::dot(m_normal, glm::vec2(secondSphere.GetPosition())) - m_distanceFromOrigin;

	//return flag based on if plane intersects with sphere
	return (abs(distanceFromPlane) <= secondSphere.GetRadius());

}
//------------------------------------------------------------------------------------------------------
//function that determines what side of plane the position passed is on
//------------------------------------------------------------------------------------------------------
Plane2D::PlaneSide Plane2D::SideOfPlane(float positionX, float positionY) const
{

	//create a position vector out of the position X and Y values passed
	glm::vec2 tempPosition(positionX, positionY);

	//calculate distance the passed position is from the plane by using 
	//a dot product formula and the plane's distance from the origin
	float distanceFromPlane = glm::dot(m_normal, (tempPosition - m_distanceFromOrigin));

	//return enum flag based on if distance value is positive, negative or 0
	return (distanceFromPlane > 0.0f ? POSITIVE_SIDE : 
		   (distanceFromPlane < 0.0f ? NEGATIVE_SIDE : ON_PLANE));

}
//------------------------------------------------------------------------------------------------------
//function that calculates plane normal and distance from origin for collision purposes
//------------------------------------------------------------------------------------------------------
void Plane2D::Update()
{

	//convert plane's position to a 2D object so that the calculations below will work
	glm::vec2 position = glm::vec2(m_position);

	//use the right vector to calculate the two plane points
	glm::vec2 rightAxis = glm::vec2(1.0f, 0.0f);

	//transform the right vector based on how plane is rotated
	rightAxis = glm::vec3(m_rotation * glm::vec4(rightAxis, 0.0f, 1.0f));

	//calculate plane's two points based on centre position and the rotated right axis
	//and multiply thousandfold for rendering purposes later to visualise an infinite plane
	m_point_1 = position - rightAxis * 10000.0f;
	m_point_2 = position + rightAxis * 10000.0f;

	//calculate plane's normal by creating a vector perpedicular to plane vector
	m_normal.x = -rightAxis.y;
	m_normal.y = rightAxis.x;

	//calculate distance the plane is from the origin by using 
	//a dot product formula and the plane's normal and position
	m_distanceFromOrigin = glm::dot(m_normal, position);

}
//------------------------------------------------------------------------------------------------------
//function that renders a plane
//------------------------------------------------------------------------------------------------------
void Plane2D::Draw()
{

	//draw line based on plane points and color set and use a spacing of 1 because 
	//the pixel scale value is already integrated when the plane points are set earlier
	//the plane points already have translation, rotation and scale considered!! 
	TheDebug::Instance()->DrawLine(m_point_1.x, m_point_1.y, 0,
		                           m_point_2.x, m_point_2.y, 0, 4, m_color, 1);

}