#pragma once

/*===================================================================#
| 'Camera' source files last updated on 25 May 2021                  |
#===================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "GameObject.h"

//TODO - Refine class such that it follows newer design

class Camera : public GameObject
{

public:

	enum class Origin2D
	{
		TOP_LEFT,
		BOTTOM_LEFT
	};

	Camera();
	virtual ~Camera() = 0 {}

	void SetVelocity(GLfloat velocity);
	void SetFieldOfView(GLfloat fieldOfView);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetOrthoView(Origin2D origin = Origin2D::BOTTOM_LEFT);
	void SetPerspView(GLfloat nearClip = 0.1f, GLfloat farClip = 1000.0f);

	virtual void Draw();

protected:

	GLfloat m_velocity;
	GLfloat m_fieldOfView;

	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_forward;
	glm::vec3 m_position;
	glm::vec3 m_direction;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projMatrix;

};