#include <gtc\matrix_transform.hpp>
#include "Input.h"
#include "OrbitCamera.h"
#include "Shader.h"

//======================================================================================================
OrbitCamera::OrbitCamera()
{
	m_sensitivity = 0.0f;
	m_zoomDistance = 5.0f;
	m_target = glm::vec3(0.0f);
	m_pitchRange = glm::vec2(-89.0f, 89.0f);
	m_zoomDistanceRange = glm::vec2(0.5f, 50.0f);
}
//======================================================================================================
void OrbitCamera::SetSensitivity(GLfloat sensitivity)
{
	m_sensitivity = sensitivity;
}
//======================================================================================================
void OrbitCamera::SetPitchRange(const glm::vec2& range)
{
	SetPitchRange(range.x, range.y);
}
//======================================================================================================
void OrbitCamera::SetPitchRange(GLfloat min, GLfloat max)
{
	m_pitchRange.x = min;
	m_pitchRange.y = max;
}
//======================================================================================================
void OrbitCamera::SetZoomDistanceRange(GLfloat min, GLfloat max)
{
	m_zoomDistanceRange.x = min;
	m_zoomDistanceRange.y = max;
}
//======================================================================================================
void OrbitCamera::SetZoomDistanceRange(const glm::vec2& range)
{
	SetZoomDistanceRange(range.x, range.y);
}
//======================================================================================================
void OrbitCamera::Zoom(GLint motion)
{
	m_zoomDistance -= motion;
	m_zoomDistance = glm::clamp(m_zoomDistance, m_zoomDistanceRange.x, m_zoomDistanceRange.y);
}
//======================================================================================================
void OrbitCamera::Rotate(const glm::ivec2& motion)
{
	Rotate(motion.x, motion.y);
}
//======================================================================================================
void OrbitCamera::Rotate(GLint motionX, GLint motionY)
{
	auto rotation = m_transform.GetEulerAngles();

	//The y rotation is the azimuth and the x rotation is the elevation
	rotation.y += motionX * m_sensitivity; 
	rotation.x += -motionY * m_sensitivity; 
	rotation.x = glm::clamp(rotation.x, m_pitchRange.x, m_pitchRange.y);

	m_transform.SetRotation(rotation);
}
//======================================================================================================
void OrbitCamera::SendToShader(Shader& shader)
{
	m_viewMatrix = glm::lookAt(m_transform.GetPosition(), m_target, m_up);
	Camera::SendToShader(shader);
}
//======================================================================================================
void OrbitCamera::Update(GLfloat deltaTime)
{
	glm::vec3 position;

	auto rotation = m_transform.GetEulerAngles();
	position.x = glm::cos(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x)) * m_zoomDistance;
	position.y = glm::sin(glm::radians(rotation.x)) * m_zoomDistance;
	position.z = glm::sin(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x)) * m_zoomDistance;

	m_transform.SetPosition(position);
}