/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2016

  -----------------------------------------------------------------------------------------------

- This is a Camera class that encapsulates FPS camera movement using Quaternions to represent the 
  rotations. The camera can move in the basic six directions. It can be set to be in free flow mode 
  or not, which will greatly affect these movements. In other words the camera will move forward, 
  backward, up and down differently in free flow mode because the X rotations / tilting is taken 
  into consideration. The left and right movements are always relative no matter what. 
  
- The member variables of the class define all the basic properties of the camera, such as position,
  speed, sensitivity, etc. The free flow variable allows setting the free flow mode on or off, which
  controls if the camera can roam freely in the game world, or if it is set to a specific horizontal
  Y plane respectively.
  There are two main quaternion variables, namely m_totalRotation and m_totalRotationY. The first 
  one represents the total X and Y rotations of the camera, and the second only the Y rotations, 
  which ignore the tilting X rotations. If the camera is free flowing, the total rotations are used,
  making sure the camera moves forwards / backwards / up / down, taking X rotations into account.
  Otherwise for a non-freeflow camera, only the Y rotations are used, meaning that no matter how 
  much the camera is rotated in X, the forwards / backwards / up / down movements remains on the 
  global horizontal Y plane.
  The m_moveDirection variable determines which direction the camera moves in and the 
  m_lookAtDirection determines where the camera is looking. Both these properties are not always 
  going to be the same. There is also a m_threshold variable which determines the min and max
  allowance value that the camera can tilt on its X axis, so that it doesn't look upwards or 
  downwards beyond its limits.

- The position of the camera can be adjusted by using the Position() function which returns a
  reference to the position variable. This makes getting and setting the positional XYZ components
  in the client code a lot easier. The other getter and setter functions will return or assign other
  properties of the camera respectively.

- The main functionality of the camera happens in the Update() and Draw() routines. The Update()
  routine will orientate and position the camera in the game world, using the correct camera 
  rotations, and the Draw() function applies the camera rotations and positioning to the modelview
  matrix, to correctly set up the view. The main difference between Update() and Draw() is that in
  the Update() function the camera's movement vectors are transformed using the camera quaternion's
  inverse rotations, while the Draw() routine applies the regular quaternion rotations to the world.
  This is because the way the camera views the world is opposite to the way the world around it is
  transformed.

- The movement functions all set the movement vectors for the camera which are later transformed
  by the internal quaternion so that the camera actually moves in the right direction based on
  where it's looking. The two rotation functions will rotate the X and Y axis of the camera, making
  sure that the camera's X-axis is local and its Y-axis is global. Using this functionality, the six
  movements will always work correctly and accordingly.

*/

#ifndef CAMERA_H
#define CAMERA_H

#include "Quaternion.h"
#include "Vector2D.h"
#include "Vector3D.h"

class Camera
{

public:

	Camera();

public:

	bool& IsFreeFlow();
	Vector3D<double>& Position();
	Vector3D<double>  GetLookAtDirection();

public:

	void SetVelocity(float velocity);
	void SetSensitivity(float sensitivity);
	void SetThreshold(float min, float max);

public:

	void Update();
	void Draw();

public:

	void Stop();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void RotateY(short motionX);
	void RotateX(short motionY);

private:

	bool m_freeFlow;
	float m_velocity;
	float m_sensitivity;

	Quaternion m_totalRotation;
	Quaternion m_totalRotationY;

	Vector2D<float> m_threshold;
	Vector3D<double> m_position;
	Vector3D<double> m_upVector;
	Vector3D<double> m_moveDirection;	
	Vector3D<double> m_lookAtDirection;
	
};

#endif