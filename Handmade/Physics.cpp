#include <gtx\norm.hpp>
#include "Game.h"
#include "Physics.h"

//------------------------------------------------------------------------------------------------------
//static function that calculates gravitational force using a formula 
//------------------------------------------------------------------------------------------------------
glm::vec3 Physics::GravityForce(double mass_1, double mass_2, glm::vec3 distance)
{

	//the formula uses scalar values, so first the scalar value is calculated
	//and then applied to the normalised distance value passed, to retain direction
	double gravityForce = (GRAVITY * mass_1 * mass_2) / glm::length2(distance);
	return glm::normalize(distance) * (float)gravityForce;
	
}
//------------------------------------------------------------------------------------------------------
//static function that calculates torque force using a formula 
//------------------------------------------------------------------------------------------------------
glm::vec3 TorqueForce(glm::vec3 force, glm::vec3 contactPosition, glm::vec3 centreOfMass)
{

	//the result produces a vector, used for the rotation axis and torque magnitude
	return glm::cross(force, (centreOfMass - contactPosition));

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
Physics::Physics()
{

	m_mass = 0.0;
	m_angle = 0.0;
	m_angMass = 0.0;
	m_angVelocity = 0.0;
	m_angAcceleration = 0.0;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to angle variable 
//------------------------------------------------------------------------------------------------------
double& Physics::Angle()
{

	return m_angle;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to angular velocity variable 
//------------------------------------------------------------------------------------------------------
double& Physics::AngVelocity()
{

	return m_angVelocity;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to force variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& Physics::Force()
{

	return m_force;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to torque variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& Physics::Torque()
{

	return m_torque;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to position variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& Physics::Position()
{

	return m_position;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to velocity variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& Physics::Velocity()
{

	return m_velocity;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets mass of object
//------------------------------------------------------------------------------------------------------
void Physics::SetMass(double mass)
{

	m_mass = mass;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets angular mass of object
//------------------------------------------------------------------------------------------------------
void Physics::SetAngMass(double mass)
{

	m_angMass = mass;

}
//------------------------------------------------------------------------------------------------------
//function that updates acceleration, velocity and position of object
//------------------------------------------------------------------------------------------------------
void Physics::Update()
{

	//variables for storing old velocity values for 
	//both displacement and rotational calculations below
	double oldVel = 0.0;
	glm::vec3 oldVelocity;

	//calculate the movement and rotational acceleration
	//the latter uses the torque vector's magnitude for scalar calculations below
	if(m_mass > 0.0) m_acceleration = (m_force / (float)m_mass);
	if(m_angMass > 0.0) m_angAcceleration = glm::length(m_torque) / m_angMass;

	//calculate the new position using Euler Integration
	//this formula is frame independent and uses time for accurate calculations
	oldVelocity = m_velocity;
	m_velocity += m_acceleration * (float)TheGame::Instance()->GetElapsedTimeSeconds();
	m_position += (m_velocity + oldVelocity) * 0.5f * (float)TheGame::Instance()->GetElapsedTimeSeconds();

	//calculate the new rotational angle using Euler Integration
	//this formula is frame independent and uses time for accurate calculations	
	oldVel = m_angVelocity;
	m_angVelocity += m_angAcceleration * TheGame::Instance()->GetElapsedTimeSeconds();
	m_angle += (m_angVelocity + oldVel) * 0.5 * TheGame::Instance()->GetElapsedTimeSeconds();

}