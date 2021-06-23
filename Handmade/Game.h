#pragma once

/*===================================================================#
| 'Game' source files last updated on 25 May 2021                    |
#===================================================================*/

#include "glad.h"
#include <deque>
#include <string>

//TODO - Refine class such that it follows newer design

class Game
{

public:

	Game();

	int GetTotalTime();
	int GetElapsedTime();

	bool Initialize(const std::string& name, GLuint screenWidth, GLuint screenHeight,
		GLuint pixelsPerUnit = 1, bool isFullscreen = false);

	bool Run();
	void ShutDown();

private:

	bool m_endGame;
	int m_deltaTime;

};