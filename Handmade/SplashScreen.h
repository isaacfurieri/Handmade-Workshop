#pragma once

/*===================================================================#
| 'SplashScreen' source files last updated on 25 May 2021            |
#===================================================================*/

#include <string>
#include "glad.h"
#include "GameObject.h"
#include "Sprite.h"

class SplashScreen : public GameObject
{

public:

	enum class Fade
	{
		FADE_IN,
		FADE_OUT
	};

	SplashScreen(const std::string& filename);
	virtual ~SplashScreen() {}

	virtual bool Create();
	virtual void Update(GLint deltaTime);
	virtual void Draw();
	virtual void Destroy();

private:

	Fade m_fade;
	GLfloat m_alpha;
	Sprite m_sprite;
	std::string m_filename;
	glm::ivec2 m_dimension;

};