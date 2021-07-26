#include "FreeCamera.h"
#include "Input.h"
#include "Shader.h"

//======================================================================================================
FreeCamera::FreeCamera()
{
	m_isFlying = true;
	m_sensitivity = 0.0f;
	m_clampedYPosition = 1.0f;
	m_forward = glm::vec3(0.0f);
	m_pitchRange = glm::vec2(-89.0f, 89.0f);

	//We set the yaw to an initial 90 degrees so that the
	//forward vector calculations later result in (0, 0, -1)
	m_transform.SetRotation(0.0f, -90.0f, 0.0f);
}
//======================================================================================================
void FreeCamera::IsFlying(bool isFlying)
{
	m_isFlying = isFlying;
}
//======================================================================================================
void FreeCamera::SetSensitivity(GLfloat sensitivity)
{
	m_sensitivity = sensitivity;
}
//======================================================================================================
void FreeCamera::SetClampedYPosition(GLfloat position)
{
	m_clampedYPosition = position;
}
//======================================================================================================
void FreeCamera::SetPitchRange(const glm::vec2& range)
{
	SetPitchRange(range.x, range.y);
}
//======================================================================================================
void FreeCamera::SetPitchRange(GLfloat min, GLfloat max)
{
	m_pitchRange.x = min;
	m_pitchRange.y = max;
}
//======================================================================================================
void FreeCamera::MoveUp()
{
	if (m_isFlying)
	{
		glm::vec3 right = glm::cross(m_forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(m_forward, right));
		m_transform.Translate(-up * m_velocity, Transform::Space::Global);
	}
}
//======================================================================================================
void FreeCamera::MoveDown()
{
	if (m_isFlying)
	{
		glm::vec3 right = glm::cross(m_forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(m_forward, right));
		m_transform.Translate(up * m_velocity, Transform::Space::Global);
	}
}
//======================================================================================================
void FreeCamera::MoveLeft()
{
	m_transform.Translate(glm::normalize(glm::cross(-m_forward, m_up)) * m_velocity, 
		Transform::Space::Global);
}
//======================================================================================================
void FreeCamera::MoveRight()
{
	m_transform.Translate(glm::normalize(glm::cross(m_forward, m_up)) * m_velocity,
		Transform::Space::Global);
}
//======================================================================================================
void FreeCamera::MoveForward()
{
	m_transform.Translate(m_forward * m_velocity, Transform::Space::Global);
}
//======================================================================================================
void FreeCamera::MoveBackward()
{
	m_transform.Translate(-m_forward * m_velocity, Transform::Space::Global);
}
//======================================================================================================
void FreeCamera::Zoom(GLint motion)
{
	m_fieldOfView += -motion;
	m_fieldOfView = glm::clamp(m_fieldOfView, MIN_FOV, MAX_FOV);
	CreatePerspView();
}
//======================================================================================================
void FreeCamera::Rotate(const glm::ivec2& motion)
{
	Rotate(motion.x, motion.y);
}
//======================================================================================================
void FreeCamera::Rotate(GLint motionX, GLint motionY)
{
	auto rotation = m_transform.GetEulerAngles();

	rotation.y += motionX * m_sensitivity;
	rotation.x += -motionY * m_sensitivity;
	rotation.x = glm::clamp(rotation.x, m_pitchRange.x, m_pitchRange.y);

	m_transform.SetRotation(rotation);
}
//======================================================================================================
void FreeCamera::Update(GLfloat deltaTime)
{
	if (!m_isFlying)
	{
		auto position = m_transform.GetPosition();
		position.y = m_clampedYPosition;
		m_transform.SetPosition(position);
	}

	//TODO - Fix the camera so that if not in 'fly' mode the camera still moves correctly
	//If camera is in debug/fly mode, transform the forward vector based on
	//the overall rotation, so that camera moves forward in any direction
	//m_forward = m_lookAt;

	//Otherwise ignore the y component so that the forward vector stays on a horizontal plane
	//when moving. This prevents the camera from moving forward freely and will restrict it. 
	//The camera still looks anywhere but moves with restrictions
	if (!m_isFlying)
	{
		m_forward.y = 0.0f;
	}

	//When the camera moves around the y-axis (yaw) the vector changes along the x/z plane
	//The x-axis (pitch) movements only affect the y component of the forward vector 
	auto rotation = m_transform.GetEulerAngles();
	m_forward.x = glm::cos(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));
	m_forward.y = glm::sin(glm::radians(rotation.x));
	m_forward.z = glm::sin(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));
}
//======================================================================================================
void FreeCamera::SendToShader(Shader& shader)
{
	m_viewMatrix = glm::lookAt(m_transform.GetPosition(), 
		m_transform.GetPosition() + m_forward, m_up);

	Camera::SendToShader(shader);
}

