#ifndef __LARGE_INDEX_BUFFER_H
#define __LARGE_INDEX_BUFFER_H

#include <d3d9.h>

namespace Cheesy
{
class LargeIndexBuffer
{
	IDirect3DIndexBuffer9 *		m_pIB;
	D3DINDEXBUFFER_DESC 		m_Desc;
	
	unsigned int				m_CurrentOffset;
	
	bool						m_Locked;
	unsigned int				m_LockedBytes;
	
	LargeIndexBuffer( IDirect3DIndexBuffer9 * p_IB, D3DINDEXBUFFER_DESC & _desc );

	LargeIndexBuffer & operator=( const LargeIndexBuffer & i_other );

	public:
		~LargeIndexBuffer( );

		static LargeIndexBuffer * create( unsigned int i_numIndices, DWORD i_usage, D3DFORMAT i_format, D3DPOOL i_pool );
	
		bool hasSpace( unsigned int i_numIndices ) const;

		bool Lock( unsigned int i_numIndices, DWORD i_LockFlags, void * & i_pLockAddr, unsigned int & i_baseIndex );
		bool Unlock( unsigned int i_usedIndices );

		IDirect3DIndexBuffer9 * getDeviceObject( void ) { return m_pIB; }
	
	} ;
}

#endif
