#include <assert.h>

#include "Device/State.h"
#include "LargeIndexBuffer.h"

namespace Cheesy
{

LargeIndexBuffer * LargeIndexBuffer::create( unsigned int _numIndices, DWORD _usage, D3DFORMAT _format, D3DPOOL _pool )
{
	assert( g_pD3DDevice != NULL );

	IDirect3DIndexBuffer9 * pNewIB = NULL;

	unsigned int bytesPerIndex = (_format == D3DFMT_INDEX32) ? 4 : 2;

	HRESULT result = g_pD3DDevice->CreateIndexBuffer( _numIndices * bytesPerIndex, _usage, _format, _pool, &pNewIB, NULL );
	
	if( FAILED( result ) || (pNewIB == NULL) )
		return NULL;
		
	D3DINDEXBUFFER_DESC desc;
	
	result = pNewIB->GetDesc( &desc );
	
	if( FAILED( result ) )
	{
		pNewIB->Release( );
		
		return NULL;
	}
					
	return new LargeIndexBuffer( pNewIB, desc );
}

LargeIndexBuffer::LargeIndexBuffer( IDirect3DIndexBuffer9 * i_pIB, D3DINDEXBUFFER_DESC & i_desc ) :
	m_pIB( i_pIB ),
	m_Desc( i_desc ),
	m_CurrentOffset( 0 ),
	m_Locked( false ),
	m_LockedBytes( 0 )
{
	assert( i_pIB );
}

LargeIndexBuffer::~LargeIndexBuffer( )
{
	assert( m_pIB );
	m_pIB->Release( );
}

bool LargeIndexBuffer::hasSpace( unsigned int i_numIndices ) const
{
	assert( i_numIndices != 0 );

	unsigned int bytesPerIndex = (m_Desc.Format == D3DFMT_INDEX32) ? 4 : 2;

	if( (m_CurrentOffset + (i_numIndices * bytesPerIndex)) <= m_Desc.Size )
		return true;

	return false;
}
		
bool LargeIndexBuffer::Lock( unsigned int i_numIndices, DWORD i_LockFlags, void * & i_pLockAddr, unsigned int & i_baseIndex )
{
	assert( i_numIndices != 0 );
	assert( m_Locked == false );
	
	if( !hasSpace( i_numIndices ) )
		return NULL;
		
	unsigned int bytesPerIndex = (m_Desc.Format == D3DFMT_INDEX32) ? 4 : 2;

	assert( (m_CurrentOffset % bytesPerIndex) == 0 );

	assert( m_pIB );
	HRESULT result = m_pIB->Lock( m_CurrentOffset, i_numIndices * bytesPerIndex, &i_pLockAddr, i_LockFlags );
		
		if( FAILED( result ) )
			return false;
			
	m_Locked = true;
	m_LockedBytes = i_numIndices * bytesPerIndex;
		
	i_baseIndex = m_CurrentOffset / bytesPerIndex;
		
	return true;
}

bool LargeIndexBuffer::Unlock( unsigned int i_usedBytes )
{
	assert( m_Locked );		
	assert( i_usedBytes <= m_LockedBytes );		

	assert( m_pIB );
	HRESULT result = m_pIB->Unlock( );
		
	if( FAILED( result ) )
		return false;
			
	m_Locked = false;
	m_LockedBytes = 0;
		
	m_CurrentOffset += i_usedBytes;
		
	return true;
}		

} // namespace Renderer