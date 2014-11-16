//#ifndef _TRIGGERBOX_COLLISION_HANDLER_H
//#define _TRIGGERBOX_COLLISION_HANDLER_H
//
//#include "CollisionInfo.h "
//#include "Spirte.h"
//
//class TriggerBoxCollisionHandler: public JimEngine::CollisionInfo::CollisionCallbackInterface
//{
//public:
//
//	void HandleCollision( JimEngine::Sprite & i_Me,  JimEngine::CollisionInfo::_CollisionInfo & i_Collision )
//	{
//	    if( ( i_Me.Get_CollisionInfo().collidableInfo.m_CollisionID & i_Collision.m_pCollisionObject.Get_Pointer()->Get_CollisionInfo().collidableInfo.m_CollisionSet ) != 0 )
//		{
//			// When the player collide with the triggerbox, its angle would be changed to be 0.
//			//i_Collision.m_pCollisionObject->Set_Angle( 0.0f );
//		}
//	}
//};
//
//#endif