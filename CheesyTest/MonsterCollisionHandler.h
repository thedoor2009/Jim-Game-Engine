//#ifndef _MONSTER_COLLISION_HANDLER_H
//#define _MONSTER_COLLISION_HANDLER_H
//
//#include <iostream>
//#include "CollisionInfo.h "
//#include "Spirte.h"
//#include "Messaging.h"
//
//class MonsterCollisionHandler: public JimEngine::CollisionInfo::CollisionCallbackInterface
//{
//public:
//
//	void HandleCollision( JimEngine::Sprite & i_Me, JimEngine::CollisionInfo::_CollisionInfo & i_Collision )
//	{
//		using namespace JimEngine;
//		
//		// Once the monster collide with 
//		if( ( i_Me.Get_CollisionInfo().collidableInfo.m_CollisionID & i_Collision.m_pCollisionObject->Get_CollisionInfo().collidableInfo.m_CollisionSet ) != 0 )
//		{
//			i_Me.Set_Velocity( JimEngine::Coordination( -i_Me.Acc_Get().Cor_GetX(),-i_Me.Acc_Get().Cor_GetY(), 0.0f ) );
//		}
//	}
//};
//
//#endif