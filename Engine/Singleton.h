#ifndef _SLINGLETON_H
#define _SLINGLETON_H

#include<memory>

template< class T >
class Singleton
{
	static Singleton< T* > m_singleton;
	Singleton();
	~Singleton()
	{
		FreeInstance();
	}

public:
	static Singleton< T* > GetInstance()
	{
		if( m_singleton == NULL )
		{
			m_singleton = new Singleton< T* >;
		}
		return m_singleton;
	}
	static void FreeInstance()
	{
		delete m_singleton;
		m_singleton = NULL;
	}
};

#endif
