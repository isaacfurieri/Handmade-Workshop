/*===================================================================#
| 'Main' source file last updated on 25 May 2021                     |
#===================================================================*/

//include SDL main header file to prevent 
//main lib conflicts in Release mode
#include <SDL.h>  

#include <string>
#include "Game.h"

//screen width and height values
int screenWidth = 1280;
int screenHeight = 720;

//variable for name of game demo
std::string gameName = "<insert game name here>";

//scale value for 2D mode
int pixelsPerUnit = 50;

//======================================================================================================
int main(int argc, char* args[])
{
	Game* game = new Game;

	//initialize game with name, width and height accordingly
	//set the last parameter to "true" for fullscreen mode!
	if (!game->Initialize(gameName, screenWidth, screenHeight, pixelsPerUnit))
	{
		return 0;
	}

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