#include <assert.h>
#include <stdint.h>
#include <vector>

#include <d3d9.h>

#include "DXUT/DXUT.h"


#include "Device/ChangeCallback.h"
#include "Device/State.h"
#include "Classes/LargeVertexBuffer.h"
#include "Classes/LargeIndexBuffer.h"

namespace Cheesy
{

// fwd declarations
static bool OnDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
static bool OnDeviceDestroyed( void );

// local variables
static LargeVertexBuffer *			s_pDynamicVB = NULL;
static std::vector<LargeVertexBuffer *> *	s_pStaticVBs = NULL;
static std::vector<LargeIndexBuffer *> *	s_pStaticIBs = NULL;

static const ChangeCallback			s_BufferCallbacks( OnDeviceCreated, NULL, NULL, OnDeviceDestroyed );

static bool OnDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc )
{
	if( s_pDynamicVB == NULL )
		s_pDynamicVB = LargeVertexBuffer::Create( 2048, D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, true );

	return s_pDynamicVB != NULL;
}

static bool OnDeviceDestroyed( void )
{
	if( s_pDynamicVB )
	{
		delete s_pDynamicVB;
		s_pDynamicVB = NULL;
	}

	if( s_pStaticVBs )
	{
		{
			std::vector<LargeVertexBuffer *> & StaticVBs = *s_pStaticVBs;

			const unsigned int VBCount = StaticVBs.size();

			for( unsigned int i = 0; i < VBCount; i++ )
			{
				if( StaticVBs[i] )
				{
					delete StaticVBs[i];
					StaticVBs[i] = NULL;
				}
			}

		}

		delete s_pStaticVBs;
		s_pStaticVBs = NULL;
	}

	if( s_pStaticIBs )
	{
		{
			std::vector<LargeIndexBuffer *> & StaticIBs = *s_pStaticIBs;

			const unsigned int IBCount = StaticIBs.size();

			for( unsigned int i = 0; i < IBCount; i++ )
			{
				if( StaticIBs[i] )
				{
					delete StaticIBs[i];
					StaticIBs[i] = NULL;
				}
			}

		}

		delete s_pStaticIBs;
		s_pStaticIBs = NULL;
	}

	return true;
}

LargeVertexBuffer * GetDynamicVB( void )
{
	return s_pDynamicVB;
}

LargeVertexBuffer * GetStaticVB( unsigned int i_numVertices, unsigned int i_strideVertex )
{
	assert( i_numVertices > 0 );
	assert( i_strideVertex > 0 );

	if( s_pStaticVBs == NULL )
		s_pStaticVBs = new std::vector<LargeVertexBuffer *>;

	assert( s_pStaticVBs );

	std::vector<LargeVertexBuffer *> & StaticVBs = *s_pStaticVBs;

	const unsigned int VBCount = StaticVBs.size();

	for( unsigned int i = 0; i < VBCount; i++ )
	{
		if( StaticVBs[i]  &&  StaticVBs[i]->HasSpace( i_numVertices, i_strideVertex ) )
			return StaticVBs[i];
	}

	LargeVertexBuffer * pNewVB = LargeVertexBuffer::Create( 1024 * 1024, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, false );
	assert( pNewVB );

	StaticVBs.push_back( pNewVB );

	return pNewVB;
}

LargeIndexBuffer * GetStaticIB( unsigned int i_numIndices )
{
	assert( i_numIndices > 0 );

	if( s_pStaticIBs == NULL )
		s_pStaticIBs = new std::vector<LargeIndexBuffer *>;

	assert( s_pStaticIBs );

	std::vector<LargeIndexBuffer *> & StaticIBs = *s_pStaticIBs;

	const unsigned int numIBs = StaticIBs.size();

	for( unsigned int i = 0; i < numIBs; i++ )
	{
		if( StaticIBs[i]  &&  StaticIBs[i]->hasSpace( i_numIndices ) )
			return StaticIBs[i];
	}

	LargeIndexBuffer * pNewIB = LargeIndexBuffer::create( i_numIndices, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED );
	assert( pNewIB );

	StaticIBs.push_back( pNewIB );

	return pNewIB;
}

bool AddStaticVertices( void * i_pVertices, unsigned int i_VertexCount, unsigned int i_VertexStride, LargeVertexBuffer * & o_pBuffer, unsigned int & o_BaseIndex )
{
	assert( i_pVertices );
	assert( i_VertexStride > 0 );
	assert( i_VertexCount > 0 );

	o_pBuffer = GetStaticVB( i_VertexCount, i_VertexStride );
	assert( o_pBuffer );

	void * pVertexMem = NULL;
	
	bool success = o_pBuffer->Lock( i_VertexCount, i_VertexStride, 0, pVertexMem, o_BaseIndex );
	assert( success);
	assert( pVertexMem );
	
	memcpy( pVertexMem, i_pVertices, i_VertexCount * i_VertexStride );
	o_pBuffer->Unlock( i_VertexCount * i_VertexStride );	
	return true;
}

bool AddStaticIndices( WORD * i_pIndices, unsigned int i_numIndices, LargeIndexBuffer * & o_pBuffer, unsigned int & o_BaseIndex )
{
	assert( i_pIndices );
	assert( i_numIndices );

	o_pBuffer = GetStaticIB( i_numIndices );
	assert( o_pBuffer );

	void * pIndexMem = NULL;

	bool success = o_pBuffer->Lock( i_numIndices, 0, pIndexMem, o_BaseIndex );
	assert( success == true );
	assert( pIndexMem );
	
	memcpy( pIndexMem, i_pIndices, i_numIndices * sizeof(WORD) );

	o_pBuffer->Unlock( i_numIndices );

	return true;
}

} // namespace Cheesy
