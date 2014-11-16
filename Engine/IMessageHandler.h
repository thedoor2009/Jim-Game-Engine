#ifndef _IMESSAGE_HANDLER_H
#define _IMESSAGE_HANDLER_H
#include "HashedString.h"
#include "SharedPtr.h"
#include "Spirte.h"

namespace JimEngine
{
	class IMessageHandler
	{
	public:
		virtual  ~IMessageHandler()
		{
		}
		virtual void ProcessMessage( const Azra::HashedString & i_Message, Ptr::SharePtr <Sprite> & i_MessageObject ) = 0;
		virtual void ProcessMessages( const Azra::HashedString & i_Message, Ptr::SharePtr <Sprite> & i_MessageObject, Ptr::SharePtr <Sprite> & i_MessageObject_other ) = 0;
	};
}
#endif