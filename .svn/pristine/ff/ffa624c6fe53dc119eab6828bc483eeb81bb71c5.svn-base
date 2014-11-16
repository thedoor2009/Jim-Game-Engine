#ifndef _COLLISION_H
#define _COLLISION_H

#include "AABBox.h"
#include <vector>
#include "SharedPtr.h"

namespace JimEngine
{
	class Collision
	{
	public:
		Collision( void )
		{
		}

		~Collision( void )
		{
		}

		void Destory(void)
		{
			for( unsigned int i = 0; i < m_CollisionSpriteArray.size(); i++ ) 
			{
				m_CollisionSpriteArray.erase(m_CollisionSpriteArray.begin() + i );
			}
		}

		bool CollisionDetect(   AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA,  AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RatationB );
		bool SwapCollision( AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA,  AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RatationB );
		bool AABBCollision( AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA,  AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RatationB );

		void isMarkDeath( void );
		void Update( void );
		void Add( JimEngine::Ptr::SharePtr< JimEngine::Sprite > i_collider );

	private:
		std::vector<JimEngine::Ptr::SharePtr<JimEngine::Sprite>> m_CollisionSpriteArray;
	};
}
#endif
