#ifndef _COLLISION_SYSTEM_H
#define _COLLISION_SYSTEM_H

#include "HashedString.h"

#include "SharedPtr.h"
#include "Spirte.h"
#include "IMessageHandler.h"


	class CollisionSystem: public JimEngine::IMessageHandler
	{
	public:
		CollisionSystem();
		~CollisionSystem();
		void ProcessMessage( const Azra::HashedString & i_Message, JimEngine::Ptr::SharePtr <JimEngine::Sprite> & i_MessageObject );
		void ProcessMessages( const Azra::HashedString & i_Message, JimEngine::Ptr::SharePtr <JimEngine::Sprite> & i_MessageObject, JimEngine::Ptr::SharePtr <JimEngine::Sprite> & i_MessageObject_other );
	};

#endif