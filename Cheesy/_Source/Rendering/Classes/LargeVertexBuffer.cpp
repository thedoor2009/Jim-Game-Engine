#include <assert.h>
#include <vector>

#include "Device/State.h"
#include "Device/ChangeCallback.h"
#include "LargeVertexBuffer.h"

namespace Cheesy
{
LargeVertexBuffer * LargeVertexBuffer::Create( unsigned int i_bytes , DWORD i_usage, DWORD i_optFVF, D3DPOOL i_pool, bool i_autoFlush )
{
	IDirect3DVertexBuffer9 * pNewVB = NULL;

	assert( g_pD3DDevice );

	HRESULT result = g_pD3DDevice->CreateVertexBuffer( i_bytes, i_usage, i_optFVF, i_pool, &pNewVB, NULL );
	
	if( FAILED( result ) || (pNewVB == NULL) )
		return NULL;
		
	D3DVERTEXBUFFER_DESC desc;
	
	result = pNewVB->GetDesc( &desc );
	
	if( FAILED( result ) )
	{
		pNewVB->Release( );
		
		return NULL;
	}
					
	return new LargeVertexBuffer( pNewVB, desc, i_autoFlush );
}

LargeVertexBuffer::LargeVertexBuffer( IDirect3DVertexBuffer9 * i_pVB, D3DVERTEXBUFFER_DESC & i_desc, bool i_autoFlush ) :
	m_pVB( i_pVB ),
	m_Desc( i_desc ),
	m_CurrentOffset( 0 ),
	m_Locked( false ),
	m_LockedBytes( 0 ),
	m_AutoFlush( i_autoFlush )
{
	
}

LargeVertexBuffer::~LargeVertexBuffer( )
{
	if( m_pVB )
		m_pVB->Release( );
}

unsigned int LargeVertexBuffer::CalcNextOffset( unsigned int i_vertexStride ) const
{
	assert( i_vertexStride != 0 );
	
	return ((m_CurrentOffset + (i_vertexStride - 1)) / i_vertexStride) * i_vertexStride;
}
		
bool LargeVertexBuffer::HasSpace( unsigned int i_numVertices, unsigned int i_vertexStride ) const
{
	assert( i_numVertices != 0 );
	assert( i_vertexStride != 0 );
	
	if( ( CalcNextOffset( i_vertexStride ) + (i_numVertices * i_vertexStride) ) < m_Desc.Size )
		return true;
		
	return false;
}

bool LargeVertexBuffer::Flush( void )
{
	m_CurrentOffset = 0;

	return true;
}

bool LargeVertexBuffer::Lock( unsigned int i_numVertices, unsigned int i_vertexStride, DWORD i_LockFlags, void *& i_ptrLockAddr, unsigned int & i_baseVertex )
{
	assert( i_numVertices != 0 );
	assert( i_vertexStride != 0 );
	assert( m_Locked == false );
	
	if( !HasSpace( i_numVertices, i_vertexStride )  &&  m_AutoFlush )
	{
		Flush( );

		if( !HasSpace( i_numVertices, i_vertexStride ) )
			return false;

		i_LockFlags |= D3DLOCK_DISCARD;
	}
	
	unsigned int lockOffset = CalcNextOffset( i_vertexStride );
		
	HRESULT result = m_pVB->Lock( lockOffset, i_numVertices * i_vertexStride, &i_ptrLockAddr, i_LockFlags );
		
	if( FAILED( result ) )
		return false;
			
	m_Locked = true;
	m_LockedBytes = i_numVertices * i_vertexStride;
		
	i_baseVertex = lockOffset / i_vertexStride;
		
	return true;
}

bool LargeVertexBuffer::Unlock( unsigned int i_usedBytes )
{
	assert( m_Locked );
			
	assert( i_usedBytes <= m_LockedBytes );		
		
	HRESULT result = m_pVB->Unlock( );
		
	if( FAILED( result ) )
		return false;
			
	m_Locked = false;
	m_LockedBytes = 0;
		
	m_CurrentOffset += i_usedBytes;
		
	return true;
}

} // namespace Cheesy
