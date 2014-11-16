#include "World.h"

namespace JimEngine
{
	bool World::Input(const int i_num)
	{
		for(int unsigned i = 0; i < m_WorldSpriteArray.size();i++)
		{
			bool iQuit;
			iQuit = m_WorldSpriteArray.at(i)->Input(i_num);
			if(iQuit == true)
			{
				return true;
			}
			if( m_WorldSpriteArray.at(1)->Get_Death() == true )
			{
				return true;
			}
		}
		return false;
	}

	void World::Update(const float i_deltatime){

		for(unsigned int i = 2; i < m_WorldSpriteArray.size();i++)
		{
			if( m_WorldSpriteArray.at(i)->Get_Renderable() )
			{
				
				if( m_WorldSpriteArray.at(1)->Get_CollisionInfo().m_CollisionID == 0x08 )
				{
					m_WorldSpriteArray.at(i)->Update( i_deltatime,*m_WorldSpriteArray.at(1).Get_Pointer() );
				}
			}
		}
		if( m_WorldSpriteArray.at(0)->Get_CollisionInfo().m_CollisionID == 0x01 )
		{
			m_WorldSpriteArray.at(0)->Update( i_deltatime,*m_WorldSpriteArray.at(0).Get_Pointer() );
			m_WorldSpriteArray.at(1)->Update( i_deltatime,*m_WorldSpriteArray.at(0).Get_Pointer() );
		}
		isMarkDeath();
	}

	void World::Add(JimEngine::Ptr::SharePtr<JimEngine::Sprite> i_sprite)
	{
		m_WorldSpriteArray.push_back(i_sprite);
	}

	void World::isMarkDeath(void)
	{
		for(unsigned int i = 0; i < m_WorldSpriteArray.size(); i++)
		{
			if(m_WorldSpriteArray.at(i)->Get_Death())
			{
				m_WorldSpriteArray.erase(m_WorldSpriteArray.begin() + i);
			}
		}
	}

	Ptr::SharePtr<Sprite> World::Create(const char *i_pSpriteName, float i_maxVelocity)
	{
		Ptr::SharePtr<Sprite> Ptr(new Sprite(i_pSpriteName,i_maxVelocity));
		return Ptr;
	}

	Ptr::SharePtr<Sprite> World::Create( void )
	{
		Ptr::SharePtr<Sprite> Ptr(new Sprite() );
		return Ptr;
	}
}