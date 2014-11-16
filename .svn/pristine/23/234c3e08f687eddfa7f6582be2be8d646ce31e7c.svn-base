#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <d3d9.h>

#include "Flow.h"
#include "Device/State.h"
#include "Exports/Material.h"
#include "Exports/MeshData.h"
#include "Exports/Mesh.h"
#include "Rendering/Buffers.h"

#include "LargeIndexBuffer.h"
#include "LargeVertexBuffer.h"
#include "ShaderAssembly.h"

namespace Cheesy
{

Mesh::Mesh(  LargeVertexBuffer * i_pVB, IDirect3DVertexDeclaration9 * i_pVBDecl, UINT i_VBStride, LargeIndexBuffer * i_pIB, const struct _DrawInfo & i_DrawInfo ) :
	m_pVB( i_pVB ),
	m_pVBDecl( i_pVBDecl ),
	m_VBStride( i_VBStride ),
	m_pIB( i_pIB ),
	m_DrawInfo( i_DrawInfo )
{
	assert( i_pVB );
	assert( i_pVBDecl );

}

static ULONG UseCount;

Mesh::~Mesh()
{
	if( m_pVBDecl )
	{
		UseCount = m_pVBDecl->Release();
	}
}

void Mesh::Draw( const D3DXMATRIX * i_ToWorld, const Material & i_Material ) const
{
	ShaderAssembly::s_pWorld = i_ToWorld;

	i_Material.Activate();
	
	Activate();
}

void Mesh::Activate( void ) const
{
	assert( g_pD3DDevice );
	assert( CanSubmit() );

	HRESULT result = g_pD3DDevice->SetStreamSource( 0, m_pVB->GetDeviceObject(), 0, m_VBStride );
	assert( result == D3D_OK );

	result = g_pD3DDevice->SetVertexDeclaration( m_pVBDecl );
	assert( result == D3D_OK );
	
	if( m_pIB )
	{
		result = g_pD3DDevice->SetIndices( m_pIB->getDeviceObject() );
		assert( result == D3D_OK );

		result = g_pD3DDevice->DrawIndexedPrimitive( m_DrawInfo.m_PrimType, m_DrawInfo.m_BaseVertexIndex, m_DrawInfo.m_MinIndex, m_DrawInfo.m_NumVertices, m_DrawInfo.m_StartIndex, m_DrawInfo.m_PrimCount );
		assert( result == D3D_OK );
	}
	else
	{
		result = g_pD3DDevice->SetIndices( NULL );
		assert( result == D3D_OK );

		result = g_pD3DDevice->DrawPrimitive( m_DrawInfo.m_PrimType, m_DrawInfo.m_BaseVertexIndex, m_DrawInfo.m_PrimCount );
		assert( result == D3D_OK );
	}
}

Mesh * Mesh::Create( const struct _MeshData & i_MeshData )
{
	assert( i_MeshData.m_pVertices );
	assert( i_MeshData.m_VertexCount );
	assert( i_MeshData.m_VertexStride );

	LargeVertexBuffer * pVB = NULL;
	LargeIndexBuffer *	pIB = NULL;

	struct _DrawInfo	DrawInfo;

	unsigned int		BaseVertex;

	bool success = AddStaticVertices( i_MeshData.m_pVertices, i_MeshData.m_VertexCount, i_MeshData.m_VertexStride, pVB, BaseVertex );

	if( success == false )
		return false;

	DrawInfo.m_BaseVertexIndex = BaseVertex;
	DrawInfo.m_NumVertices = i_MeshData.m_VertexCount;

	if( i_MeshData.m_pIndices )
	{
		unsigned int BaseIndex;

		assert( i_MeshData.m_IndexCount );
		bool success = AddStaticIndices( i_MeshData.m_pIndices, i_MeshData.m_IndexCount, pIB, BaseIndex );

		if( success == false )
			return false;

		DrawInfo.m_StartIndex = BaseIndex;

		DrawInfo.m_MinIndex = UINT32_MAX;

		for( unsigned int i = 0; i < i_MeshData.m_IndexCount; i++ )
			if( i_MeshData.m_pIndices[i] < DrawInfo.m_MinIndex )
				DrawInfo.m_MinIndex = i_MeshData.m_pIndices[i];
	}

	switch ( i_MeshData.m_PrimType )
	{
	case D3DPT_TRIANGLELIST:
		if( i_MeshData.m_pIndices )
		{
			assert( (i_MeshData.m_IndexCount % 3) == 0 );
			DrawInfo.m_PrimCount = i_MeshData.m_IndexCount / 3;
		} else {
			assert( (i_MeshData.m_VertexCount % 3) );
			DrawInfo.m_PrimCount = i_MeshData.m_VertexCount / 3;
		}
		break;
	case D3DPT_TRIANGLESTRIP:
		if( i_MeshData.m_pIndices )
		{
			assert( i_MeshData.m_IndexCount >= 3 );
			DrawInfo.m_PrimCount = i_MeshData.m_IndexCount - 2;
		} else {
			assert( i_MeshData.m_VertexCount >= 3 );
			DrawInfo.m_PrimCount = i_MeshData.m_VertexCount - 2;
		}
		break;
	default:
		assert( false );
		break;
	}

	DrawInfo.m_PrimType = i_MeshData.m_PrimType;

	IDirect3DVertexDeclaration9 * pDecl = NULL;

	HRESULT result = g_pD3DDevice->CreateVertexDeclaration( i_MeshData.m_VertexDecl, & pDecl );
	D3D_FAILBUTRETURN( result );

	return new Mesh( pVB, pDecl, i_MeshData.m_VertexStride, pIB, DrawInfo );
}

} // namespace Cheesy