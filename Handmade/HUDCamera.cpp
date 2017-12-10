#include "HUDCamera.h"
#include "InputManager.h"
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//function that resets and applies a simple identity matrix
//------------------------------------------------------------------------------------------------------
void HUDCamera::Draw()
{

	Camera::SetIdentity();
	Camera::SendToShader();

}