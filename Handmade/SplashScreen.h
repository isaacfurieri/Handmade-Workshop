/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This game object represents and draws a 2D splash screen which is used in the Start State to
  display the game engine logo and the API logos used in the engine. It is also used in the End
  State to display any last minute contact info. The main component is the Sprite, which is used
  to represent the 2D image and draw it on screen. The fade variable monitors whether the image 
  is fading in or out, which is used to determine when to deactivate the image, ie as soon as it
  has faded out again. The constructor takes a string parameter to load in the correct splash
  image to be used.

*/

#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <string>
#include <glew.h>
#include "GameObject.h"
#include "Sprite.h"

class SplashScreen : public GameObject
{

public :

	enum Fade { FADE_IN, FADE_OUT };

public:

	SplashScreen(std::string filename);
	virtual ~SplashScreen();

public:

	virtual void Update();
	virtual bool Draw();

private:

	Fade m_fade;
	Sprite m_sprite;
	GLuint m_textureFlagUniformID;

};

#endif