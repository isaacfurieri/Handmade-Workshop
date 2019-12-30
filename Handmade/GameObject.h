#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "glad.h"
#include <glm.hpp>
#include <string>
#include <vector>

class GameObject 
{

public:

	static void SetIdentity();
	static void PushMatrix();
	static void PopMatrix();
	static void SendToShader(bool isLit, bool isTextured);

	static void Translate(GLfloat x, GLfloat y, GLfloat z);
	//static void Rotate(Quaternion& quaternion);
	static void Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	static void Scale(GLfloat x, GLfloat y, GLfloat z);
	static void ScaleUV(GLfloat x, GLfloat y);

private:

	static glm::mat3 s_normalMatrix;
	static glm::mat4 s_textureMatrix;
	static std::vector<glm::mat4> s_modelMatrix;

public :

	GameObject();
	virtual ~GameObject() = 0 {}

public :

	bool& IsLit();
	bool& IsAlive();
	bool& IsActive();
	bool& IsVisible();
	bool& IsTextured();

public :

	std::string GetTag();
	unsigned int GetPriority();
	void SetTag(std::string tag);
	void SetPriority(unsigned int priority);

public:

	virtual bool Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

protected :

	bool m_isLit;
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;
	bool m_isTextured;

	std::string m_tag;
	unsigned int m_priority;

};

#endif