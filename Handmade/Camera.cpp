#include <assert.h>
#include <gtc\matrix_transform.hpp>
#include "Camera.h"
#include "Screen.h"
#include "Shader.h"

//======================================================================================================
Camera::Camera()
{
	m_velocity = 0.0f;
	m_fieldOfView = 45.0f;
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	
	m_viewport = glm::ivec4(0);
	m_resolution = glm::ivec2(0);
	m_backgroundColor = glm::vec4(0.0f);

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
}
//======================================================================================================
const glm::ivec2 Camera::GetResolution() const
{
	return m_resolution;
}
//======================================================================================================
glm::vec2 Camera::ConvertWorldToScreen(const glm::vec3& worldPosition)
{
	//convert to clip space
	glm::vec4 clipCoordinate = m_projectionMatrix * m_viewMatrix * glm::vec4(worldPosition, 1.0f);

	//convert to NDC
	clipCoordinate /= clipCoordinate.w;

	//convert to screen space
	glm::vec2 resolution = Screen::Instance()->GetResolution();
	return glm::vec2((clipCoordinate.x + 1.0f) * resolution.x * 0.5f,
					 (clipCoordinate.y + 1.0f) * resolution.y * 0.5f);
}
//======================================================================================================
glm::vec3 Camera::ConvertScreenToWorld(const glm::vec2& screenPosition, GLfloat zNDC)
{
	glm::vec2 resolution = Screen::Instance()->GetResolution();

	//convert to NDC
	glm::vec4 NDC((2.0f * screenPosition.x) / resolution.x - 1.0f, 
		          (2.0f * (resolution.y - screenPosition.y)) / resolution.y - 1.0f,
		          zNDC, 1.0f);

	//convert to world space (4D)
	glm::vec4 worldCoordinate = glm::inverse(m_viewMatrix) * glm::inverse(m_projectionMatrix) * NDC;
	
	//convert to world space (3D)
	return (worldCoordinate /= worldCoordinate.w);
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
void Camera::SetBackgroundColor(const glm::vec4& backgroundColor)
{
	m_backgroundColor = backgroundColor;
}
//======================================================================================================
void Camera::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	m_resolution.x = width;
	m_resolution.y = height;
	m_viewport = glm::ivec4(x, y, width, height);
}
//======================================================================================================
void Camera::CreateOrthoView(Origin2D origin)
{
	Screen::Instance()->IsDepthTestEnabled(false);
	Screen::Instance()->SetViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);
	Screen::Instance()->SetColor(m_backgroundColor);
	Screen::Instance()->Refresh();

	if (origin == Origin2D::TopLeft)
	{
		m_projectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(m_resolution.x),
											  static_cast<GLfloat>(m_resolution.y), 0.0f);
	}

	else if (origin == Origin2D::BottomLeft)
	{
		m_projectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(m_resolution.x),
									    0.0f, static_cast<GLfloat>(m_resolution.y));
	}
}
//======================================================================================================
void Camera::CreatePerspView()
{
	Screen::Instance()->IsDepthTestEnabled(true);
	Screen::Instance()->SetViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);
	Screen::Instance()->SetColor(m_backgroundColor);
	Screen::Instance()->Refresh();

	GLfloat aspectRatio = (m_resolution.x) / static_cast<GLfloat>(m_resolution.y);

	m_projectionMatrix = glm::perspective(glm::radians(m_fieldOfView), 
		aspectRatio, NEAR_CLIP, FAR_CLIP);
}
//======================================================================================================
void Camera::Reset()
{
	m_viewMatrix = glm::mat4(1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	m_transform.SetPosition(glm::vec3(0.0f));
}
//======================================================================================================
void Camera::SendToShader(Shader& shader)
{
	shader.SendData("view", m_viewMatrix);
	shader.SendData("projection", m_projectionMatrix);
}