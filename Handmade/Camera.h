#pragma once

/*===================================================================#
| 'Camera' source files last updated on 26 July 2021                 |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "Object.h"

const GLfloat MIN_FOV = 1.0f;
const GLfloat MAX_FOV = 100.0f;
const GLfloat NEAR_CLIP = 0.1f;
const GLfloat FAR_CLIP = 1000.0f;

class Camera : public Object
{

public:

	enum class Origin2D
	{
		TopLeft,
		BottomLeft
	};

	Camera();
	virtual ~Camera() = 0 {}

	void SetVelocity(GLfloat velocity);
	void SetFieldOfView(GLfloat fieldOfView);

	void CreatePerspView();
	void CreateOrthoView(Origin2D origin = Origin2D::BottomLeft);

	glm::vec2 ConvertWorldToScreen(const glm::vec3& worldPosition);
	glm::vec3 ConvertScreenToWorld(const glm::vec2& screenPosition, GLfloat zNDC);

	void Reset();

	virtual void Render(Shader& shader) = 0;
	virtual void Update(GLfloat deltaTime) = 0;
	virtual void SendToShader(Shader& shader);

protected:

	GLfloat m_velocity;
	GLfloat m_fieldOfView;

	glm::vec3 m_up;
	glm::vec3 m_forward;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

};