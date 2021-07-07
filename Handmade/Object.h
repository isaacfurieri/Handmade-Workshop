#pragma once

/*===================================================================#
| 'Object' source files last updated on 7 July 2021                  |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>
#include <string>
#include "Shader.h"
#include "Transform.h"

class Object
{

public:

	Object();
	virtual ~Object() = 0 {}

	bool IsLit() const;
	bool IsAlive() const;
	bool IsActive() const;
	bool IsVisible() const;
	bool IsTextured() const;

	void IsLit(bool flag);
	void IsAlive(bool flag);
	void IsActive(bool flag);
	void IsVisible(bool flag);
	void IsTextured(bool flag);

	GLuint GetPriority() const;
	const std::string& GetTag();

	Transform& GetTransform();

	void SetPriority(GLuint priority);
	void SetTag(const std::string& tag);

	virtual void Render(Shader& shader) = 0;
	virtual void Update(GLfloat deltaTime) = 0;
	virtual void SendToShader(Shader& shader) = 0;

protected:

	bool m_isLit;
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;
	bool m_isTextured;

	std::string m_tag;
	GLuint m_priority;
	Transform m_transform;
	glm::mat3 m_normalMatrix;

};