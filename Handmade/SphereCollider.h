#pragma once

/*===================================================================#
| 'SphereCollider' source files last updated on 23 June 2021         |
#===================================================================*/

#include "BoxCollider.h"

//TODO - Add some kind of 'central system' to render all colliders in the scene

class SphereCollider
{

public:

	SphereCollider();

	float GetScale() const;
	float GetRadius() const;
	float GetRadiusScaled() const;
	const glm::vec3& GetPosition() const;

	void SetScale(float scale);
	void SetRadius(float radius);
	void SetPosition(float x, float y, float z);

	bool IsColliding(const BoxCollider& secondBox) const;
	bool IsColliding(const SphereCollider& secondSphere) const;

	void Update();
	void Draw();

private:

	float m_scale;
	float m_radius;
	float m_radiusScaled;

	glm::vec4 m_color;
	glm::vec3 m_position;

};