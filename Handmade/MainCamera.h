#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H

#include "Camera.h"
#include "GameObject.h"

class MainCamera : public GameObject
{

public:

	MainCamera();
	virtual ~MainCamera() {}

public:

	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {}

private :

	Camera m_camera;

};

#endif