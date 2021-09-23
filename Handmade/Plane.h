#pragma once

/*===================================================================#
| 'Plane' source files last updated on 5 August 2021                 |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>
#include "LineSegment.h"
#include "SphereCollider.h"

struct PlanePoints
{
	glm::vec3 point1 = glm::vec3(0.0f);
	glm::vec3 point2 = glm::vec3(0.0f);
	glm::vec3 point3 = glm::vec3(0.0f);
	glm::vec3 point4 = glm::vec3(0.0f);
};

class Plane
{

public:

	enum class PlaneSide
	{
		OnPlane,
		Positive,
		Negative
	};

	Plane();

	void SetPoint1(const glm::vec3& point1);
	void SetPoint1(GLfloat x, GLfloat y, GLfloat z);
	
	void SetPoint2(const glm::vec3& point2);
	void SetPoint2(GLfloat x, GLfloat y, GLfloat z);
	
	void SetPoint3(const glm::vec3& point3);
	void SetPoint3(GLfloat x, GLfloat y, GLfloat z);
	
	void SetPoint4(const glm::vec3& point4);
	void SetPoint4(GLfloat x, GLfloat y, GLfloat z);

	void SetPosition(const glm::vec3& position);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	bool IsColliding(const SphereCollider& secondSphere) const;
	
	PlaneSide SideOfPlane(const glm::vec3& point) const;
	PlaneSide SideOfPlane(GLfloat x, GLfloat y, GLfloat z) const;
	
	GLfloat DistanceFromPlane(const glm::vec3& point) const;
	GLfloat DistanceFromPlane(GLfloat x, GLfloat y, GLfloat z) const;
	GLfloat DistanceFromPlane(const LineSegment& lineSegment) const;

	void Update();
	void Render() { /*debug only*/ }

private:

	glm::vec4 m_color;
	glm::vec3 m_normal;
	glm::vec3 m_position;
	PlanePoints m_planePoints;
	GLfloat m_distanceFromOrigin;

};