#include "RigidBody.h"

//======================================================================================================
glm::vec3 RigidBody::GravityForce(GLdouble mass_1, GLdouble mass_2, const glm::vec3& distance)
{
	GLdouble gravityForce = (GRAVITY * mass_1 * mass_2) /
		glm::length(distance) * glm::length(distance);
	return glm::normalize(distance) * static_cast<GLfloat>(gravityForce);
}
//======================================================================================================
glm::vec3 RigidBody::TorqueForce(const glm::vec3& force,
	const glm::vec3& contactPosition, const glm::vec3& centreOfMass)
{
	//The result produces a vector, used for the rotation axis and torque magnitude
	return glm::cross(force, (centreOfMass - contactPosition));
}
//======================================================================================================
RigidBody::RigidBody()
{
	m_mass = 0.0;
	m_angle = 0.0;
	m_angularMass = 0.0;
	m_angularVelocity = 0.0;
	m_angularAcceleration = 0.0;

	m_force = glm::vec3(0.0f);
	m_torque = glm::vec3(0.0f);
	m_position = glm::vec3(0.0f);
	m_velocity = glm::vec3(0.0f);
	m_acceleration = glm::vec3(0.0f);
}
//======================================================================================================
GLdouble RigidBody::GetAngle() const
{
	return m_angle;
}
//======================================================================================================
GLdouble RigidBody::GetAngularVelocity() const
{
	return m_angularVelocity;
}
//======================================================================================================
const glm::vec3& RigidBody::GetForce() const
{
	return m_force;
}
//======================================================================================================
const glm::vec3& RigidBody::GetTorque() const
{
	return m_torque;
}
//======================================================================================================
const glm::vec3& RigidBody::GetPosition() const
{
	return m_position;
}
//======================================================================================================
const glm::vec3& RigidBody::GetVelocity() const
{
	return m_velocity;
}
//======================================================================================================
void RigidBody::SetMass(GLdouble mass)
{
	m_mass = mass;
}
//======================================================================================================
void RigidBody::SetAngle(GLdouble angle)
{
	m_angle = angle;
}
//======================================================================================================
void RigidBody::SetAngularMass(GLdouble mass)
{
	m_angularMass = mass;
}
//======================================================================================================
void RigidBody::SetAngularVelocity(GLdouble velocity)
{
	m_angularVelocity = velocity;
}
//======================================================================================================
void RigidBody::SetForce(const glm::vec3& force)
{
	m_force = force;
}
//======================================================================================================
void RigidBody::SetTorque(const glm::vec3& torque)
{
	m_torque = torque;
}
//======================================================================================================
void RigidBody::SetPosition(const glm::vec3& position)
{
	m_position = position;
}
//======================================================================================================
void RigidBody::SetVelocity(const glm::vec3& velocity)
{
	m_velocity = velocity;
}
//======================================================================================================
void RigidBody::Update()
{
	if (m_mass > 0.0) m_acceleration = (m_force / (float)m_mass);
	if (m_angularMass > 0.0) m_angularAcceleration = glm::length(m_torque) / m_angularMass;

	glm::vec3 oldVelocity = m_velocity;
	m_velocity += m_acceleration * 0.16f;
	m_position += (m_velocity + oldVelocity) * 0.5f * 0.16f;

	GLdouble oldAngularVelocity = m_angularVelocity;
	m_angularVelocity += m_angularAcceleration * 0.16f;
	m_angle += (m_angularVelocity + oldAngularVelocity) * 0.5 * 0.16f;
}