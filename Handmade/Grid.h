/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2016

  -----------------------------------------------------------------------------------------------

- This is a game object that represents a 2D or 3D grid based on what the game mode has been set
  to. It will use the Debug Manager's grid and coordinate system drawing routines to draw a 
  visual orientation in the dark world of OpenGL. This class is designed to be used as a debug
  tool only. 

*/

#ifndef GRID_H
#define GRID_H

#include "GameObject.h"

class Grid : public GameObject
{

public:

	Grid()                {}
	virtual ~Grid()       {}

public:

	virtual void Update() {}
	virtual bool Draw();

};

#endif