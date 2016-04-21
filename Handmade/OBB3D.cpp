#include <algorithm>
#include "DebugManager.h"
#include "OBB3D.h"
#include "ScreenManager.h"
#include "Transform.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
OBB3D::OBB3D()
{

	m_scale = 1;

	m_color.R = 1.0f;
	m_color.G = 0.5f;
	m_color.B = 0.0f;
	m_color.A = 0.4f;

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

	m_scale.X = x;
	m_scale.Y = y;
	m_scale.Z = z;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of OBB
//------------------------------------------------------------------------------------------------------
void OBB3D::SetDimension(float width, float height, float depth)
{

	m_dimension.X = width;
	m_dimension.Y = height;
	m_dimension.Z = depth;

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
	tempBox[1].SetScale(secondBox.GetScale().X, 
		                secondBox.GetScale().Y, 
						secondBox.GetScale().Z);

	tempBox[1].SetPosition(secondBox.GetPosition().X, 
		                   secondBox.GetPosition().Y, 
						   secondBox.GetPosition().Z);

	tempBox[1].SetDimension(secondBox.GetDimension().X, 
		                    secondBox.GetDimension().Y, 
							secondBox.GetDimension().Z);

	//update temporary OBB so that box corners and axes are setup
	tempBox[1].Update();

	//check if OBBs collide using inner IsColliding() routine
	return IsColliding(tempBox);

}
//------------------------------------------------------------------------------------------------------
//function that calculates corners and axes of OBB for collision purposes
//------------------------------------------------------------------------------------------------------
void OBB3D::Update()
{

	//first determine the half width and height of bound based on scale value  
	Vector3D<float> halfDimension(m_dimension.X * m_scale.X / 2.0f,
		                          m_dimension.Y * m_scale.Y / 2.0f,
								  m_dimension.Z * m_scale.Z / 2.0f);

	//use the up, right and forward vector to calculate box's corners 
	//below and to create projection vectors to project onto later on
	m_upAxis = Vector3D<float>::UP;
	m_rightAxis = Vector3D<float>::RIGHT;
	m_forwardAxis = Vector3D<float>::FORWARD;

	//transform the up, right and forward vectors based on how OBB is rotated 
	m_upAxis = m_rotation.GetMatrix() * m_upAxis * halfDimension.Y;
	m_rightAxis = m_rotation.GetMatrix() * m_rightAxis * halfDimension.X;
	m_forwardAxis = m_rotation.GetMatrix() * m_forwardAxis * halfDimension.Z;

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
	TheDebug::Instance()->DrawCube3D(m_dimension.X, m_dimension.Y, m_dimension.Z, m_color);

}
//------------------------------------------------------------------------------------------------------
//function that checks if two OBB objects collide
//------------------------------------------------------------------------------------------------------
bool OBB3D::IsColliding(const OBB3D* tempBoxes) const
{

	float extentMin[2];
	float extentMax[2];
	float projection = 0.0f;

	Vector3D<float> tempAxis[15];
	Vector3D<float> normalizedAxis;

	//assign all fifteen temporary axes based on both boxes' up, right and forward axes 
	//these will be the fifteen axes that all sixteen corners are projected onto
	//there are six normal axes and nine cross product axes to represent edge axes
	tempAxis[0] = tempBoxes[0].m_rightAxis;
	tempAxis[1] = tempBoxes[0].m_upAxis;
	tempAxis[2] = tempBoxes[0].m_forwardAxis;

	tempAxis[3] = tempBoxes[1].m_rightAxis;
	tempAxis[4] = tempBoxes[1].m_upAxis;
	tempAxis[5] = tempBoxes[1].m_forwardAxis;

	tempAxis[6] = tempBoxes[0].m_rightAxis.CrossProduct(tempBoxes[1].m_rightAxis);
	tempAxis[7] = tempBoxes[0].m_rightAxis.CrossProduct(tempBoxes[1].m_upAxis);
	tempAxis[8] = tempBoxes[0].m_rightAxis.CrossProduct(tempBoxes[1].m_forwardAxis);

	tempAxis[9] = tempBoxes[0].m_upAxis.CrossProduct(tempBoxes[1].m_rightAxis);
	tempAxis[10] = tempBoxes[0].m_upAxis.CrossProduct(tempBoxes[1].m_upAxis);
	tempAxis[11] = tempBoxes[0].m_upAxis.CrossProduct(tempBoxes[1].m_forwardAxis);

	tempAxis[12] = tempBoxes[0].m_forwardAxis.CrossProduct(tempBoxes[1].m_rightAxis);
	tempAxis[13] = tempBoxes[0].m_forwardAxis.CrossProduct(tempBoxes[1].m_upAxis);
	tempAxis[14] = tempBoxes[0].m_forwardAxis.CrossProduct(tempBoxes[1].m_forwardAxis);

	//loop through all 15 axes 
	for (int i = 0; i < 15; i++)
	{

		//check if one of the axis is 0, as this may result from a 
		//cross product of two vectors pointing in same direction
		//if a zero axis is found skip this loop iteration as its useless
		if (tempAxis[i] == Vector3D<float>::ZERO) continue;

		//normalise each axis for projection purposes later
		normalizedAxis = tempAxis[i].Normalise();

		//reset the min and max extent values each time a new axis is tested
		//set both min and max to the first projected corner of each box
		extentMin[0] = extentMax[0] = tempBoxes[0].m_corners[0].DotProduct(normalizedAxis);
		extentMin[1] = extentMax[1] = tempBoxes[1].m_corners[0].DotProduct(normalizedAxis);

		//loop through each box
		for (int j = 0; j < 2; j++)
		{

			//loop through each corner
			for (int k = 0; k < 8; k++)
			{

				//project each box's corner onto the current active axis
				projection = tempBoxes[j].m_corners[k].DotProduct(normalizedAxis);

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