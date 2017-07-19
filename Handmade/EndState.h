/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This game state monitors the final state of the game. Things like credits, end screens, final
  messages, etc are intended to be used here. This particular state consists of only one single
  SplashScreen object, which will render the final credits message splash screen before the 
  application ends for good. The OnExit() routine will destroy the main game's vertex and fragment
  shaders that were created and compiled in the Start State's OnEnter() function.

*/

#ifndef END_STATE_H
#define END_STATE_H

#include "GameState.h"
#include "HUDCamera.h"
#include "SplashScreen.h"

class EndState : public GameState
{

public:

	EndState() {}
	virtual ~EndState() {}

public:

	virtual bool OnEnter();
	virtual bool Update();
	virtual bool Draw();
	virtual void OnExit();

private:

	HUDCamera* m_HUDCamera;
	SplashScreen* m_endMessage;

};

#endif
