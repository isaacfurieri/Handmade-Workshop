#ifndef RIGIDBODY_H
#define RIGIDBODY_H

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
| 'RigidBody' source files last updated in December 2019									    |
#==============================================================================================*/

#include <glm.hpp>

const double GRAVITY = 1.0000000000667;

class RigidBody
{

public:

	static glm::vec3 GravityForce(double mass_1, double mass_2, glm::vec3 distance);
	static glm::vec3 TorqueForce(glm::vec3 force, glm::vec3 contactPosition, glm::vec3 centreOfMass);

public:

	RigidBody();

public:

	double& Angle();
	double& AngVelocity();

public:

	glm::vec3& Force();
	glm::vec3& Torque();
	glm::vec3& Position();
	glm::vec3& Velocity();

public:

	void SetMass(double mass);
	void SetAngMass(double mass);

public:

	void Update();

private:

	double m_mass;
	double m_angle;
	double m_angMass;  	
	double m_angVelocity;
	double m_angAcceleration;

	glm::vec3 m_force;
	glm::vec3 m_torque;
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

};

#endif