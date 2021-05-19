#pragma once

/*===================================================================#
| 'GameObject' source files last updated on 19 May 2021              |
#===================================================================*/

#include <glm.hpp>
#include <string>

//TODO - Add 'CreatePrimitive()' function to 'GameObject' class to create set primitives 

class GameObject
{

public:

	GameObject();
	virtual ~GameObject() = 0 {}

	bool IsLit();
	void IsLit(bool isLit);

	bool IsAlive();
	void IsAlive(bool isAlive);

	bool IsActive();
	void IsActive(bool isActive);

	bool IsVisible();
	void IsVisible(bool isVisible);

	bool IsTextured();
	void IsTextured(bool isTextured);

	const std::string& GetTag();
	unsigned int GetPriority();

	void SetTag(const std::string& tag);
	void SetPriority(unsigned int priority);

	virtual bool Create() = 0;
	virtual void Update(int deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	void SendToShader(bool isLit, bool isTextured);

protected:

	bool m_isLit;
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;
	bool m_isTextured;

	std::string m_tag;
	unsigned int m_priority;
	glm::mat4 m_modelMatrix;

};