#pragma once

/*===================================================================#
| 'BoxCollider' source files last updated on 14 July 2021            |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>

//TODO - Add some kind of 'central system' to render all colliders in the scene

class SphereCollider;

class BoxCollider
{

public:

	BoxCollider();

	const glm::vec3& GetScale() const;
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetDimension() const;

	void SetScale(GLfloat x, GLfloat y, GLfloat z);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetDimension(GLfloat width, GLfloat height, GLfloat depth);

	bool IsColliding(const BoxCollider& secondBox) const;
	bool IsColliding(const SphereCollider& secondSphere) const;
	glm::vec3 PointOnBox(GLfloat x, GLfloat y, GLfloat z) const;

	void Update();
	void Render() { /*debug only*/ }

private:

	glm::vec3 m_min;
	glm::vec3 m_max;
	glm::vec4 m_color;
	glm::vec3 m_scale;
	glm::vec3 m_position;
	glm::vec3 m_dimension;
	glm::vec3 m_halfDimension;

};