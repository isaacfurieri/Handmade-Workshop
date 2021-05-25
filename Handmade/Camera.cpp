#include <gtc\matrix_transform.hpp>
#include "Camera.h"
#include "Input.h"
#include "Screen.h"
#include "Shader.h"

//======================================================================================================
Camera::Camera()
{
	m_velocity = 5.0f;
	m_fieldOfView = 45.0f;

	m_viewMatrix = glm::mat4(1.0f);
	m_projMatrix = glm::mat4(1.0f);

	m_position = glm::vec3(0.0f);
	m_direction = glm::vec3(0.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
}
//======================================================================================================
void Camera::SetVelocity(GLfloat velocity)
{
	m_velocity = velocity;
}
//======================================================================================================
void Camera::SetFieldOfView(GLfloat fieldOfView)
{
	m_fieldOfView = fieldOfView;
}
//======================================================================================================
void Camera::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position = glm::vec3(x, y, z);
}
//======================================================================================================
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
	if (origin == Origin2D::TOP_LEFT)
	{
		m_projMatrix = glm::ortho(0.0f, (float)resolution.x,
			(float)resolution.y, 0.0f);
	}

	//if screen origin passed is set as bottom left of screen 
	//create orthographic view so that Y is positive upward 
	else if (origin == Origin2D::BOTTOM_LEFT)
	{
		m_projMatrix = glm::ortho(0.0f, (float)resolution.x,
			0.0f, (float)resolution.y);
	}

	//send projection matrix data to shader
	Shader::Instance()->SendUniformData("projection", m_projMatrix);

	//only if the window was resized then reset the viewport for correct display
	if (Input::Instance()->IsWindowResized())
	{
		Screen::Instance()->SetViewport(0, 0, resolution.x, resolution.y);
	}
}
//======================================================================================================
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

	//only if the window was resized then reset the viewport for correct display
	if (Input::Instance()->IsWindowResized())
	{
		Screen::Instance()->SetViewport(0, 0, resolution.x, resolution.y);
	}
}
//======================================================================================================
void Camera::Draw()
{
	//send camera's view matrix data to the vertex shader
	Shader::Instance()->SendUniformData("view", m_viewMatrix);
}