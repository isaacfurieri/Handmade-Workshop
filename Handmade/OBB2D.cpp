#include <algorithm>
#include "DebugManager.h"
#include "OBB2D.h"
#include "Sphere2D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
OBB2D::OBB2D()
{

	m_scale = glm::vec2(1.0f);
	m_color = glm::vec4(1.0f, 0.5f, 0.0f, 0.4f);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of OBB
//------------------------------------------------------------------------------------------------------
void OBB2D::SetScale(float x, float y)
{

	m_scale.x = x;
	m_scale.y = y;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns rotation of OBB
//------------------------------------------------------------------------------------------------------
void OBB2D::SetRotation(glm::mat4& rotation)
{

	m_rotation = rotation;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of OBB
//------------------------------------------------------------------------------------------------------
void OBB2D::SetDimension(float width, float height)
{

	m_dimension.x = width;
	m_dimension.y = height;

}
//------------------------------------------------------------------------------------------------------
//function that checks if OBB collides with another OBB object
//------------------------------------------------------------------------------------------------------
bool OBB2D::IsColliding(const OBB2D& secondBox) const
{

	//create a temporary array of OBBs to send to inner IsColliding() routine
	OBB2D tempBox[2];
	
	//assign both temporary box array elements 
	//to this calling object and the passed object
	tempBox[0] = *this;
	tempBox[1] = secondBox;

	//check if OBBs collide using inner IsColliding() routine
	return IsColliding(tempBox);
	
}
//------------------------------------------------------------------------------------------------------
//function that checks if OBB collides with a AABB object
//------------------------------------------------------------------------------------------------------
bool OBB2D::IsColliding(const AABB2D& secondBox) const
{

	//create a temporary array of OBBs to send to inner IsColliding() routine
	OBB2D tempBox[2];

	//assign first temporary box array element 
	tempBox[0] = *this;
	
	//set properties of second temporary box array element based on passed AABB
	tempBox[1].SetScale(secondBox.GetScale().x, secondBox.GetScale().y);
	tempBox[1].SetPosition(secondBox.GetPosition().x, secondBox.GetPosition().y);
	tempBox[1].SetDimension(secondBox.GetDimension().x, secondBox.GetDimension().y);

	//update temporary OBB so that box corners and axes are setup
	tempBox[1].Update();

	//check if OBBs collide using inner IsColliding() routine
	return IsColliding(tempBox);
	
}
//------------------------------------------------------------------------------------------------------
//function that checks if OBB collides with a sphere object
//------------------------------------------------------------------------------------------------------
bool OBB2D::IsColliding(const Sphere2D& secondSphere) const
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
glm::vec2 OBB2D::PointOnBox(float positionX, float positionY) const
{

	float projectValue;
	float clampValue[2];
	float halfDimension[2];

	glm::vec2 tempAxis[2];
	glm::vec2 normalizedAxis[2];
	glm::vec2 distanceFromSphere;
	glm::vec2 tempPosition(positionX, positionY);

	//first determine the half width and height of bound based on scale value 
	//here an array is used instead of a vector for use in the loop below
	halfDimension[0] = m_dimension.x * m_scale.x / 2.0f;
	halfDimension[1] = m_dimension.y * m_scale.y / 2.0f;

	//assign the box's right and up axis to the temporary array
	//so that we can make use of them easily in the loop below
	tempAxis[0] = m_rightAxis;
	tempAxis[1] = m_upAxis;

	//calculate distance between the box and position passed
	distanceFromSphere = tempPosition - glm::vec2(m_position);

	//loop through both axes 
	for (int i = 0; i < 2; i++)
	{

		//normalise each axis for projection purposes later
		normalizedAxis[i] = glm::normalize(tempAxis[i]);

		//project distance vector onto current axis
		projectValue = glm::dot(distanceFromSphere, normalizedAxis[i]);

		//calculate the clamp value based on the projected value 
		//and the half dimension of the box using a min/max formula 
		clampValue[i] = std::max(-halfDimension[i], std::min(halfDimension[i], projectValue));

	}

	//the clamp values are used together with the axes to determine the exact
	//point on the edge of the box that lines up with the passed position point
	return glm::vec2(m_position) + (normalizedAxis[0] * clampValue[0]) 
		                         + (normalizedAxis[1] * clampValue[1]);

}
//------------------------------------------------------------------------------------------------------
//function that calculates corners and axes of OBB for collision purposes
//------------------------------------------------------------------------------------------------------
void OBB2D::Update()
{

	//convert box's position to a 2D object so that the corner calculations below will work
	glm::vec2 position = glm::vec2(m_position);

	//first determine the half width and height of bound based on scale value  
	glm::vec2 halfDimension(m_dimension.x * m_scale.x / 2.0f,
		                    m_dimension.y * m_scale.y / 2.0f);

	//use the up and right vector to calculate box's corners below
	//and to create projection vectors to project onto later on
	m_upAxis = glm::vec2(0.0f, 1.0f);
	m_rightAxis = glm::vec2(1.0f, 0.0f);

	//transform the up and right vectors based on how OBB is rotated 
	m_upAxis = glm::vec2(m_rotation * glm::vec4(m_upAxis, 0.0f, 1.0f)) * halfDimension.y;
	m_rightAxis = glm::vec2(m_rotation * glm::vec4(m_rightAxis, 0.0f, 1.0f)) * halfDimension.x;

	//calculate all four corners of box based on bound's centre 
	//position, starting in the top left corner and moving clockwise
	m_corners[0] = position - m_rightAxis + m_upAxis;
	m_corners[1] = position + m_rightAxis + m_upAxis;
	m_corners[2] = position + m_rightAxis - m_upAxis;
	m_corners[3] = position - m_rightAxis - m_upAxis;

}
//------------------------------------------------------------------------------------------------------
//function that draws a bounding box on screen
//------------------------------------------------------------------------------------------------------
void OBB2D::Draw()
{

	//draw bound based on dimension and color set and use a spacing of 1 because
	//the pixel scale value is already integrated when the dimension is set earlier
	TheDebug::Instance()->DrawCube2D(m_dimension.x, m_dimension.y, 
		                             m_color.r, m_color.g, m_color.b, m_color.a);

}
//------------------------------------------------------------------------------------------------------
//function that checks if two OBB objects collide
//------------------------------------------------------------------------------------------------------
bool OBB2D::IsColliding(const OBB2D* tempBoxes) const
{

	float extentMin[2];
	float extentMax[2];
	float projection = 0.0f;
	
	glm::vec2 tempAxis[4];
	glm::vec2 normalizedAxis;
	
	//assign all four temporary axes based on both boxes' up and right axes 
	//these will be the four axes that all eight corners are projected onto
	tempAxis[0] = tempBoxes[0].m_rightAxis;
	tempAxis[1] = tempBoxes[0].m_upAxis;
	tempAxis[2] = tempBoxes[1].m_rightAxis;
	tempAxis[3] = tempBoxes[1].m_upAxis;

	//loop through all four axes 
	for(int i = 0; i < 4; i++)
	{

		//normalise each axis for projection purposes later
		normalizedAxis = glm::normalize(tempAxis[i]);

		//reset the min and max extent values each time a new axis is tested
		//set both min and max to the first projected corner of each box
		extentMin[0] = extentMax[0] = glm::dot(tempBoxes[0].m_corners[0], normalizedAxis);
		extentMin[1] = extentMax[1] = glm::dot(tempBoxes[1].m_corners[0], normalizedAxis);
		
		//loop through each box
		for(int j = 0; j < 2; j++)
		{

			//loop through each corner
			for(int k = 0; k < 4; k++)
			{
			
				//project each box's corner onto the current active axis
				projection = glm::dot(tempBoxes[j].m_corners[k], normalizedAxis);
				
				//find the min and max extent values for each box
				extentMin[j] = std::min(projection, extentMin[j]); 
				extentMax[j] = std::max(projection, extentMax[j]); 
					
			} 

		}

		//if there is at least 1 extent non-overlap found
		//boxes do not collide, so return false immediately
		if (!(extentMax[0] > extentMin[1] && extentMax[1] > extentMin[0]))
		{
			return false;
		}

	}

	//otherwise there are extent overlaps for each axis
	//that means both boxes collide, so return true
	return true;

}