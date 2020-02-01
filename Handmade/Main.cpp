/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

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
#include "Game.h"
#include "StartState.h"

//screen width and height values
int screenWidth = 1280;
int screenHeight = 720;

//variable for name of game demo
std::string gameName = "<insert game name here>";

//scale value for 2D mode
int pixelsPerUnit = 50;

//------------------------------------------------------------------------------------------------------
//main function that processes everything  
//------------------------------------------------------------------------------------------------------
int main(int argc, char* args[])
{

	Game* game = new Game;

	//initialize game with name, width and height accordingly
	//set the last parameter to "true" for fullscreen mode!
	if (!game->Initialize(gameName, screenWidth, screenHeight, pixelsPerUnit))
	{
		return 0;
	}

	//create the first state to be used in the game
	game->AddState(new StartState(game, nullptr));

	//run the game
	if (!game->Run())
	{
		return 0;
	}

	//close down game
	game->ShutDown();
	
	delete game;

	//end application
	return 0;

}