#include <assert.h>
#include "HashedString.h"

namespace Azra
{

inline HashedString::HashedString( ) :
	m_Hash( Hash( "" ) )
{
}

inline HashedString::HashedString( const char * i_string ) :
	m_Hash( Hash( i_string ) )
#ifdef DEBUG_KEEP_STRING
	, m_String( i_string )
#endif
{
}

inline HashedString::HashedString( const HashedString & i_other ) :
m_Hash( i_other.m_Hash )
#ifdef DEBUG_KEEP_STRING
	, m_String( i_other.m_String )
#endif
{
}

inline HashedString & HashedString::operator=( const HashedString & i_other )
{
	m_Hash = i_other.m_Hash;

#ifdef DEBUG_KEEP_STRING
	m_String = i_other.m_String;
#endif

	return *this;
}

inline unsigned int HashedString::Get( void ) const
{
	return m_Hash;
}

inline bool HashedString::operator==( const HashedString & i_other ) const
{
	return m_Hash == i_other.m_Hash;
}

inline bool  HashedString::operator <( const HashedString & i_other) const
{
	if( this->m_Hash < i_other.m_Hash )
		return true;
	else
		return false;
}

} // namespace Azra
