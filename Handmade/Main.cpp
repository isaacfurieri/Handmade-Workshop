/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : April 2016

  -----------------------------------------------------------------------------------------------

- This is the main starting point for the game demo. The main game state is created here and added
  to the main game manager, from where it is run. Change the screen width and height accordingly, 
  and set the pixel per unit value to whichever value you find most comfortable when in 2D mode. 
  Feel free to create and add more game states.

*/

//include SDL main header file to prevent 
//main lib conflicts in Release mode
#include <SDL.h>  

#include <string>
#include "EndState.h"
#include "Game.h"
#include "GameState.h"
#include "MainState.h"
#include "StartState.h"

//screen width and height values
int screenWidth = 1024;
int screenHeight = 768;

//variable for name of game demo
std::string gameName = "<insert game name here>";

//scale value for 2D mode
int pixelsPerUnit = 50;

//------------------------------------------------------------------------------------------------------
//main function that processes everything  
//------------------------------------------------------------------------------------------------------
int main(int argc, char* args[])
{

	//variables that reference all states of game 
	GameState* startState;
	GameState* mainState;
	GameState* endState;

	//initialize game with name, width and height accordingly
	//set last parameter to true for fullscreen mode!
	TheGame::Instance()->Initialize(gameName, screenWidth, screenHeight, pixelsPerUnit, false);

	//create all states for game 
	startState = new StartState();
	mainState = new MainState();
	endState = new EndState();

	//add game states to vector container in reverse order 
	//because they will be executed from the back of the vector
	TheGame::Instance()->AddGameState(endState);
	TheGame::Instance()->AddGameState(mainState);
	TheGame::Instance()->AddGameState(startState);
	
	//run game
	TheGame::Instance()->Run();

	//close down game
	TheGame::Instance()->ShutDown();

	//destroy all game states
	delete endState;
	delete mainState;
	delete startState;
	
	//end application
	return 0;

}