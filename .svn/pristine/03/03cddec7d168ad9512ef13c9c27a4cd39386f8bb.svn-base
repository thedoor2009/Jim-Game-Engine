#ifndef __LARGE_VERTEX_BUFFER_H
#define __LARGE_VERTEX_BUFFER_H

#include "DXUT/DXUT.h"

namespace Cheesy
{

class LargeVertexBuffer
{
	IDirect3DVertexBuffer9 *	m_pVB;
	D3DVERTEXBUFFER_DESC 		m_Desc;

	unsigned int				m_CurrentOffset;
	
	unsigned int				m_LockedBytes;
	bool						m_Locked;
	bool						m_AutoFlush;
		
	LargeVertexBuffer( IDirect3DVertexBuffer9 * i_pVB, D3DVERTEXBUFFER_DESC & i_desc, bool i_autoFlush = true );

	LargeVertexBuffer( const LargeVertexBuffer & i_other );
	LargeVertexBuffer & operator=( const LargeVertexBuffer & i_other );

	unsigned int CalcNextOffset( unsigned int i_vertexStride ) const;
	
public:
	~LargeVertexBuffer( );

	static LargeVertexBuffer * Create( unsigned int i_bytes, DWORD i_usage, DWORD i_optFVF, D3DPOOL i_pool, bool i_autoFlush = true );
	
	bool Flush( void );
	bool HasSpace( unsigned int i_numVertices, unsigned int i_vertexStride ) const;
	
	bool Lock( unsigned int i_numVertices, unsigned int i_vertexStride, DWORD i_LockFlags, void * & i_pLockAddr, unsigned int & i_baseVertex );
	bool Unlock( unsigned int i_usedBytes );

	IDirect3DVertexBuffer9 * GetDeviceObject() { return m_pVB; }	
} ;

} // namespace Cheesy
#endif
