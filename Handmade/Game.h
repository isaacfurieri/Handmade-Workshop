#ifndef GAME_H
#define GAME_H

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
| 'Game' source files last updated in December 2019								                |
#==============================================================================================*/

#include <deque>
#include <string>
#include "GameState.h"

class Game
{

public:

	static Game* Instance();

public:

	int GetTotalTime();
	int GetElapsedTime();

public:

	bool Initialize(std::string name, int screenWidth, int screenHeight, 
		            int pixelsPerUnit = 1, bool fullscreen = false);
	
	void AddState(GameState* state);
	void ChangeState(GameState* state);

	bool Run();
	void ShutDown();


private:

	Game();
	Game(const Game&);
	Game& operator=(const Game&);

private:

	void RemoveState();

private:

	bool m_endGame;
	int m_elapsedTime;
	std::deque<GameState*> m_gameStates;
	
};

#endif