#include "DebugManager.h"
#include "Grid.h"
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//function that displays a 2D or 3D grid on screen based on game setting
//------------------------------------------------------------------------------------------------------
bool Grid::Draw()
{

	//reset model matrix so that grid renders in global world origin position
	GameObject::SetIdentity();

	//send model matrix data to vertex shader 
	GameObject::ApplyMatrix();

#ifdef GAME_3D

		TheDebug::Instance()->DrawGrid3D(25, 1);
		TheDebug::Instance()->DrawCoordSystem3D(25, 5);

#endif

#ifdef GAME_2D
	
		TheDebug::Instance()->DrawGrid2D(50, 1, TheScreen::Instance()->GetPixelsPerUnit());
		TheDebug::Instance()->DrawCoordSystem2D(50, 4, TheScreen::Instance()->GetPixelsPerUnit());
	
#endif

	return true;

}