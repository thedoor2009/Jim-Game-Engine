#include "Messaging.h"
#include <utility>

namespace JimEngine
{
	static Messaging* g_Messaging ;
	static std::map< Azra::HashedString, std::vector< IMessageHandler* > > *MessageHandlers;

	Messaging::Messaging()
	{
		g_Messaging = this;
		MessageHandlers = NULL;
	}

	Messaging::~Messaging()
	{

	}

	 Messaging* Messaging::Get_Messaging( void )
	{
		return g_Messaging;
	}

	 void Messaging::Destory( void )
	 {
		 if( g_Messaging )
		 {
			delete g_Messaging;
		 }
	 }

	 void Messaging::Set_MessageHandler( std::map< Azra::HashedString, std::vector< IMessageHandler* >> * i_handler )
	{
		MessageHandlers = i_handler;
	}

	bool Messaging::RegisterMessageHandler( const Azra::HashedString & i_Message, IMessageHandler & i_MessageHandler )
	{
		if( MessageHandlers == NULL )
		{
			std::vector< IMessageHandler* > handler;
			handler.push_back( &i_MessageHandler );

			MessageHandlers = new std::map< Azra::HashedString, std::vector< IMessageHandler* > >();

			MessageHandlers->insert( std::map<Azra::HashedString, std::vector< IMessageHandler* >>::value_type(i_Message, handler));
			return true;
		}

		map< Azra::HashedString, std::vector< IMessageHandler* >>::iterator it;
		int message_id =  i_Message.Get();
		it = MessageHandlers->find( i_Message );
		if( it != MessageHandlers->end() )
		{
			it->second.push_back( &i_MessageHandler );
		}
		else
		{
			std::vector< IMessageHandler* > handler;
			handler.push_back( &i_MessageHandler );

			MessageHandlers->insert( std::make_pair(i_Message, handler));
		}
		return true;
	}

	bool Messaging::UnregisterMessageHandler( const Azra::HashedString & i_Message, IMessageHandler & i_MessageHandler )
	{
		map< Azra::HashedString, std::vector< IMessageHandler* >>::iterator it;
		it = MessageHandlers->find( i_Message );
		if( it == MessageHandlers->end() )
		{
			return false;
		}
		else
		{
			if( it->second.size() != 0 )
			{
				it->second.pop_back();
			}
			else
			{
				MessageHandlers->erase( it );
			}
			
			return true;
		}
	}

	bool Messaging::SendtheMessage( const Azra::HashedString & i_Message, Ptr::SharePtr <Sprite> & i_MessageObject )
	{
		map< Azra::HashedString, std::vector< IMessageHandler* >>::iterator it;
		it = MessageHandlers->find( i_Message );
		if( it == MessageHandlers->end() )
		{
			return false;
		}
		else
		{
			it->second.at(0)->ProcessMessage( i_Message, i_MessageObject );
			return true;
		}
	}

	bool Messaging::SendtheMessage( const Azra::HashedString & i_Message, Ptr::SharePtr <Sprite> & i_MessageObject, Ptr::SharePtr <Sprite> & i_MessageObject_other )
	{
		map< Azra::HashedString, std::vector< IMessageHandler* >>::iterator it;
		it = MessageHandlers->find( i_Message );
		if( it == MessageHandlers->end() )
		{
			return false;
		}
		else
		{
			it->second.at(0)->ProcessMessages( i_Message, i_MessageObject, i_MessageObject_other );
			return true;
		}
	}

	void Messaging::Destroy_MessageHandlers( void )
	{
		map< Azra::HashedString, std::vector< IMessageHandler* >>::iterator it = MessageHandlers->begin();
		for( it; it != MessageHandlers->end(); it++)
		{
			if( it->second.size() != 0 )
			{
				return;
			}
		}
		it = MessageHandlers->begin();
		delete MessageHandlers;
	}
}