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
| 'Camera' source files last updated in February 2020									        |
#==============================================================================================*/

#include <glm.hpp>
#include "glad.h"
#include "GameObject.h"

class Camera : public GameObject
{

public:

	enum Origin2D { TOP_LEFT, BOTTOM_LEFT };

public:

	Camera();

public:

	void SetVelocity(GLfloat velocity);
	void SetFieldOfView(GLfloat fieldOfView);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetOrthoView(Origin2D origin = BOTTOM_LEFT);
	void SetPerspView(GLfloat nearClip = 0.1f, GLfloat farClip = 1000.0f);

public:

	virtual void Draw();

protected:

	GLfloat m_velocity;
	GLfloat m_fieldOfView;

	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_forward;
	glm::vec3 m_position;
	glm::vec3 m_direction;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projMatrix;
	
};

#endif