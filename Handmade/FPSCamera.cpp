#include <gtc\matrix_transform.hpp>
#include "FPSCamera.h"
#include "Game.h"
#include "Input.h"
#include "Shader.h"
#include "Screen.h"

#include "Debug.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
FPSCamera::FPSCamera()
{

	m_isFlying = true;
	
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_sensitivity = 1.0f;

	m_lookAt = glm::vec3(0.0f, 0.0f, -1.0f);
	m_target = glm::vec3(0.0f, 0.0f, -1.0f);

	m_rotationMatrixX = glm::mat4(1.0f);
	m_rotationMatrixY = glm::mat4(1.0f);

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns free flow movement flag reference variable for FPSCamera 
//------------------------------------------------------------------------------------------------------
bool FPSCamera::IsFlying()
{
	return m_isFlying;
}

void FPSCamera::IsFlying(bool isFlying)
{
	m_isFlying = isFlying;
}
//------------------------------------------------------------------------------------------------------
//setter function that assigns FPSCamera rotation sensitivity
//------------------------------------------------------------------------------------------------------
void FPSCamera::SetSensitivity(GLfloat sensitivity)
{

	m_sensitivity = sensitivity;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns initial viewing direction of FPSCamera
//------------------------------------------------------------------------------------------------------
void FPSCamera::SetTarget(GLfloat x, GLfloat y, GLfloat z)
{

	m_target = glm::vec3(x, y, z);
	m_target = glm::normalize(m_target - m_position);

}
//------------------------------------------------------------------------------------------------------
//function that updates and assigns FPSFPSCamera "look at" direction and position
//------------------------------------------------------------------------------------------------------
void FPSCamera::Update(int deltaTime)
{

	glm::vec2 mouseWheel = Input::Instance()->GetMouseWheel();
	glm::vec2 mouseMotion = Input::Instance()->GetMouseMotion();

	//generate a rotation angle based on mouse motion and rotation sensitivity
	m_yaw += mouseMotion.x * m_sensitivity;
	m_pitch += mouseMotion.y * m_sensitivity;
	m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

	//use either the sin/cos or the matrix method of rotation
	RotateTrig();
	//RotateMatrix();

	//if WASDQE keys are pressed then move the camera in the correct direction
	//we make use of the forward vector to move in the forward/backward direction
	//the cross product of forward/up create a left/right direction of movement
	//when flying about, a new temporary 'up' vector is calculated to move it

	KeyState keys = Input::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_W])
	{
		m_direction = m_forward;
	}

	else if (keys[SDL_SCANCODE_S])
	{
		m_direction = -m_forward;
	}

	else if (keys[SDL_SCANCODE_A])
	{
		m_direction = -m_right; 
	}

	else if (keys[SDL_SCANCODE_D])
	{
		m_direction = m_right; 
	}

	else if (keys[SDL_SCANCODE_Q] && m_isFlying)
	{
		m_direction = m_up;
	}

	else if (keys[SDL_SCANCODE_E] && m_isFlying)
	{
		m_direction = -m_up;
	}

	else
	{
		m_direction = glm::vec3(0.0f);
	}

	if (keys[SDL_SCANCODE_F])
	{
		m_isFlying = false;
	}

	//if the FPSCamera is set to move, calculate its position using the chosen rotation, 
	//the direction the FPSCamera is moving in, the speed at which its moving and time
	m_position += m_direction * m_velocity * (deltaTime / 1000.0f);
	
	//if mouse wheel was moved, apply values to FOV to zoom in/out
	//also make sure that the FOV stays between 1 and 45 degrees!
	if (mouseWheel != glm::vec2(0.0f))
	{
		m_fieldOfView += -mouseWheel.y;
		m_fieldOfView = glm::clamp(m_fieldOfView, 1.0f, 45.0f);
		SetPerspView();
	}

	//update FPSCamera's view matrix
	m_viewMatrix = glm::lookAt(m_position, m_position + m_lookAt, m_up);

}

void FPSCamera::RotateTrig()
{

	//use basic trig to calculate the x, y and z components of the viewing vector
	//when the camera moves around the y-axis (yaw) the vector changes along the x/z plane
	//the x-axis (pitch) movements only affect the y component of the viewing vector 
	//we always subtract 90 degrees from the yaw so that our initial view is (0, 0, -1) 
	m_lookAt.x = glm::cos(glm::radians(m_yaw - 90.0f)) * glm::cos(glm::radians(-m_pitch));
	m_lookAt.y = glm::sin(glm::radians(-m_pitch));
	m_lookAt.z = glm::sin(glm::radians(m_yaw - 90.0f)) * glm::cos(glm::radians(-m_pitch));

	//if camera is in debug/fly mode, transform the forward vector based on
	//the overall rotation, so that camera moves forward in any direction
	m_forward = m_lookAt;

	//otherwise transform the forward vector based on ONLY the y-rotations as
	//this prevents the camera from moving forward freely and will restrict it to
	//a certain y-axis. The camera still looks anywhere but moves with restrictions
	if (!m_isFlying)
	{
		m_forward.y = 0.0f;
	}

	//calculate the new right vector based on the forward vector
	//so that camera can move local left/right based on rotation
	m_right = glm::normalize(glm::cross(m_forward, m_up));

}

void FPSCamera::RotateMatrix()
{

	//create rotation matrices for x/y rotation
	//we always start with fresh new matrices
	m_rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(m_yaw), glm::vec3(0.0f, -1.0f, 0.0f));
	m_rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(m_pitch), glm::vec3(-1.0f, 0.0f, 0.0f));

	//create a total rotation transformation based on X and Y rotations
	//we do a Y rotation FIRST and then a local X rotation thereafter
	glm::mat4 totalRotation = m_rotationMatrixY * m_rotationMatrixX;

	//calculate the FPSCamera's viewing vector by transforming the 
	//initial viewing target based on FPSCamera's total rotation
	m_lookAt = glm::vec3(totalRotation * glm::vec4(m_target, 1.0f));
	
	//if camera is in debug/fly mode, transform the forward vector based on
	//the overall rotation, so that camera moves forward in any direction
	if (m_isFlying)
	{
		m_forward = m_lookAt;
	}

	//otherwise transform the forward vector based on ONLY the y-rotations as
	//this prevents the camera from moving forward freely and will restrict it to
	//a certain y-axis. The camera still looks anywhere but moves with restrictions
	else
	{
		m_forward = glm::vec3(m_rotationMatrixY * glm::vec4(m_target, 1.0f));
	}

	//calculate the new right vector based on the forward vector
	//so that camera can move local left/right based on rotation
	m_right = glm::normalize(glm::cross(m_forward, m_up));

}