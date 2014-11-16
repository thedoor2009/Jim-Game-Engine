namespace Azra
{

template<typename T>
bool NamedBitSet<T>::FindBitIndex( const HashedString & i_Name, unsigned int & i_BitIndex )
{
	// see if i_Name exists in set
	for( unsigned int i = 0; i < NumBits; i++ )
		if( m_BitNames == i_Name )
		{
			i_BitIndex = i;

			return true;
		}

	return false;
}

template<typename T>
unsigned int NamedBitSet<T>::GetBitIndex( const HashedString & i_Name )
{
	// see if i_Name exists in set
	for( unsigned int i = 0; i < NumBits; i++ )
		if( m_BitNames[i] == i_Name )
			return i;

	// if not find an empty slot
	HashedString	Empty;

	for( unsigned int i = 0; i < NumBits; i++ )
		if( m_BitNames[i] == Empty )
		{
			m_BitNames[i] = i_Name;
			return i;
		}

		// out of bits == bad
		assert( false );

		return 0;
}

template<typename T>
bool NamedBitSet<T>::FindBitMask( const HashedString & i_Name, T & i_BitMask )
{
	unsigned int i_BitIndex = 0;

	if( FindBitIndex( i_Name, i_BitIndex ) == true )
	{
		i_BitMask = 1 << GetBitIndex( i_Name );

		return true;
	}

	return false;
}

template<typename T>
T NamedBitSet<T>::GetBitMask( const HashedString & i_Name )
{
	return 1 << GetBitIndex( i_Name );
}

} // namespace Azra