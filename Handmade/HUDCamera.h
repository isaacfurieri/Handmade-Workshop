#ifndef HUD_CAMERA_H
#define HUD_CAMERA_H

#include "Camera.h"
#include "GameObject.h"

class HUDCamera : public GameObject
{

public:

	virtual ~HUDCamera() {}

public:

	virtual bool Create()  { return true; }
	virtual void Update(int deltaTime)  {}
	virtual void Draw();
	virtual void Destroy() {}

private:

	Camera m_camera;

};

#endif