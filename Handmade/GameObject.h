#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm.hpp>
#include <string>

class GameObject 
{

public:

	GameObject();
	virtual ~GameObject() = 0 {}

public:

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

public:

	const std::string& GetTag();
	unsigned int GetPriority();

	void SetTag(const std::string& tag);
	void SetPriority(unsigned int priority);

public:

	virtual bool Create()              = 0;
	virtual void Update(int deltaTime) = 0;
	virtual void Draw()                = 0;
	virtual void Destroy()             = 0;

public:

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

#endif