#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Spirte.h"
#include "SharedPtr.h"

#include <assert.h>
#include <stdint.h>

#include "luaplus\LuaPlus.h"

namespace JimEngine
{
	class World
	{
	public:
		World(void)
		{
			
		}
		~World(void)
		{
			
		}
		void Destory(void)
		{
			
			for( unsigned int i = 0; i < m_WorldSpriteArray.size(); i++ )
			{
				m_WorldSpriteArray.erase(m_WorldSpriteArray.begin() + i );
			}
		}

		void isMarkDeath(void);
		bool Input( const int i_num );
		void Update (const float i_deltatime );
		void Add( JimEngine::Ptr::SharePtr<JimEngine::Sprite> i_sprite );
		static Ptr::SharePtr<Sprite> Create( const char *i_pSpriteName, float i_maxVelocity );
		static Ptr::SharePtr<Sprite> Create( void );

	private:
		std::vector<JimEngine::Ptr::SharePtr<JimEngine::Sprite>> m_WorldSpriteArray;
	};
}

#endif