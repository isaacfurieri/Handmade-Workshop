/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This game object represents the main viewing camera and contains a Camera component that will
  represent the camera's orientation and position in the game world. There is a CheckInput() 
  routine that reads keypresses and mouse motions to determine which way the camera will be moving
  and rotating. The Update() function will constantly call this routine and if it returns false it
  means the player pressed ESCAPE and wishes to quit, which will set the camera's m_active flag 
  accordingly. The camera determines when the game state ends. The Draw() function will set the 
  view matrix and set up the camera accordingly. This should be done before all game objects are 
  drawn on screen, meaning that this camera's Draw() routine should be called before all other game 
  objects are drawn. 

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

	virtual void Update();
	virtual bool Draw();

private :

	bool CheckInput();

private :

	Camera m_camera;

};

#endif