#ifndef START_STATE_H
#define START_STATE_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'StartState' source files last updated in February 2020								        |
#==============================================================================================*/

#include "GameState.h"
#include "SplashScreen.h"
#include "UICamera.h"

class StartState : public GameState
{

public:

	StartState(Game* game, GameState* state);
	virtual ~StartState() {}

public:

	virtual bool OnEnter();
	virtual bool Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

private:

	UICamera* m_UICamera;
	SplashScreen* m_splashScreen_1;
	SplashScreen* m_splashScreen_2;
	
};

#endif
