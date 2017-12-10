#include <algorithm>
#include "DebugManager.h"
#include "OBB3D.h"
#include "Sphere3D.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
OBB3D::OBB3D()
{

	m_scale = glm::vec3(1.0f);
	m_color = glm::vec4(1.0f, 0.5f, 0.0f, 0.4f);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns rotation of OBB
//------------------------------------------------------------------------------------------------------
void OBB3D::SetRotation(Quaternion rotation)
{

	m_rotation = rotation;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns scale of OBB
//------------------------------------------------------------------------------------------------------
void OBB3D::SetScale(float x, float y, float z)
{

	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of OBB
//------------------------------------------------------------------------------------------------------
void OBB3D::SetDimension(float width, float height, float depth)
{

	m_dimension.x = width;
	m_dimension.y = height;
	m_dimension.z = depth;

}
//------------------------------------------------------------------------------------------------------
//function that checks if OBB collides with another OBB object
//------------------------------------------------------------------------------------------------------
bool OBB3D::IsColliding(const OBB3D& secondBox) const
{

	//create a temporary array of OBBs to send to inner IsColliding() routine
	OBB3D tempBox[2];

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
bool OBB3D::IsColliding(const AABB3D& secondBox) const
{

	//create a temporary array of OBBs to send to inner IsColliding() routine
	OBB3D tempBox[2];

	//assign first temporary box array element 
	tempBox[0] = *this;

	//set properties of second temporary box array element based on passed AABB
	tempBox[1].SetScale(secondBox.GetScale().x, 
		                secondBox.GetScale().y, 
						secondBox.GetScale().z);

	tempBox[1].SetPosition(secondBox.GetPosition().x, 
		                   secondBox.GetPosition().y, 
						   secondBox.GetPosition().z);

	tempBox[1].SetDimension(secondBox.GetDimension().x, 
		                    secondBox.GetDimension().y, 
							secondBox.GetDimension().z);

	//update temporary OBB so that box corners and axes are setup
	tempBox[1].Update();

	//check if OBBs collide using inner IsColliding() routine
	return IsColliding(tempBox);

}
//------------------------------------------------------------------------------------------------------
//function that checks if OBB collides with a sphere object
//------------------------------------------------------------------------------------------------------
bool OBB3D::IsColliding(const Sphere3D& secondSphere) const
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
glm::vec3 OBB3D::PointOnBox(float positionX, float positionY, float positionZ) const
{

	float projectValue;
	float clampValue[3];
	float halfDimension[3];

	glm::vec3 tempAxis[3];
	glm::vec3 normalizedAxis[3];
	glm::vec3 distanceFromSphere;
	glm::vec3 tempPosition(positionX, positionY, positionZ);

	//first determine the half width, height and depth of bound based on scale value 
	//here an array is used instead of a vector for use in the loop below
	halfDimension[0] = m_dimension.x * m_scale.x / 2.0f;
	halfDimension[1] = m_dimension.y * m_scale.y / 2.0f;
	halfDimension[2] = m_dimension.z * m_scale.z / 2.0f;

	//assign the box's right, up and forward axis to the temporary array
	//so that we can make use of them easily in the loop below
	tempAxis[0] = m_rightAxis;
	tempAxis[1] = m_upAxis;
	tempAxis[2] = m_forwardAxis;

	//calculate distance between the box and position passed
	distanceFromSphere = tempPosition - m_position;

	//loop through all three axes 
	for (int i = 0; i < 3; i++)
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
	return m_position + (normalizedAxis[0] * clampValue[0])
					  + (normalizedAxis[1] * clampValue[1])
					  + (normalizedAxis[2] * clampValue[2]);

}
//------------------------------------------------------------------------------------------------------
//function that calculates corners and axes of OBB for collision purposes
//------------------------------------------------------------------------------------------------------
void OBB3D::Update()
{

	//first determine the half width and height of bound based on scale value  
	glm::vec3 halfDimension(m_dimension.x * m_scale.x / 2.0f,
		                    m_dimension.y * m_scale.y / 2.0f,
							m_dimension.z * m_scale.z / 2.0f);

	//use the up, right and forward vector to calculate box's corners 
	//below and to create projection vectors to project onto later on
	m_upAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	m_rightAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forwardAxis = glm::vec3(0.0f, 0.0f, -1.0f);

	//transform the up, right and forward vectors based on how OBB is rotated 
	m_upAxis = glm::vec3(m_rotation.GetMatrix() * glm::vec4(m_upAxis, 1.0f)) * halfDimension.y;
	m_rightAxis = glm::vec3(m_rotation.GetMatrix() * glm::vec4(m_rightAxis, 1.0f)) * halfDimension.x;
	m_forwardAxis = glm::vec3(m_rotation.GetMatrix() * glm::vec4(m_forwardAxis, 1.0f)) * halfDimension.z;

	//calculate all eight corners of box based on bound's centre 
	//position, starting in the top left corner and moving clockwise
	//the front face is calculated first and then the back face
	m_corners[0] = m_position - m_rightAxis + m_upAxis - m_forwardAxis;
	m_corners[1] = m_position + m_rightAxis + m_upAxis - m_forwardAxis;
	m_corners[2] = m_position + m_rightAxis - m_upAxis - m_forwardAxis;
	m_corners[3] = m_position - m_rightAxis - m_upAxis - m_forwardAxis;
	m_corners[4] = m_position - m_rightAxis + m_upAxis + m_forwardAxis;
	m_corners[5] = m_position + m_rightAxis + m_upAxis + m_forwardAxis;
	m_corners[6] = m_position + m_rightAxis - m_upAxis + m_forwardAxis;
	m_corners[7] = m_position - m_rightAxis - m_upAxis + m_forwardAxis;

}
//------------------------------------------------------------------------------------------------------
//function that draws a bounding box on screen
//------------------------------------------------------------------------------------------------------
void OBB3D::Draw()
{

	//draw bound based on dimension and color set
	TheDebug::Instance()->DrawCube3D(m_dimension.x, m_dimension.y, m_dimension.z, 
		                             m_color.r, m_color.g, m_color.b, m_color.a);

}
//------------------------------------------------------------------------------------------------------
//function that checks if two OBB objects collide
//------------------------------------------------------------------------------------------------------
bool OBB3D::IsColliding(const OBB3D* tempBoxes) const
{

	float extentMin[2];
	float extentMax[2];
	float projection = 0.0f;

	glm::vec3 tempAxis[15];
	glm::vec3 normalizedAxis;

	//assign all fifteen temporary axes based on both boxes' up, right and forward axes 
	//these will be the fifteen axes that all sixteen corners are projected onto
	//there are six normal axes and nine cross product axes to represent edge axes
	tempAxis[0] = tempBoxes[0].m_rightAxis;
	tempAxis[1] = tempBoxes[0].m_upAxis;
	tempAxis[2] = tempBoxes[0].m_forwardAxis;

	tempAxis[3] = tempBoxes[1].m_rightAxis;
	tempAxis[4] = tempBoxes[1].m_upAxis;
	tempAxis[5] = tempBoxes[1].m_forwardAxis;

	tempAxis[6] = glm::cross(tempBoxes[0].m_rightAxis, tempBoxes[1].m_rightAxis);
	tempAxis[7] = glm::cross(tempBoxes[0].m_rightAxis, tempBoxes[1].m_upAxis);
	tempAxis[8] = glm::cross(tempBoxes[0].m_rightAxis, tempBoxes[1].m_forwardAxis);

	tempAxis[9] = glm::cross(tempBoxes[0].m_upAxis, tempBoxes[1].m_rightAxis);
	tempAxis[10] = glm::cross(tempBoxes[0].m_upAxis, tempBoxes[1].m_upAxis);
	tempAxis[11] = glm::cross(tempBoxes[0].m_upAxis, tempBoxes[1].m_forwardAxis);

	tempAxis[12] = glm::cross(tempBoxes[0].m_forwardAxis, tempBoxes[1].m_rightAxis);
	tempAxis[13] = glm::cross(tempBoxes[0].m_forwardAxis, tempBoxes[1].m_upAxis);
	tempAxis[14] = glm::cross(tempBoxes[0].m_forwardAxis, tempBoxes[1].m_forwardAxis);

	//loop through all 15 axes 
	for (int i = 0; i < 15; i++)
	{

		//check if one of the axis is 0, as this may result from a 
		//cross product of two vectors pointing in same direction
		//if a zero axis is found skip this loop iteration as its useless
		if (tempAxis[i] == glm::vec3(0.0f)) continue;

		//normalise each axis for projection purposes later
		normalizedAxis = glm::normalize(tempAxis[i]);

		//reset the min and max extent values each time a new axis is tested
		//set both min and max to the first projected corner of each box
		extentMin[0] = extentMax[0] = glm::dot(tempBoxes[0].m_corners[0], normalizedAxis);
		extentMin[1] = extentMax[1] = glm::dot(tempBoxes[1].m_corners[0], normalizedAxis);

		//loop through each box
		for (int j = 0; j < 2; j++)
		{

			//loop through each corner
			for (int k = 0; k < 8; k++)
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