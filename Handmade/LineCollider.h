#pragma once

/*===================================================================#
| 'LineCollider' source files last updated on 14 July 2021           |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>

class SphereCollider;

class LineCollider
{

public:

	LineCollider();

	//void SetScale(GLfloat scale);
	//void SetLength(GLfloat length);

	void SetStartPoint(const glm::vec3& startPoint);
	void SetStartPoint(GLfloat x, GLfloat y, GLfloat z);

	void SetEndPoint(const glm::vec3& endPoint);
	void SetEndPoint(GLfloat x, GLfloat y, GLfloat z);

	bool IsColliding(const SphereCollider& secondSphere) const;
	glm::vec3 PointOnLine(GLfloat positionX, GLfloat positionY, GLfloat positionZ) const;

	void Update();
	void Render() {}

private:

	GLfloat m_scale;
	GLfloat m_length;

	glm::vec4 m_color;
	glm::vec3 m_endPoint;
	glm::vec3 m_startPoint;

};