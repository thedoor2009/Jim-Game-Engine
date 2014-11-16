#ifndef __NAMED_BIT_SET_H
#define __NAMED_BIT_SET_H

#include "HashedString.h"

namespace Azra
{

template<typename T>
class NamedBitSet
{
	static const unsigned int NumBits = sizeof(T) * 8; // num bytes * 8 bits / byte
	
	HashedString m_BitNames[NumBits];

public:
	unsigned int GetBitIndex( const HashedString & i_Name );
	bool FindBitIndex( const HashedString & i_Name, unsigned & i_BitIndex );

	T GetBitMask( const HashedString & i_Name );
	bool FindBitMask( const HashedString & i_Name, T & i_BitMask );
} ;

} // namespace Azra

#include "NamedBitSet.inl"

#endif // __NAMED_BIT_SET_H