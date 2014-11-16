#ifndef GAME_H
#define GAME_H

#include "World.h"
#include "Render.h"
#include "Collision.h"
#include <d3d9.h>

namespace JimEngine
{
	class Game
	{
	public:
		Game(void){ }
		virtual void Init(int i_num){}

		~Game(void)
		{
			Destroy();
		}

		void Destroy(void)
		{
			m_gameWorld.Destory();
			m_gameRender.Destory();
			m_gameCollision.Destory();
		}
		bool Input(int i_num);
		void Update(float i_deltatime);
		void Draw(void);

		World Get_World(void);
		Render Get_Render(void);
		Collision Get_Collision(void);

		Render m_gameRender;
		World m_gameWorld;
		Collision m_gameCollision;

	};
}
#endif