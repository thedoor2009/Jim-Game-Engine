#ifndef FREEZE_CONTROLLER_H
#define FREEZE_CONTROLLER_H
#include "SpriteController.h"

class FreezeController:public  JimEngine::SpriteController
{
	public:
		void UpdateCoordination( JimEngine::Sprite &i_Sprtie )
		{
			i_Sprtie.Set_Velocity( JimEngine::Coordination( 1.0f, 0.0f, 0.0f ) );
			i_Sprtie.Set_Acceleration( JimEngine::Coordination( 0.0f, 0.0f, 0.0f ) );
		}
};

#endif
