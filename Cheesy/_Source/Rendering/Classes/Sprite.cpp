#include <assert.h>

#include "DXUT/DXUT.h"

#include "Device/State.h"
#include "Exports/Sprite.h"
#include "Exports/Texture.h"
#include "Exports/Types.h"
#include "Flow.h"
#include "LargeVertexBuffer.h"
#include "Rendering/Buffers.h"


namespace Cheesy
{
// fwd declarations

// Colored Vertex
struct SpriteVertexPC
{
	FLOAT		x, y, z;
	D3DCOLOR	color;
} ;

static const unsigned int SpriteVertexPCSizeB = sizeof( struct SpriteVertexPC );

// Colored Textured Vertex
struct SpriteVertexPCT
{
	FLOAT		x, y, z;
	D3DCOLOR	color;
	FLOAT		u, v;
} ;

static const unsigned int SpriteVertexPCTSizeB = sizeof( struct SpriteVertexPCT );

void BuildVertices( SpriteVertexPC * i_pSpriteVerts, const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color );
void BuildVertices( SpriteVertexPCT * i_pSpriteVerts, const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color, const UVSet & i_UVs );

Sprite::Sprite( LargeVertexBuffer * i_pVB, unsigned int i_VBStartVertex, Texture * i_pTexture ) :
	m_pVB( i_pVB ),
	m_VBStartVertex( i_VBStartVertex ),
	m_pTexture( i_pTexture )
{
	assert( i_pVB );

	if( m_pTexture )
		m_pTexture->Acquire();
}

Sprite::~Sprite()
{
	if( m_pTexture )
		m_pTexture->Release();
}

bool Sprite::Draw( const Point2D & i_Offset, float i_RotationDegrees ) const
{
	assert( g_pD3DDevice );
	assert( CanSubmit() );

	HRESULT result = g_pD3DDevice->SetStreamSource( 0, m_pVB->GetDeviceObject(), 0, m_pTexture ? SpriteVertexPCTSizeB : SpriteVertexPCSizeB );
	assert( result == D3D_OK );

	if( m_pTexture )
	{
		m_pTexture->Activate( 0 );
		result = g_pD3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	}
	else
		result = g_pD3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );

	assert( result == D3D_OK );

	D3DXMATRIX Rotation;
	D3DXMatrixRotationZ( &Rotation, (i_RotationDegrees * 3.14159265359f) / 180.0f   );

	D3DXMATRIX Translation;
	D3DXMatrixTranslation( &Translation, i_Offset.x, i_Offset.y, 0.0f );

	D3DXMATRIX Final;
	D3DXMatrixMultiply( &Final, &Rotation, &Translation );

	g_pD3DDevice->SetTransform( D3DTS_WORLD, &Final );

	// Enable alpha blending.
	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	g_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	g_pD3DDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1,   D3DTA_TEXTURE );

	result = g_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, m_VBStartVertex, 2 );
	assert( result == D3D_OK );

	return true;
}

Sprite * Sprite::Create( const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color )
{	
	unsigned int VertexSize = SpriteVertexPCSizeB;

	LargeVertexBuffer * pVB = GetStaticVB( 4, VertexSize );
	assert( pVB );

	void * pVBMem;
	unsigned int SpriteBaseVertex;

	bool LockSuccess = pVB->Lock( 4, VertexSize, D3DLOCK_NOOVERWRITE, pVBMem, SpriteBaseVertex );
	assert( LockSuccess );

	BuildVertices( reinterpret_cast<SpriteVertexPC *>( pVBMem ), i_Center, i_Depth, i_Dimensions, i_Color );

	pVB->Unlock( VertexSize * 4 );

	return new Sprite( pVB, SpriteBaseVertex, NULL );
}

Sprite * Sprite::Create( const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color, Texture & i_Texture, const UVSet & i_UVs )
{	
	unsigned int VertexSize = SpriteVertexPCTSizeB;

	LargeVertexBuffer * pVB = GetStaticVB( 4, VertexSize );
	assert( pVB );

	void * pVBMem;
	unsigned int SpriteBaseVertex;

	bool LockSuccess = pVB->Lock( 4, VertexSize, 0, pVBMem, SpriteBaseVertex );
	assert( LockSuccess );

	BuildVertices( reinterpret_cast<SpriteVertexPCT *>( pVBMem ), i_Center, i_Depth, i_Dimensions, i_Color, i_UVs );

	pVB->Unlock( VertexSize * 4 );

	return new Sprite( pVB, SpriteBaseVertex, &i_Texture );
}

void BuildVertices( SpriteVertexPCT * i_pSpriteVerts, const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color, const UVSet & i_UVs )
{
	// 0 (Upper Left)
	i_pSpriteVerts[0].x = i_Center.x - (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[0].y = i_Center.y + (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[0].z = i_Depth;

	i_pSpriteVerts[0].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	i_pSpriteVerts[0].u = i_UVs[0].u;
	i_pSpriteVerts[0].v = i_UVs[0].v;

	// 1 (Upper Right)
	i_pSpriteVerts[1].x = i_Center.x + (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[1].y = i_Center.y + (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[1].z = i_Depth;

	i_pSpriteVerts[1].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	i_pSpriteVerts[1].u = i_UVs[1].u;
	i_pSpriteVerts[1].v = i_UVs[1].v;

	// 2 (Lower Left)
	i_pSpriteVerts[2].x = i_Center.x - (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[2].y = i_Center.y - (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[2].z = i_Depth;

	i_pSpriteVerts[2].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	i_pSpriteVerts[2].u = i_UVs[2].u;
	i_pSpriteVerts[2].v = i_UVs[2].v;

	// 3 (Lower Right)
	i_pSpriteVerts[3].x = i_Center.x + (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[3].y = i_Center.y - (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[3].z = i_Depth;

	i_pSpriteVerts[3].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	i_pSpriteVerts[3].u = i_UVs[3].u;
	i_pSpriteVerts[3].v = i_UVs[3].v;
}

void BuildVertices( SpriteVertexPC * i_pSpriteVerts, const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color )
{
	// 0
	i_pSpriteVerts[0].x = i_Center.x + (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[0].y = i_Center.y - (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[0].z = i_Depth;

	i_pSpriteVerts[0].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	// 1
	i_pSpriteVerts[1].x = i_Center.x + (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[1].y = i_Center.y + (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[1].z = i_Depth;

	i_pSpriteVerts[1].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	// 2
	i_pSpriteVerts[2].x = i_Center.x - (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[2].y = i_Center.y - (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[2].z = i_Depth;

	i_pSpriteVerts[2].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	// 3
	i_pSpriteVerts[3].x = i_Center.x - (i_Dimensions.x / 2.0f );
	i_pSpriteVerts[3].y = i_Center.y + (i_Dimensions.y / 2.0f );
	i_pSpriteVerts[3].z = i_Depth;

	i_pSpriteVerts[3].color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );
}
} // namespace Cheesy
