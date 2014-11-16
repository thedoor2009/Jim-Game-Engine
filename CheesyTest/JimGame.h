#ifndef JIMGAME_H
#define JIMGAME_H

#include "Game.h"
#include "HumanController.h"
#include "MonsterController.h"
#include "FreezeController.h"

#include "Random.h"

#include "..\Cheesy\_Source\Exports\Sprite.h"
#include "..\Cheesy\_Source\Exports\Material.h"
#include "..\Cheesy\_Source\Exports\MeshData.h"
#include <Types.h>
#include <Texture.h>

class JimGame:public JimEngine::Game
{
public:
	JimGame(void){}
	void Init(int i_num);

	Cheesy::Texture * CreateTextureFromFile( const char * i_pTextureFilename );

};

#endif