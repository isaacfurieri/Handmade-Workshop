#pragma once

/*===================================================================#
| 'FreeCamera' source files last updated on 24 June 2021             |
#===================================================================*/

#include "Camera.h"

class FreeCamera : public Camera
{

public:

	FreeCamera();
	virtual ~FreeCamera() {}

	void IsFlying(bool isFlying);
	void IsZooming(bool isZooming);
	void SetSensitivity(GLfloat sensitivity);

	virtual void Update();

private:

	bool m_isFlying;
	bool m_isZooming;

	//TODO - Do we need this for correct orientation?
	glm::vec3 m_lookAt;  

	GLfloat m_sensitivity;

};