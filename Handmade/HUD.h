/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This game object represents and draws a 2D heads-up display on screen for the viewer to have 
  on-screen information at hand. The main component is the Sprite, which is used to represent the
  2D image and draw it on screen. 

*/

#ifndef HUD_H
#define HUD_H

#include "glad.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"

class HUD : public GameObject
{

public:

	virtual ~HUD() {}

public:

	virtual bool Create();
	virtual void Update() {}
	virtual void Draw();
	virtual void Destroy();

private :

	Sprite m_sprite;

};

#endif