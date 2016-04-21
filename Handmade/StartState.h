/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : April 2016

  -----------------------------------------------------------------------------------------------

- This game state monitors the beginning state of the game. Things like menu's, start up screens,
  splash screens, etc are intended to be used here. This particular state consists of two 
  SplashScreen objects, which will draw two splash screen images before the Main State begins. It 
  will wait for one splash screen image to fade in and out before the next one becomes active.
  The OnEnter() function will create and compile the main game's vertex and fragment shaders as 
  well. These shaders are then only destroyed in the End State's OnExit() function so that they
  remain active throughout the program.

*/

#ifndef START_STATE_H
#define START_STATE_H

#include "GameState.h"
#include "SplashScreen.h"

class StartState : public GameState
{

public:

	StartState() {}
	virtual ~StartState() {}

public:

	virtual bool OnEnter();
	virtual bool Update();
	virtual bool Draw();
	virtual void OnExit();

private:

	SplashScreen* m_APILogo;
	SplashScreen* m_handmadeLogo;
	
};

#endif
