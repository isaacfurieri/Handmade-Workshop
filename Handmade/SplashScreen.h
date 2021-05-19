#pragma once

/*===================================================================#
| 'SplashScreen' source files last updated on 19 May 2021            |
#===================================================================*/

#include <string>
#include "glad.h"
#include "GameObject.h"
#include "Sprite.h"

class SplashScreen : public GameObject
{

public:

	enum Fade
	{
		FADE_IN,
		FADE_OUT
	};

	SplashScreen(const std::string& filename);
	virtual ~SplashScreen() {}

	virtual bool Create();
	virtual void Update(int deltaTime);
	virtual void Draw();
	virtual void Destroy();

private:

	Fade m_fade;
	GLfloat m_alpha;
	Sprite m_sprite;
	std::string m_filename;
	glm::ivec2 m_dimension;

};