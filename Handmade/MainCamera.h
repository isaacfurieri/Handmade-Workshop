/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This game object represents the main viewing camera and contains a Camera component that will
  represent the camera's orientation and position in the game world. The Update() function will 
  constantly check what keys are pressed and determine how to move the camera based on the mouse
  motion. The Draw() function will pass the view matrix to the vertex shader This should be done 
  before all game objects are drawn on screen, meaning that this camera's Draw() routine should 
  be called before all other game objects are drawn. 

*/

#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H

#include "Camera.h"
#include "GameObject.h"

class MainCamera : public GameObject
{

public:

	MainCamera();
	virtual ~MainCamera() {}

public:

	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {}

private :

	Camera m_camera;

};

#endif