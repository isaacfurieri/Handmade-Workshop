#pragma once

/*===================================================================#
| 'OBBCollider' source files last updated on 4 August 2021           |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include "BoxCollider.h"
#include "SphereCollider.h"

class OBBCollider
{

public:

	OBBCollider();

	const glm::vec3& GetScale() const;
	const glm::vec3& GetPosition() const;
	const glm::quat& GetRotation() const;
	const glm::vec3& GetDimension() const;

	void SetScale(const glm::vec3& scale);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);

	void SetPosition(const glm::vec3& position);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	void SetRotation(const glm::quat& rotation);
	void SetRotation(const glm::vec3& eulerAngles);
	void SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll);

	void SetDimension(const glm::vec3& dimension);
	void SetDimension(GLfloat width, GLfloat height, GLfloat depth);

	bool IsColliding(const OBBCollider& secondBox) const;
	bool IsColliding(const BoxCollider& secondBox) const;
	bool IsColliding(const SphereCollider& secondSphere) const;
	
	glm::vec3 PointOnBox(const glm::vec3& point) const;
	glm::vec3 PointOnBox(GLfloat x, GLfloat y, GLfloat z) const;

	void Update();
	void Render() { /*debug only*/ }

private:

	glm::vec3 m_upAxis;
	glm::vec3 m_rightAxis;
	glm::vec3 m_forwardAxis;
	glm::vec3 m_corners[8];

	glm::vec4 m_color;
	glm::vec3 m_scale;
	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_dimension;
	glm::vec3 m_halfDimension;

};