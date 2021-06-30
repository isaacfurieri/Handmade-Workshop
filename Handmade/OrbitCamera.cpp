#include <gtc\matrix_transform.hpp>
#include "Input.h"
#include "OrbitCamera.h"
#include "Shader.h"

//======================================================================================================
OrbitCamera::OrbitCamera()
{
	m_azimuth = 0.0f;
	m_elevation = 0.0f;
	m_sensitivity = 0.0f;
	m_zoomDistance = 5.0f;
}
//======================================================================================================
void OrbitCamera::SetSensitivity(GLfloat sensitivity)
{
	m_sensitivity = sensitivity;
}
//======================================================================================================
void OrbitCamera::Update()
{
	glm::ivec2 mouseWheel = Input::Instance()->GetMouseWheel();
	glm::ivec2 mouseMotion = Input::Instance()->GetMouseMotion();

	if (Input::Instance()->IsLeftButtonDown())
	{
		m_azimuth += mouseMotion.x * m_sensitivity;
		m_elevation += mouseMotion.y * m_sensitivity;
		m_elevation = glm::clamp(m_elevation, -89.9f, 89.9f);
	}

	m_zoomDistance -= mouseWheel.y;
	m_zoomDistance = glm::clamp(m_zoomDistance, 0.5f, 50.0f);

	m_position.x = glm::cos(glm::radians(m_azimuth)) * glm::cos(glm::radians(m_elevation)) * m_zoomDistance;
	m_position.y = glm::sin(glm::radians(m_elevation)) * m_zoomDistance;
	m_position.z = glm::sin(glm::radians(m_azimuth)) * glm::cos(glm::radians(m_elevation)) * m_zoomDistance;

	m_viewMatrix = glm::lookAt(m_position, glm::vec3(0.0f), m_up);
}