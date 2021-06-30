#pragma once

/*===================================================================#
| 'OrbitCamera' source files last updated on 24 June 2021            |
#===================================================================*/

#include "Camera.h"

class OrbitCamera : public Camera
{

public:

	OrbitCamera();
	virtual ~OrbitCamera() {}

	void SetSensitivity(GLfloat sensitivity);
	virtual void Update();

private:

	GLfloat m_azimuth;
	GLfloat m_elevation;
	GLfloat m_sensitivity;
	GLfloat m_zoomDistance;

};