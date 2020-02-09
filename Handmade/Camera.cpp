#include <gtc\matrix_transform.hpp>
#include "Camera.h"
#include "Input.h"
#include "Screen.h"
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Camera::Camera()
{

	m_velocity = 0.9f;
	m_fieldOfView = 45.0f;

	m_viewMatrix = glm::mat4(1.0f);
	m_projMatrix = glm::mat4(1.0f);

	m_position = glm::vec3(0.0f);
	m_direction = glm::vec3(0.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns speed of camera
//------------------------------------------------------------------------------------------------------
void Camera::SetVelocity(GLfloat velocity)
{

	m_velocity = velocity;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns FOV of camera
//------------------------------------------------------------------------------------------------------
void Camera::SetFieldOfView(GLfloat fieldOfView)
{

	m_fieldOfView = fieldOfView;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns position of camera
//------------------------------------------------------------------------------------------------------
void Camera::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{

	m_position = glm::vec3(x, y, z);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 2D orthographic projection 
//------------------------------------------------------------------------------------------------------
void Camera::SetOrthoView(Origin2D origin)
{

	//disable Z-buffering because in
	//2D the depth buffer isn't needed 
	glDisable(GL_DEPTH_TEST);

	//first get screen resolution for calculating projection below
	glm::ivec2 resolution; 
	Screen::Instance()->GetResolution(resolution.x, resolution.y);

	//if screen origin passed is set as top left of screen 
	//create orthographic view so that Y is positive downward 
	if (origin == TOP_LEFT)
	{
		m_projMatrix = glm::ortho(0.0f, (float)resolution.x, 
			                            (float)resolution.y, 0.0f);
	}

	//if screen origin passed is set as bottom left of screen 
	//create orthographic view so that Y is positive upward 
	else if (origin == BOTTOM_LEFT)
	{
		m_projMatrix = glm::ortho(0.0f, (float)resolution.x, 
			                      0.0f, (float)resolution.y);
	}

	//send projection matrix data to shader
	Shader::Instance()->SendUniformData("projection", m_projMatrix);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 3D perspective projection 
//------------------------------------------------------------------------------------------------------
void Camera::SetPerspView(GLfloat nearClip, GLfloat farClip)
{

	//enable Z-buffering so that vertices
	//are rendered in the correct order
	glEnable(GL_DEPTH_TEST);

	//first get screen resolution for calculating projection below
	glm::ivec2 resolution;
	Screen::Instance()->GetResolution(resolution.x, resolution.y);

	//determine the aspect ratio based on width and height of screen
	float aspectRatio = (float)resolution.x / (float)resolution.y;

	//create a 3D perspective projection using FOV angle, aspect ratio and clipping planes
	m_projMatrix = glm::perspective(glm::radians(m_fieldOfView), aspectRatio, nearClip, farClip);

	//send projection matrix data to shader
	Shader::Instance()->SendUniformData("projection", m_projMatrix);

}

void Camera::Draw()
{

	//send camera's view matrix data to the vertex shader
	Shader::Instance()->SendUniformData("view", m_viewMatrix);

}