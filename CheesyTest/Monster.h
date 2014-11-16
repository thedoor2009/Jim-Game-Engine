#ifndef MONSTER_CLASS
#define MONSTER_CLASS
#include "Spirte.h"

class Monster:public JimEngine::Sprite
{
public:

	Monster(void);
	~Monster();
	void Update(float i_deltatime);

};

#endif