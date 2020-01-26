#ifndef MAIN_STATE_H
#define MAIN_STATE_H

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
| 'MainState' source files last updated in January 2020								            |
#==============================================================================================*/

#include <vector>
#include "GameObject.h"
#include "GameState.h"
#include "HUD.h"
#include "HUDCamera.h"
#include "MainCamera.h"

class MainState : public GameState
{

public:

	MainState(Game* game, GameState* state);
	virtual ~MainState() {}

public:

	virtual bool OnEnter();
	virtual bool Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

private :

	HUD* m_HUD;
	HUDCamera* m_HUDCamera;
	MainCamera* m_mainCamera;
	
	std::vector<GameObject*> m_gameObjects;

};

#endif