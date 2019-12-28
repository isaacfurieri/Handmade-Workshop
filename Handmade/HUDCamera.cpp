#include "HUDCamera.h"
#include "Input.h"
#include "Screen.h"

//------------------------------------------------------------------------------------------------------
//function that resets and applies a simple identity matrix
//------------------------------------------------------------------------------------------------------
void HUDCamera::Draw()
{

	Camera::SetIdentity();
	Camera::SendToShader();

}