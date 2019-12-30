#include <gtc\matrix_transform.hpp>
#include "Camera.h"
#include "Game.h"
#include "Shader.h"
#include "Screen.h"

glm::vec3 Camera::s_position = glm::vec3(0.0f);
glm::mat4 Camera::s_viewMatrix = glm::mat4(1.0f);

//------------------------------------------------------------------------------------------------------
//static setter function that resets view matrix to the identity 
//------------------------------------------------------------------------------------------------------
void Camera::SetIdentity()
{

	s_viewMatrix = glm::mat4(1.0f);

}
//------------------------------------------------------------------------------------------------------
//static function that sends all camera's main properties to shaders
//------------------------------------------------------------------------------------------------------
void Camera::SendToShader()
{

	//send view matrix data to the vertex shader
	Shader::Instance()->SendUniformData("viewMatrix", s_viewMatrix);

	//send camera position to fragment shader
	Shader::Instance()->SendUniformData("cameraPosition", s_position);

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns position reference variable for camera 
//------------------------------------------------------------------------------------------------------
glm::vec3& Camera::Position()
{

	return s_position;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Camera::Camera()
{

	m_isFreeFlow = false;
	
	m_velocity = 0.07f;
	m_sensitivity = 1.0f;

	m_moveDirection = glm::vec3(0.0f);
	m_viewDirection = glm::vec3(0.0f);

	m_threshold = glm::vec2(-0.90f, 0.90f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_lookAt = glm::vec3(0.0f, 0.0f, -1.0f);

	m_rotationMatrixX = glm::mat4(1.0f);
	m_rotationMatrixY = glm::mat4(1.0f);

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns free flow movement flag reference variable for camera 
//------------------------------------------------------------------------------------------------------
bool& Camera::IsFreeFlow()
{

	return m_isFreeFlow;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns speed of camera
//------------------------------------------------------------------------------------------------------
void Camera::SetVelocity(GLfloat velocity)
{

	m_velocity = velocity;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns camera rotation sensitivity
//------------------------------------------------------------------------------------------------------
void Camera::SetSensitivity(GLfloat sensitivity)
{

	m_sensitivity = sensitivity;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns camera's min and max Y threshold value
//------------------------------------------------------------------------------------------------------
void Camera::SetThreshold(GLfloat min, GLfloat max)
{

	m_threshold = glm::vec2(min, max);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns initial viewing direction of camera
//------------------------------------------------------------------------------------------------------
void Camera::SetLookAt(GLfloat x, GLfloat y, GLfloat z)
{

	m_lookAt = glm::vec3(x, y, z);

}
//------------------------------------------------------------------------------------------------------
//function that updates and assigns camera "look at" direction and position
//------------------------------------------------------------------------------------------------------
void Camera::Update()
{

	//set camera to initially look forward in the negative Z-axis 
	//this view will be transformed by the camera's rotation below
	m_lookAt = glm::vec3(0.0f, 0.0f, -1.0f);

	//create a total rotation transformation based on X and Y rotations
	//we do a Y rotation FIRST and then a local X rotation thereafter
	glm::mat4 totalRotation = m_rotationMatrixY * m_rotationMatrixX;

	//calculate the camera's view direction vector by transforming 
	//the initial viewing target based on camera's total rotation
	m_lookAt = glm::vec3(totalRotation * glm::vec4(m_lookAt, 1.0f));

	//create a separate move rotation based on if camera is in freeflow mode or not
	//this affects movement so that camera either moves freely or is bound to a Y plane 
	glm::mat4 moveRotation = (m_isFreeFlow) ? totalRotation : m_rotationMatrixY;

	//apply same rotation to move direction vector so that
	//the camera moves correctly based on camera orientation
	m_moveDirection = glm::vec3(moveRotation * glm::vec4(m_moveDirection, 1.0f));

	//if the camera is set to move, calculate its position using the chosen rotation, 
	//the direction the camera is moving in, the speed at which its moving and time
	if (m_moveDirection != glm::vec3(0.0f))
	{

		s_position += m_moveDirection * m_velocity *
			          ((float)Game::Instance()->GetElapsedTime() / 1000);
	}

	//update camera's view matrix
	s_viewMatrix = glm::lookAt(s_position, s_position + m_lookAt, m_upVector);

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
	GLfloat angle = motionY * m_sensitivity;

	//calculate the dot product between the "look at" vector and the up vector. This will
	//give us a value to determine how far up or down the X axis the camera is tilting
	double dot = glm::dot(m_lookAt, m_upVector);

	//if the camera is tilting upwards or downwards and only if it is between its allowed 
	//threshold, then accumulate the current X axis rotation using the angle calculated
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
	GLfloat angle = motionX * m_sensitivity;

	//accumulate the current Y axis rotation using the angle calculated
	m_rotationMatrixY = glm::rotate(m_rotationMatrixY,
						glm::radians(angle),
						glm::vec3(0.0f, -1.0f, 0.0f));

}