#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include "Camera.h"

class UICamera : public Camera
{

public:

	virtual bool Create()               { return true; }
	virtual void Update(int deltaTime);
	virtual void Draw()                 {};
	virtual void Destroy()              {};

};

#endif