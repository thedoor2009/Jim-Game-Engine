#include "CollisionSystem.h"
#include "Messaging.h"
#include <Text.h>

CollisionSystem::CollisionSystem()
{
	JimEngine::Messaging::Get_Messaging()->RegisterMessageHandler( "ReleaseMonster", *this );
	JimEngine::Messaging::Get_Messaging()->RegisterMessageHandler( "ReleaseLove", *this );
	JimEngine::Messaging::Get_Messaging()->RegisterMessageHandler( "GamePaused", *this );
	JimEngine::Messaging::Get_Messaging()->RegisterMessageHandler( "BounceBack", *this );
	JimEngine::Messaging::Get_Messaging()->RegisterMessageHandler( "Trigger", *this );
}
	
void CollisionSystem::ProcessMessage( const Azra::HashedString & i_Message, JimEngine::Ptr::SharePtr <JimEngine::Sprite> & i_MessageObject )
{
	if( i_Message == "ReleaseMonster" )
	{
		if (i_MessageObject->Get_CollisionInfo().m_CollisionID == 0x02 )
		{
			i_MessageObject->Set_Death();
		}
	}

	else if( i_Message == "ReleaseLove" )
	{
		if (i_MessageObject->Get_CollisionInfo().m_CollisionID == 0x08 )
		{
			i_MessageObject->Set_Death();
		}
	}

	else if ( i_Message == "Trigger" )
	{
		if (i_MessageObject->Get_CollisionInfo().m_CollisionID == 0x02 )
		{
			i_MessageObject->Set_Angle( 0.0f );
		}
	}	
}

void CollisionSystem::ProcessMessages( const Azra::HashedString & i_Message, JimEngine::Ptr::SharePtr <JimEngine::Sprite> & i_MessageObject, JimEngine::Ptr::SharePtr <JimEngine::Sprite> & i_MessageObject_other )
{
	if(  i_Message == "BounceBack" )
	{
		JimEngine::Coordination a_velocity( i_MessageObject->Get_Acceleration().Cor_GetX(), i_MessageObject->Get_Acceleration().Cor_GetY(), 0.0f );
		JimEngine::Coordination b_velocity(  i_MessageObject_other->Get_Acceleration().Cor_GetX(), i_MessageObject_other->Get_Acceleration().Cor_GetY(), 0.0f );

		i_MessageObject->Set_Velocity( b_velocity );
		i_MessageObject_other->Set_Velocity( a_velocity );
	}
}

CollisionSystem::~CollisionSystem()
{
	JimEngine::Messaging::Get_Messaging()->UnregisterMessageHandler( "ReleaseMonster", *this );
	JimEngine::Messaging::Get_Messaging()->UnregisterMessageHandler( "ReleaseLove", *this );
	JimEngine::Messaging::Get_Messaging()->UnregisterMessageHandler( "GamePaused", *this );
	JimEngine::Messaging::Get_Messaging()->UnregisterMessageHandler( "BounceBack", *this );
	JimEngine::Messaging::Get_Messaging()->UnregisterMessageHandler( "Trigger", *this );
	JimEngine::Messaging::Get_Messaging()->Destroy_MessageHandlers();
}
