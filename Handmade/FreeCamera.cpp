#include <gtc\matrix_transform.hpp>
#include "FreeCamera.h"
#include "Input.h"
#include "Shader.h"

//======================================================================================================
FreeCamera::FreeCamera()
{
	m_isFlying = true;
	m_isZooming = false;
	m_sensitivity = 0.0f;
}
//======================================================================================================
void FreeCamera::IsFlying(bool isFlying)
{
	m_isFlying = isFlying;
}
//======================================================================================================
void FreeCamera::IsZooming(bool isZooming)
{
	m_isZooming = isZooming;
}
//======================================================================================================
void FreeCamera::SetSensitivity(GLfloat sensitivity)
{
	m_sensitivity = sensitivity;
}
//======================================================================================================
void FreeCamera::Update()
{
	//get keyboard and mouse data from input manager
	//KeyState keys = Input::Instance()->GetKeyStates();
	int keyDown = Input::Instance()->GetKeyDown();
	glm::ivec2 mouseWheel = Input::Instance()->GetMouseWheel();
	glm::ivec2 mouseMotion = Input::Instance()->GetMouseMotion();

	//store pitch and yaw rotation values based on sensitivity
	//we set the yaw to an initial 90 degrees so that the
	//forward vector calculation below results in (0, 0, -1)
	static GLfloat yaw = -90.0f;
	static GLfloat pitch = 0.0f;

	yaw += mouseMotion.x * m_sensitivity;
	pitch += -mouseMotion.y * m_sensitivity;
	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	//use basic trig to calculate the x, y and z components of the forward vector
	//when the camera moves around the y-axis (yaw) the vector changes along the x/z plane
	//the x-axis (pitch) movements only affect the y component of the forward vector 
	glm::vec3 forward;
	forward.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	forward.y = glm::sin(glm::radians(pitch));
	forward.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

	//if WASDQE keys are pressed then move the camera in the correct direction
	//we make use of the forward vector to move in the forward/backward direction
	//the cross product of forward/up create a left/right direction of movement
	//when flying about, a new temporary 'up' vector is calculated to move it

	if (keyDown == HM_KEY_W)
	{
		m_position += forward * m_velocity;
	}

	else if (keyDown == HM_KEY_S)
	{
		m_position -= forward * m_velocity;
	}

	else if (keyDown == HM_KEY_A)
	{
		m_position -= glm::normalize(glm::cross(forward, m_up)) * m_velocity;
	}

	else if (keyDown == HM_KEY_D)
	{
		m_position += glm::normalize(glm::cross(forward, m_up)) * m_velocity;
	}

	else if (keyDown == HM_KEY_Q && m_isFlying)
	{
		glm::vec3 right = glm::cross(forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(forward, right));
		m_position -= up * m_velocity;
	}

	else if (keyDown == HM_KEY_E && m_isFlying)
	{
		glm::vec3 right = glm::cross(forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(forward, right));
		m_position += up * m_velocity;
	}

	//if the camera is not free-flying then 
	//clamp the y position to the ground
	if (!m_isFlying)
	{
		m_position.y = 1.0f;
	}

	//TODO - Fix the camera so that if not in 'fly' mode the camera still moves correctly====================
	//if camera is in debug/fly mode, transform the forward vector based on
	//the overall rotation, so that camera moves forward in any direction
	//m_forward = m_lookAt;

	//otherwise ignore the y component so that the forward vector stays on a horizontal plane
	//when moving. This prevents the camera from moving forward freely and will restrict it. 
	//The camera still looks anywhere but moves with restrictions
	/*if (!m_isFlying)
	{
		m_forward.y = 0.0f;
	}*/
	//======================================================================================================
	
	//if mouse wheel was moved, apply values to FOV to zoom in/out
	//also make sure that the FOV stays between its min/max value
	if (m_isZooming && mouseWheel != glm::ivec2(0))
	{
		m_fieldOfView += -mouseWheel.y;
		m_fieldOfView = glm::clamp(m_fieldOfView, MIN_FOV, MAX_FOV);
		CreatePerspView();
	}

	//update camera's view matrix
	m_viewMatrix = glm::lookAt(m_position, m_position + forward, m_up);
}
//======================================================================================================
// OLD code that makes use of rotation matrices - not ideal but good for learning

//void FreeCamera::RotateMatrix()
//{
//	//create rotation matrices for x/y rotation
//	//we always start with fresh new matrices
//	m_rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(m_yaw), glm::vec3(0.0f, -1.0f, 0.0f));
//	m_rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(m_pitch), glm::vec3(-1.0f, 0.0f, 0.0f));
//
//	//create a total rotation transformation based on x and y rotations
//	//we do a y rotation FIRST and then a local x rotation thereafter
//	glm::mat4 totalRotation = m_rotationMatrixY * m_rotationMatrixX;
//
//	//calculate the FreeCamera's viewing vector by transforming the 
//	//initial viewing target based on FreeCamera's total rotation
//	m_lookAt = glm::vec3(totalRotation * glm::vec4(m_target, 1.0f));
//
//	//if camera is in debug/fly mode, transform the forward vector based on
//	//the overall rotation, so that camera moves forward in any direction
//	if (m_isFlying)
//	{
//		m_forward = m_lookAt;
//	}
//
//	//otherwise transform the forward vector based on ONLY the y-rotations as
//	//this prevents the camera from moving forward freely and will restrict it to
//	//a certain y-axis. The camera still looks anywhere but moves with restrictions
//	else
//	{
//		m_forward = glm::vec3(m_rotationMatrixY * glm::vec4(m_target, 1.0f));
//	}
//
//	//calculate the new right vector based on the forward vector
//	//so that camera can move local left/right based on rotation
//	m_right = glm::normalize(glm::cross(m_forward, m_up));
//}