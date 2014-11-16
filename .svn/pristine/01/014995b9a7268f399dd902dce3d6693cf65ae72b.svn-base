#ifndef __HASHED_STRING_H
#define __HASHED_STRING_H

#include <string>

namespace Azra
{
	
class HashedString
{
#ifdef DEBUG_KEEP_STRING
	std::string  m_String;
#endif
	unsigned int m_Hash;

public:
	HashedString();
	HashedString( const char * i_string );
	HashedString( const HashedString & i_other );
	HashedString & operator=( const HashedString & i_other );

	unsigned int Get() const;

	bool operator==( const HashedString & i_other ) const;
	bool operator <( const HashedString & i_other) const; 
	
	static unsigned int Hash( const char * i_string );
	static unsigned int Hash( const void * i_bytes, unsigned int i_count );

} ;

}

#include "HashedString.inl"

#endif // __HASHED_STRING_H