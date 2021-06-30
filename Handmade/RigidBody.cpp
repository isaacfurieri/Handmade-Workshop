#include "RigidBody.h"

//======================================================================================================
glm::vec3 RigidBody::GravityForce(double mass_1, double mass_2, glm::vec3 distance)
{
	//the formula uses scalar values, so first the scalar value is calculated
	//and then applied to the normalised distance value passed, to retain direction
	double gravityForce = (GRAVITY * mass_1 * mass_2) / glm::length(distance) * glm::length(distance);
	return glm::normalize(distance) * (float)gravityForce;
}
//======================================================================================================
glm::vec3 RigidBody::TorqueForce(glm::vec3 force, glm::vec3 contactPosition, glm::vec3 centreOfMass)
{
	//the result produces a vector, used for the rotation axis and torque magnitude
	return glm::cross(force, (centreOfMass - contactPosition));
}
//======================================================================================================
RigidBody::RigidBody()
{
	m_mass = 0.0;
	m_angle = 0.0;
	m_angMass = 0.0;
	m_angVelocity = 0.0;
	m_angAcceleration = 0.0;

	m_force = glm::vec3(0.0f);
	m_torque = glm::vec3(0.0f);
	m_position = glm::vec3(0.0f);
	m_velocity = glm::vec3(0.0f);
	m_acceleration = glm::vec3(0.0f);
}
//======================================================================================================
double& RigidBody::Angle()
{
	return m_angle;
}
//======================================================================================================
double& RigidBody::AngVelocity()
{
	return m_angVelocity;
}
//======================================================================================================
glm::vec3& RigidBody::Force()
{
	return m_force;
}
//======================================================================================================
glm::vec3& RigidBody::Torque()
{
	return m_torque;
}
//======================================================================================================
glm::vec3& RigidBody::Position()
{
	return m_position;
}
//======================================================================================================
glm::vec3& RigidBody::Velocity()
{
	return m_velocity;
}
//======================================================================================================
void RigidBody::SetMass(double mass)
{
	m_mass = mass;
}
//======================================================================================================
void RigidBody::SetAngMass(double mass)
{
	m_angMass = mass;
}
//======================================================================================================
void RigidBody::Update()
{
	//variables for storing old velocity values for 
	//both displacement and rotational calculations below
	double oldVel = 0.0;
	glm::vec3 oldVelocity;

	//calculate the movement and rotational acceleration
	//the latter uses the torque vector's magnitude for scalar calculations below
	if (m_mass > 0.0) m_acceleration = (m_force / (float)m_mass);
	if (m_angMass > 0.0) m_angAcceleration = glm::length(m_torque) / m_angMass;

	//calculate the new position using Euler Integration
	//this formula is frame independent and uses time for accurate calculations
	oldVelocity = m_velocity;
	m_velocity += m_acceleration * 0.16f; // ((float)Game::Instance()->GetElapsedTime() / 1000);
	m_position += (m_velocity + oldVelocity) * 0.5f * 0.16f; // ((float)Game::Instance()->GetElapsedTime() / 1000);

	//calculate the new rotational angle using Euler Integration
	//this formula is frame independent and uses time for accurate calculations	
	oldVel = m_angVelocity;
	m_angVelocity += m_angAcceleration * 0.16f; // Game::Instance()->GetElapsedTime() / 1000; //temp!
	m_angle += (m_angVelocity + oldVel) * 0.5 * 0.16f; // Game::Instance()->GetElapsedTime() / 1000; //temp!
}