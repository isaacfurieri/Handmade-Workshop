#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

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
| 'Camera' source files last updated in February 2020									        |
#==============================================================================================*/

#include <string>
#include "glad.h"
#include <glm.hpp>
#include "Camera.h"

class FPSCamera : public Camera
{

public:

	FPSCamera();

public:

	bool IsFlying();
	void IsFlying(bool isFlying);

public:

	void SetSensitivity(GLfloat sensitivity);
	void SetTarget(GLfloat x, GLfloat y, GLfloat z);

public:

	virtual bool Create()               { return true; }
	virtual void Update(int deltaTime);
	virtual void Draw()                 {};
	virtual void Destroy()              {};
	
private:

	void UseMatrix();
	void UseSinCos();

private:

	bool m_isFlying;
	
	GLfloat m_yaw;
	GLfloat m_pitch;
	GLfloat m_sensitivity;
	
	glm::vec3 m_lookAt;
	glm::vec3 m_target;
	glm::mat4 m_rotationMatrixX;
	glm::mat4 m_rotationMatrixY;
	
};

#endif