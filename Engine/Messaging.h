#ifndef _IMESSAGING_H
#define _IMESSAGEING_H

#include <map>
#include <vector>
#include "HashedString.h"
#include "SharedPtr.h"
#include "Spirte.h"
#include "IMessageHandler.h"

namespace JimEngine
{
	class Messaging
	{
	public:
	
		friend class IMessageHandler;

		Messaging();
		~Messaging();
		static void init();

		 bool RegisterMessageHandler( const Azra::HashedString & i_Message, IMessageHandler & i_MessageHandler );
		 bool UnregisterMessageHandler( const Azra::HashedString & i_Message, IMessageHandler & i_MessageHandler );

		 bool SendtheMessage( const Azra::HashedString & i_Message, Ptr::SharePtr <Sprite> & i_MessageObject ); 
		 bool SendtheMessage( const Azra::HashedString & i_Message, Ptr::SharePtr <Sprite> & i_MessageObject, Ptr::SharePtr <Sprite> & i_MessageObject_other ); 

		 void Set_MessageHandler(std::map< Azra::HashedString, std::vector< IMessageHandler* >> * i_handler );

		 void Destroy_MessageHandlers( void );

		static Messaging* Get_Messaging( void );
		static void Destory( void );
	private:
	};
}
#endif