//======================================================================================================
//OLD code that makes use of rotation matrices - not ideal but good for learning
//======================================================================================================
//void FreeCamera::RotateMatrix()
//{
//	//create rotation matrices for x/y rotation
//	//we always start with fresh new matrices
//	m_rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(m_yaw), glm::vec3(0.0f, -1.0f, 0.0f));
//	m_rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(m_pitch), glm::vec3(-1.0f, 0.0f, 0.0f));
//
//	//create a total rotation transformation based on x and y rotations
//	//we do a y rotation FIRST and then a local x rotation thereafter
//	glm::mat4 totalRotation = m_rotationMatrixY * m_rotationMatrixX;
//
	//create a separate move rotation based on if camera is in freeflow mode or not
	//this affects movement so that camera either moves freely or is bound to a Y plane 
	//glm::mat4 moveRotation = (m_isFreeFlow) ? totalRotation : m_rotationMatrixY;

	//apply same rotation to move direction vector so that
	//the camera moves correctly based on camera orientation
	//m_moveDirection = glm::vec3(moveRotation * glm::vec4(m_moveDirection, 1.0f));

//	//calculate the FreeCamera's viewing vector by transforming the 
//	//initial viewing target based on FreeCamera's total rotation
//	m_lookAt = glm::vec3(totalRotation * glm::vec4(m_target, 1.0f));
//
//	//apply total rotation to move direction vector for correct movement
//	moveDirection = glm::vec3(totalRotation * glm::vec4(moveDirection, 1.0f));

	////update camera position based on move direction only if camera is set to move
	//if (moveDirection != glm::vec3(0.0f))
	//{
	//	m_position += moveDirection * m_velocity;
	//}

	////update camera's view matrix
	//m_viewMatrix = glm::lookAt(m_position, m_position + lookAtDirection, glm::vec3(0.0f, 1.0f, 0.0f));

//	//if camera is in debug/fly mode, transform the forward vector based on
//	//the overall rotation, so that camera moves forward in any direction
//	if (m_isFlying)
//	{
//		m_forward = m_lookAt;
//	}
//
//	//otherwise transform the forward vector based on ONLY the y-rotations as
//	//this prevents the camera from moving forward freely and will restrict it to
//	//a certain y-axis. The camera still looks anywhere but moves with restrictions
//	else
//	{
//		m_forward = glm::vec3(m_rotationMatrixY * glm::vec4(m_target, 1.0f));
//	}
//
//	//calculate the new right vector based on the forward vector
//	//so that camera can move local left/right based on rotation
//	m_right = glm::normalize(glm::cross(m_forward, m_up));
//}

//=============================================================================
//function that controls rotation of camera around local X axis
//=============================================================================
//void Camera::RotateX(short motionY)
//{
//
//	//generate a rotation angle based on mouse motion and rotation sensitivity
//	GLfloat angle = motionY * m_sensitivity;
//
//	//calculate the dot product between the "look at" vector and the up vector. This will
//	//give us a value to determine how far up or down the X axis the camera is tilting
//	double dot = glm::dot(m_lookAt, m_upVector);
//
//	//if the camera is tilting upwards or downwards and only if it is between its allowed 
//	//threshold, then accumulate the current X axis rotation using the angle calculated
//	if ((motionY > 0 && dot >= m_threshold.x) || (motionY < 0 && dot <= m_threshold.y))
//	{
//		m_rotationMatrixX = glm::rotate(m_rotationMatrixX,
//			glm::radians(angle),
//			glm::vec3(-1.0f, 0.0f, 0.0f));
//	}
//
//}

//=============================================================================
//function that controls rotation of camera around global Y axis
//=============================================================================
//void Camera::RotateY(short motionX)
//{
//
//	//generate a rotation angle based on mouse motion and rotation sensitivity
//	GLfloat angle = motionX * m_sensitivity;
//
//	//accumulate the current Y axis rotation using the angle calculated
//	m_rotationMatrixY = glm::rotate(m_rotationMatrixY,
//		glm::radians(angle),
//		glm::vec3(0.0f, -1.0f, 0.0f));
//
//}