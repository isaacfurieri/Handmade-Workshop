#pragma once

/*===================================================================#
| 'UICamera' source files last updated on 19 May 2021                |
#===================================================================*/

#include "Camera.h"

//TODO - Refine class such that it follows newer design

class UICamera : public Camera
{

public:

	UICamera() {}
	virtual ~UICamera() {}

	virtual bool Create() { return true; }
	virtual void Update(int deltaTime);
	virtual void Destroy() {};

};