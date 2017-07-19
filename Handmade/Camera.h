/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This is a Camera class that encapsulates FPS camera movement using basic matrix transformations 
  to represent the rotations. The camera can move in the basic six directions. It can be set to be
  in free flow mode or not, which will greatly affect these movements. In other words the camera 
  will move forward, backward, up and down differently in free flow mode because the X rotations or
  "tilting" is taken into consideration. The left and right movements are always relative no matter
  what. 
  
- There are a few static variables and functions which were added to allow global access to the 
  camera's main properties, that belong to the camera. Of these is the view matrix, because we only
  need one matrix to represent the camera view. The other variable is the ID that monitors the 
  vertex shader's view matrix uniform, to which the view matrix is passed to. The static functions
  allow for the view matrix to be reset to the identity and passed to the vertex shader. The view
  matrix is transformed in the Update() routine, and no need to manually transform it, unlike how
  the GameObject class deals with its model matrix.

- The member variables of the class define all the basic properties of the camera, such as position,
  speed, sensitivity, etc. The free flow variable allows setting the free flow mode on or off, which
  controls if the camera can roam freely in the game world, or if it is set to a specific horizontal
  Y plane respectively.
  There are two main matrix variables, one to hold the X rotations and one to hold the Y rotations
  of the camera. If the camera is free flowing, the total rotations are used, ie X and Y combined,
  making sure the camera moves forwards / backwards / up / down, taking X rotations into account.
  Otherwise for a non-freeflow camera, only the Y rotations are used, meaning that no matter how 
  much the camera is rotated in X, the forwards / backwards / up / down movements remains on the 
  global horizontal Y plane.
  The m_moveDirection variable determines which direction the camera moves in and the 
  m_viewDirection determines where the camera is looking. Both these properties are not always 
  going to be the same. There is also a m_threshold variable which determines the min and max
  allowance value that the camera can tilt on its X axis, so that it doesn't look upwards or 
  downwards beyond its limits.
  
- The position of the camera can be adjusted by using the Position() function which returns a
  reference to the position variable. This makes getting and setting the positional XYZ components
  in the client code a lot easier. The other getter and setter functions will return or assign other
  properties of the camera respectively. The SetLookAt() function sets the initial direction the
  camera is looking in. By default this is always down the negative Z-axis (OpenGL), but for 
  multiple cameras, each one might initially be looking in different directions, and these initial
  directions will be transformed accordingly.

- The main functionality of the camera happens in the Update() and Draw() routines. The Update()
  routine will orientate and position the camera in the game world, using the correct camera 
  rotations, and applies the camera orientation and positioning to the internal view matrix, to 
  correctly set up the view.

- The movement functions all set the movement vectors for the camera which are later transformed
  by the matrix transformations so that the camera actually moves in the right direction based on
  where it's looking. The two rotation functions will rotate the X and Y axis of the camera, making
  sure that the camera's X-axis is local and its Y-axis is global. Using this functionality, the six
  movements will always work correctly and accordingly.

*/

#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <glew.h>
#include <glm.hpp>

class Camera
{

public:

	static void SetIdentity();
	static void ApplyMatrix();
	static void SetViewUniformID(std::string uniformID);

private:

	static GLuint s_viewUniformID;
	static glm::mat4 s_viewMatrix;

public:

	Camera();

public:

	bool& IsFreeFlow();
	glm::vec3& Position();
	glm::vec3 GetViewDirection();

public:

	void SetVelocity(float velocity);
	void SetSensitivity(float sensitivity);
	void SetThreshold(float min, float max);
	void SetLookAt(float x, float y, float z);

public:

	void Update();

public:

	void Stop();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void RotateX(short motionY);
	void RotateY(short motionX);

private:

	bool m_freeFlow;
	float m_velocity;
	float m_sensitivity;

	glm::vec2 m_threshold;
	glm::vec3 m_position;

	glm::vec3 m_lookAt;
	glm::vec3 m_upVector;
	glm::vec3 m_moveDirection;
	glm::vec3 m_viewDirection;

	glm::mat4 m_rotationMatrixX;
	glm::mat4 m_rotationMatrixY;
	
};

#endif