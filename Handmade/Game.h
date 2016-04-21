/*
 
  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : April 2016

  -----------------------------------------------------------------------------------------------

- This class controls the main game. It is a Singleton so that it can be accessed from anywhere
  in the main code, and because only one game can exist at any one time. At its core, it consists
  of a vector of game states, that can be added and removed at any time from within the main 
  client code. The m_activeGameState variable will keep track of the active game state by always
  looking for the last state in the vector container. The active state will have its OnEnter(), 
  Update(), Draw() and OnExit() routines called accordingly from within this class' Run() function.
  when the state deactivates, the next active state will be sought out and controlled, until the
  vector contains no more states, at which point the game ends.

- The Initialize() and ShutDown() functions start up and close down all the other managers 
  respectively.

*/

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "GameState.h"
#include "Singleton.h"

class Game
{

public:

	friend class Singleton<Game>;

public:

	GameState* GetActiveGameState();
	void AddGameState(GameState* gameState);
	
public:

	bool Initialize(std::string name, int screenWidth, int screenHeight, 
		            int pixelScaleValue = 0, bool fullscreen = false);
	bool Run();
	void ShutDown();

private:

	Game();
	Game(const Game&);
	Game& operator=(const Game&);

private:

	GameState* m_activeGameState;
	std::vector<GameState*> m_gameStateManager;
	
};

typedef Singleton<Game> TheGame;

#endif