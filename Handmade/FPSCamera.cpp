#include <gtc\matrix_transform.hpp>
#include "FPSCamera.h"
#include "Game.h"
#include "Input.h"
#include "Shader.h"
#include "Screen.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
FPSCamera::FPSCamera()
{

	m_isFlying = false;
	
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

	//send camera's view matrix data to the vertex shader
	Shader::Instance()->SendUniformData("view", m_viewMatrix);

}

void FPSCamera::UseMatrix()
{

	//create rotation matrices for x/y rotation
	m_rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	m_rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));

	//set FPSCamera to initially look forward in the negative Z-axis 
	//this view will be transformed by the FPSCamera's rotation below
	m_lookAt = m_target;

	//create a total rotation transformation based on X and Y rotations
	//we do a Y rotation FIRST and then a local X rotation thereafter
	glm::mat4 totalRotation = m_rotationMatrixY * m_rotationMatrixX;

	//calculate the FPSCamera's view direction vector by transforming 
	//the initial viewing target based on FPSCamera's total rotation
	m_lookAt = glm::vec3(totalRotation * glm::vec4(m_lookAt, 1.0f));

	//create a separate move rotation based on if FPSCamera is in freeflow mode or not
	//this affects movement so that FPSCamera either moves freely or is bound to a Y plane 
	glm::mat4 moveRotation = (m_isFlying) ? totalRotation : m_rotationMatrixY;

	//apply same rotation to move direction vector so that
	//the FPSCamera moves correctly based on FPSCamera orientation
	m_forward = glm::vec3(moveRotation * glm::vec4(m_forward, 1.0f));

	//calculate the right/up vectors based on the forward 
	m_right = glm::normalize(glm::cross(m_forward, m_up));
	m_up = glm::normalize(glm::cross(m_forward, m_right));

}

void FPSCamera::UseSinCos()
{

	//store pitch and yaw rotation values based on sensitivity
	//we set the yaw to an initial 90 degrees so that the
	//forward vector calculation below results in (0, 0, -1)
	//static GLfloat yaw = -90.0f;
	//static GLfloat pitch = 0.0f;

	//use basic trig to calculate the x, y and z components of the forward vector
	//when the camera moves around the y-axis (yaw) the vector changes along the x/z plane
	//the x-axis (pitch) movements only affect the y component of the forward vector 
	m_forward.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	m_forward.y = glm::sin(glm::radians(m_pitch));
	m_forward.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));

	//calculate the right/up vectors based on the forward 
	m_right = glm::normalize(glm::cross(m_forward, m_up));
	m_up = glm::normalize(glm::cross(m_forward, m_right));

}