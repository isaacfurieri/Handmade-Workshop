#include <gtc\matrix_transform.hpp>
#include "Camera.h"
#include "Game.h"
#include "ScreenManager.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------
//static member variable initializations
//------------------------------------------------------------------------------------------------------
GLuint Camera::s_viewUniformID = 0;
glm::mat4 Camera::s_viewMatrix;

//------------------------------------------------------------------------------------------------------
//static setter function that resets view matrix to the identity 
//------------------------------------------------------------------------------------------------------
void Camera::SetIdentity()
{

	s_viewMatrix = glm::mat4(1.0f);

}
//------------------------------------------------------------------------------------------------------
//static function that sends camera's view matrix data to the vertex shader
//------------------------------------------------------------------------------------------------------
void Camera::ApplyMatrix()
{

	TheShader::Instance()->SetUniformMatrix(s_viewUniformID, &s_viewMatrix[0][0]);

}
//------------------------------------------------------------------------------------------------------
//static setter function that assigns view matrix's shader uniform ID  
//------------------------------------------------------------------------------------------------------
void Camera::SetViewUniformID(std::string uniformID)
{

	s_viewUniformID = TheShader::Instance()->GetUniformID(uniformID.c_str());

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Camera::Camera()
{

	m_freeFlow = false;
	m_velocity = 0.0f;
	m_sensitivity = 1.0f;

	m_threshold.x = -0.90f;
	m_threshold.y = 0.90f;

	m_lookAt = glm::vec3(0.0f, 0.0f, -1.0f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);

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
glm::vec3& Camera::Position()
{

	return m_position;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns viewing direction vector of camera
//------------------------------------------------------------------------------------------------------
glm::vec3 Camera::GetViewDirection()
{

	return m_viewDirection;

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

	m_threshold.x = min;
	m_threshold.y = max;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns initial viewing direction of camera
//------------------------------------------------------------------------------------------------------
void Camera::SetLookAt(float x, float y, float z)
{

	m_lookAt.x = x;
	m_lookAt.y = y;
	m_lookAt.z = z;

}
//------------------------------------------------------------------------------------------------------
//function that updates and assigns camera "look at" direction and position
//------------------------------------------------------------------------------------------------------
void Camera::Update()
{

	glm::mat4 tempRotation;
	glm::mat4 totalRotation = m_rotationMatrixY * m_rotationMatrixX;
	
	//calculate the camera's view direction vector by transforming 
	//the initial viewing target based on camera's total rotation
	m_viewDirection = glm::vec3(totalRotation * glm::vec4(m_lookAt, 1.0f));

	//based on if camera is in freeflow or non-freeflow mode, set temp rotation to be used below
	//this will either be the total rotation based on X and Y rotations or only the Y rotation
	((m_freeFlow) ? tempRotation = m_rotationMatrixY * m_rotationMatrixX
		          : tempRotation = m_rotationMatrixY);

	//if the camera is set to move, calculate its position using the chosen rotation, 
	//the direction the camera is moving in, the speed at which its moving and time
	if (m_moveDirection != glm::vec3(0.0f))
	{
		
		m_position += glm::vec3(tempRotation * glm::vec4(m_moveDirection, 1.0f)) * m_velocity *
			          (float)TheGame::Instance()->GetElapsedTimeSeconds();
	}

	//update camera's view matrix
	s_viewMatrix = glm::lookAt(m_position, m_position + m_viewDirection, m_upVector);

}
//------------------------------------------------------------------------------------------------------
//function that stops camera from moving
//------------------------------------------------------------------------------------------------------
void Camera::Stop()
{

	m_moveDirection = glm::vec3(0.0f);

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go UP
//------------------------------------------------------------------------------------------------------
void Camera::MoveUp()
{

	m_moveDirection = glm::vec3(0.0f, 1.0f, 0.0f);

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go DOWN
//------------------------------------------------------------------------------------------------------
void Camera::MoveDown()
{

	m_moveDirection = glm::vec3(0.0f, -1.0f, 0.0f);

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go LEFT
//------------------------------------------------------------------------------------------------------
void Camera::MoveLeft()
{

	m_moveDirection = glm::vec3(-1.0f, 0.0f, 0.0f);

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go RIGHT
//------------------------------------------------------------------------------------------------------
void Camera::MoveRight()
{

	m_moveDirection = glm::vec3(1.0f, 0.0f, 0.0f);

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go FORWARD
//------------------------------------------------------------------------------------------------------
void Camera::MoveForward()
{

	m_moveDirection = glm::vec3(0.0f, 0.0f, -1.0f);

}
//------------------------------------------------------------------------------------------------------
//function that assigns camera movement to go BACKWARD
//------------------------------------------------------------------------------------------------------
void Camera::MoveBackward()
{

	m_moveDirection = glm::vec3(0.0f, 0.0f, 1.0f);

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
	double dot = glm::dot(m_viewDirection, m_upVector);

	//if the camera is tilting upwards or downwards and only if it is between its allowed 
	//threshold, accumulate rotation matrix based on rotation created around X axis
	if ((motionY > 0 && dot >= m_threshold.x) || (motionY < 0 && dot <= m_threshold.y))
	{
		m_rotationMatrixX = glm::rotate(m_rotationMatrixX,
						    glm::radians(angle),
							glm::vec3(-1.0f, 0.0f, 0.0f));
	}

}
//------------------------------------------------------------------------------------------------------
//function that controls rotation of camera around global Y axis
//------------------------------------------------------------------------------------------------------
void Camera::RotateY(short motionX)
{

	//generate a rotation angle based on mouse motion and rotation sensitivity
	float angle = motionX * m_sensitivity;

	//accumulate rotation matrix based on rotation created around Y axis
	m_rotationMatrixY = glm::rotate(m_rotationMatrixY,
						glm::radians(angle),
						glm::vec3(0.0f, -1.0f, 0.0f));

}