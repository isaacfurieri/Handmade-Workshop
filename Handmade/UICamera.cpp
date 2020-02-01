#include <gtc\matrix_transform.hpp>
#include "Shader.h"
#include "UICamera.h"

//------------------------------------------------------------------------------------------------------
//function that keeps 2D UI camera standing still and facing forward
//------------------------------------------------------------------------------------------------------
void UICamera::Update(int deltaTime)
{

	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
	Shader::Instance()->SendUniformData("view", m_viewMatrix);

}