#pragma once

/*===================================================================#
| 'FreeCamera' source files last updated on 7 July 2021              |
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

	virtual void Render(Shader& shader) {};
	virtual void Update(GLfloat deltaTime);
	virtual void SendToShader(Shader& shader);

private:

	bool m_isFlying;
	bool m_isZooming;
	GLfloat m_sensitivity;

};