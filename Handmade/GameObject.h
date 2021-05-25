#pragma once

/*===================================================================#
| 'GameObject' source files last updated on 25 May 2021              |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>
#include <string>

//TODO - Add 'CreatePrimitive()' function to 'GameObject' class to create set primitives 

class GameObject
{

public:

	GameObject();
	virtual ~GameObject() = 0 {}

	bool IsLit();
	void IsLit(bool flag);

	bool IsAlive();
	void IsAlive(bool flag);

	bool IsActive();
	void IsActive(bool flag);

	bool IsVisible();
	void IsVisible(bool flag);

	bool IsTextured();
	void IsTextured(bool flag);

	GLuint GetPriority();
	const std::string& GetTag();

	void SetTag(const std::string& tag);
	void SetPriority(GLuint priority);

	virtual bool Create() = 0;
	virtual void Update(GLint deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	void SendToShader(bool isLit, bool isTextured);

protected:

	bool m_isLit;
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;
	bool m_isTextured;

	GLuint m_priority;
	std::string m_tag;
	glm::mat4 m_modelMatrix;

};