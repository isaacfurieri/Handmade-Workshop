/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This game object represents the 2D camera that is needed to render 2D objects on screen, such as
  the HUD or text. It works as a secondary camera to the main camera and should be called before
  each 2D object is rendered. The Draw() function will simply reset the camera component's view
  matrix to the identity, which is all we need as a view before rendering our 2D objects.
  This camera should not be confused with the main camera's 2D setting, which is for orthographic
  view in games, and is treated separately to this one.

*/

#ifndef HUD_CAMERA_H
#define HUD_CAMERA_H

#include "Camera.h"
#include "GameObject.h"

class HUDCamera : public GameObject
{

public:

	virtual ~HUDCamera() {}

public:

	virtual void Update() {}
	virtual bool Draw();

private:

	Camera m_camera;

};

#endif