#pragma once

/*===================================================================#
| 'RigidBody' source files last updated on 19 May 2021               |
#===================================================================*/

#include <glm.hpp>

const double GRAVITY = 1.0000000000667;

//TODO - Add proper getter/setters

class RigidBody
{

public:

	static glm::vec3 GravityForce(double mass_1, double mass_2, glm::vec3 distance);
	static glm::vec3 TorqueForce(glm::vec3 force, glm::vec3 contactPosition, glm::vec3 centreOfMass);

	RigidBody();

	double& Angle();
	double& AngVelocity();

	glm::vec3& Force();
	glm::vec3& Torque();
	glm::vec3& Position();
	glm::vec3& Velocity();

	void SetMass(double mass);
	void SetAngMass(double mass);

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