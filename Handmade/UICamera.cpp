#include <gtc\matrix_transform.hpp>
#include "Shader.h"
#include "UICamera.h"

//======================================================================================================
void UICamera::Update(int deltaTime)
{
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
}