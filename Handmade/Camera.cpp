#include "Camera.h"
#include "ScreenManager.h"
#include "TimeManager.h"
#include "Transform.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Camera::Camera()
{

	m_freeFlow = false;
	m_velocity = 0.0f;
	m_sensitivity = 1.0f;
	
	m_upVector = Vector3D<double>::UP;
	m_lookAtDirection = Vector3D<double>::FORWARD;

	m_threshold.X = -0.90f;
	m_threshold.Y = 0.90f;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns free flow movement flag reference variable for camera 
//------------------------------------------------------------------------------------------------------
bool& Camera::IsFreeFlow()
{

	return m_freeFlow;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns position reference variable for camera 
//------------------------------------------------------------------------------------------------------
Vector3D<double>& Camera::Position()
{

	return m_position;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns "look at" direction vector of camera
//------------------------------------------------------------------------------------------------------
Vector3D<double> Camera::GetLookAtDirection()
{

	return m_lookAtDirection;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns speed of camera
//------------------------------------------------------------------------------------------------------
void Camera::SetVelocity(float velocity)
{

	m_velocity = velocity;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns camera rotation sensitivity
//------------------------------------------------------------------------------------------------------
void Camera::SetSensitivity(float sensitivity)
{

	m_sensitivity = sensitivity;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns camera's min and max Y threshold value
//------------------------------------------------------------------------------------------------------
void Camera::SetThreshold(float min, float max)
{

	m_threshold.X = min;
	m_threshold.Y = max;

}
//------------------------------------------------------------------------------------------------------
//function that updates and assigns camera "look at" direction and position
//------------------------------------------------------------------------------------------------------
void Camera::Update()
{

	//temp rotation for assigning free flow or non-freeflow camera below
	Quaternion tempRotation;
	
	//set camera to initially look forward in the negative Z-axis 
	//this view will be transformed by the camera's rotation below
	m_lookAtDirection = Vector3D<double>::FORWARD;

	//based on if camera is in freeflow or non-freeflow mode, set temp rotation to be used below
	((m_freeFlow) ? tempRotation = m_totalRotation : tempRotation = m_totalRotationY);

	//calculate the camera's "look at" vector by transfroming it based on camera's rotation
	//this essentially multiplies the total camera rotation by the forward vector 
	m_lookAtDirection = m_totalRotation.Conjugate() * m_lookAtDirection;

	//if the camera is set to move, calculate its position using the chosen quaternion rotation, 
	//the direction the camera is moving in, the speed at which its moving and time
	//the quaternion rotation's conjugate is used because we use inverse rotations for the camera, 
	//because the camera's view of the world and the world itself are opposed 
	if (m_moveDirection != Vector3D<double>::ZERO)
	{
		m_position += tempRotation.Conjugate() * m_moveDirection * m_velocity *
			          TheTime::Instance()->GetElapsedTimeSeconds();
	}

}
//------------------------------------------------------------------------------------------------------
//function that applies camera position and rotation to the global modelview matrix
//------------------------------------------------------------------------------------------------------
void Camera::Draw()
{

	//translation variable to move the world into position
	Transform translation;

	//multiply modelview matrix by camera's total rotation quaternion
	//here we apply the normal quaternion rotations to the world
	TheScreen::Instance()->ModelViewMatrix() * m_totalRotation.GetMatrix();
	
	//move the world in the opposite direction because the world "moves around the camera"
	translation.Translate((float)-m_position.X, (float)-m_position.Y, (float)-m_position.Z);

	//apply translation transformation to modelview matrix
	TheScreen::Instance()->ModelViewMatrix() * translation.GetMatrix();
	
}
//------------------------------------------------------------------------------------------------------
//function that stops camera from moving
//------------------------------------------------------------------------------------------------------
void Camera::Stop()
{

	m_moveDirection = Vector3D<double>::ZERO;

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go UP
//------------------------------------------------------------------------------------------------------
void Camera::MoveUp()
{

	m_moveDirection = Vector3D<double>::UP;

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go DOWN
//------------------------------------------------------------------------------------------------------
void Camera::MoveDown()
{

	m_moveDirection = Vector3D<double>::DOWN;

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go LEFT
//------------------------------------------------------------------------------------------------------
void Camera::MoveLeft()
{

	m_moveDirection = Vector3D<double>::LEFT;

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go RIGHT
//------------------------------------------------------------------------------------------------------
void Camera::MoveRight()
{

	m_moveDirection = Vector3D<double>::RIGHT;

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go FORWARD
//------------------------------------------------------------------------------------------------------
void Camera::MoveForward()
{

	m_moveDirection = Vector3D<double>::FORWARD;

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go BACKWARD
//------------------------------------------------------------------------------------------------------
void Camera::MoveBackward()
{

	m_moveDirection = Vector3D<double>::BACKWARD;

}
//------------------------------------------------------------------------------------------------------
//function that controls rotation of camera around global Y axis
//------------------------------------------------------------------------------------------------------
void Camera::RotateY(short motionX)
{

	//generate a rotation angle based on mouse motion and rotation sensitivity
	float angle = motionX * m_sensitivity;
	
	//create a temporary Y axis rotation using the angle calculated 
	Quaternion tempRotation(angle, 0.0f, 1.0f, 0.0f);

	//multiply the temporary rotation by the total rotation
	//multiplying the quaternions in this order ensures global Y axis rotation
	m_totalRotation = m_totalRotation * tempRotation;

	//store a rotation that adds Y axis rotations only
	//this will help with forward / backward / up / down movement in a non-free flowing camera
	//it doesn't matter which order of multiplication is used since only the Y axis is needed	
	m_totalRotationY = m_totalRotationY * tempRotation;

}
//------------------------------------------------------------------------------------------------------
//function that controls rotation of camera around local X axis
//------------------------------------------------------------------------------------------------------
void Camera::RotateX(short motionY)
{

	//generate a rotation angle based on mouse motion and rotation sensitivity
	float angle = motionY * m_sensitivity;

	//calculate the dot product between the "look at" vector and the up vector. This will give 
	//us a value to determine how far up or down the X axis the camera is tilting
	double dot = m_lookAtDirection.DotProduct(m_upVector);

	//if the camera is tilting upwards or downwards and only if it is between its allowed 
	//threshold, then create a temporary X axis rotation using the angle calculated and 
	//multiply the total rotation by the temporary rotation to ensure local X axis rotation
	if ((motionY > 0 && dot >= m_threshold.X) || (motionY < 0 && dot <= m_threshold.Y))
	{

		Quaternion tempRotation(angle, 1.0f, 0.0f, 0.0f);
		m_totalRotation = tempRotation * m_totalRotation;

	}
	
}