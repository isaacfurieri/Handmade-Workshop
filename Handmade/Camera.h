#ifndef CAMERA_H
#define CAMERA_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Camera' source files last updated in December 2019									        |
#==============================================================================================*/

#include <string>
#include "glad.h"
#include <glm.hpp>

class Camera
{

public:

	static void SetIdentity();
	static void SendToShader();
	static glm::vec3& Position();

private:

	static glm::vec3 s_position;
	static glm::mat4 s_viewMatrix;

public:

	Camera();

public:

	bool& IsFreeFlow();

public:

	void SetVelocity(GLfloat velocity);
	void SetSensitivity(GLfloat sensitivity);
	void SetThreshold(GLfloat min, GLfloat max);
	void SetLookAt(GLfloat x, GLfloat y, GLfloat z);

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

	bool m_isFreeFlow;
	
	GLfloat m_velocity;
	GLfloat m_sensitivity;

	glm::vec3 m_lookAt;
	glm::vec3 m_upVector;
	glm::vec2 m_threshold;
	glm::vec3 m_moveDirection;
	glm::vec3 m_viewDirection;

	glm::mat4 m_rotationMatrixX;
	glm::mat4 m_rotationMatrixY;
	
};

#endif