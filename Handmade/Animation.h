/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2016

  -----------------------------------------------------------------------------------------------

- This class encapsulates animation objects and derives from the Sprite base class. Animations 
  generally use spritesheets with multiple images and loop through them either endlessly or for 
  one cylce only. This setting can be set externally from the client code. The animation speed can 
  also be set externally. 

- The IsAnimationLooping() function returns a bool reference variable, which makes this routine a 
  getter/setter. This makes setting the flag in the client code a lot easier.

- Because the texture index value is calculated differently here than in the Sprite base class, the 
  Draw() function is overriden.

*/

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Sprite.h"

class Animation : public Sprite
{

public:

	Animation();
	virtual ~Animation() {}

public:

	bool& IsAnimationLooping();
	bool GetKillAnimation();
	void SetAnimationVelocity(GLfloat velocity);
	
public:

	virtual void Draw();

protected:

	bool m_killAnimation;
	bool m_finalAnimationLoop;
	bool m_isAnimationLooping;
	
	GLdouble m_timeElapsed;
	GLfloat m_animationVelocity;

};

#endif