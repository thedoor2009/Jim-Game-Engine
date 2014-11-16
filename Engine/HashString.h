#ifndef _HASH_STRING_H
#define _HASH_STRING_H

namespace JimEngine{
class HashString
{
	int m_ID;
	char * m_Str;

public:
	HashString( );
	HashString( const char* i_Str )
	{
		m_Str = const_cast<char *>(i_Str);
		Hash();
	}

	void Hash( void )
	{
		int h = 0;
		while( *m_Str )
			h = h << 1 ^ *m_Str ++;
		m_ID = h;
	}

	int Get_ID( void )
	{
		return m_ID;
	}
};
}
#endif