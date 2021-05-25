#pragma once

/*===================================================================#
| 'HUD' source files last updated on 25 May 2021                     |
#===================================================================*/

#include "glad.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"

class HUD : public GameObject
{

public:

	virtual ~HUD() {}

	virtual bool Create();
	virtual void Update(int deltaTime) {}
	virtual void Draw();
	virtual void Destroy();

private:

	Sprite m_sprite;
	glm::ivec2 m_dimension;

};