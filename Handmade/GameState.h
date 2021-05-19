#ifndef GAME_STATE_H
#define GAME_STATE_H

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
| 'GameState' source files last updated in January 2020	  							            |
#==============================================================================================*/

class Game;

//TODO - Consider removing all game states and have only one single state

class GameState
{

public:

	GameState(Game* game, GameState* state);
	virtual ~GameState() = 0 {}

public:

	bool& IsAlive();
	bool& IsActive();

public:

	virtual bool OnEnter()             = 0;
	virtual bool Update(int deltaTime) = 0;
	virtual bool Draw()                = 0;
	virtual void OnExit()              = 0;

protected:

	bool m_isAlive;
	bool m_isActive;

	Game* m_game;
	GameState* m_previousState;

};

#endif