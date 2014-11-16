#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H
#include "SpriteController.h"

class MonsterController:public JimEngine::SpriteController
{
public:
	void UpdateCoordination( JimEngine::Sprite & i_Sprite,float i_deltatime, bool o_IsDone, JimEngine::Sprite & i_Target);
};

#endif