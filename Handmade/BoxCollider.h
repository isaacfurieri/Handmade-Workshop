#pragma once

/*===================================================================#
| 'BoxCollider' source files last updated on 23 June 2021            |
#===================================================================*/

#include <glm.hpp>

//TODO - Add some kind of 'central system' to render all colliders in the scene

class SphereCollider;

class BoxCollider
{

public:

	BoxCollider();

	const glm::vec3& GetScale()     const;
	const glm::vec3& GetPosition()  const;
	const glm::vec3& GetDimension() const;

	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetDimension(float width, float height, float depth);

	bool IsColliding(const BoxCollider& secondBox) const;
	bool IsColliding(const SphereCollider& secondSphere) const;
	const glm::vec3& PointOnBox(float x, float y, float z) const;

	void Update();
	void Draw();

private:

	glm::vec3 m_min;
	glm::vec3 m_max;
	glm::vec4 m_color;
	glm::vec3 m_scale;
	glm::vec3 m_position;
	glm::vec3 m_dimension;
	glm::vec3 m_halfDimension;

};