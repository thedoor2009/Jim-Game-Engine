#include <assert.h>

#include "DXUT/DXUT.h"

#include "Device/State.h"
#include "Exports/Types.h"
#include "Flow.h"
#include "Rendering/Buffers.h"
#include "Classes/LargeVertexBuffer.h"

// On-The-Fly Rendering

namespace Cheesy
{

bool DrawQuad( const struct Point2D & i_center, float i_width, float i_height, float i_depth, const struct ColorRGB & i_color )
{
	struct QuadVertex
	{
		FLOAT		x, y, z, rhw;
		D3DCOLOR	color;
	} ;

	if( CanSubmit() == false )
		return false;

	assert( g_pD3DDevice );

	LargeVertexBuffer * pDynamicVB = GetDynamicVB();
	assert( pDynamicVB );

	void * pQuadData = NULL;
	unsigned int iQuadBaseIndex = 0;

	if( pDynamicVB->Lock( 4, sizeof( struct QuadVertex ), D3DLOCK_NOOVERWRITE, pQuadData, iQuadBaseIndex ) )
	{
		assert( pQuadData );

		struct QuadVertex * pVerts = reinterpret_cast<struct QuadVertex *>( pQuadData );

		pVerts[0].x = i_center.x - i_width / 2;
		pVerts[0].y = i_center.y - i_height / 2;
		pVerts[0].z = i_depth;
		pVerts[0].rhw = 1.0f;
		pVerts[0].color = D3DCOLOR_RGBA( i_color.r, i_color.g, i_color.b, 0xff );

		pVerts[1].x = i_center.x + i_width / 2;
		pVerts[1].y = i_center.y - i_height / 2;
		pVerts[1].z = i_depth;
		pVerts[1].rhw = 1.0f;
		pVerts[1].color = D3DCOLOR_RGBA( i_color.r, i_color.g, i_color.b, 0xff );

		pVerts[2].x = i_center.x - i_width / 2;
		pVerts[2].y = i_center.y + i_height / 2;
		pVerts[2].z = i_depth;
		pVerts[2].rhw = 1.0f;
		pVerts[2].color = D3DCOLOR_RGBA( i_color.r, i_color.g, i_color.b, 0xff );

		pVerts[3].x = i_center.x + i_width / 2;
		pVerts[3].y = i_center.y + i_height / 2;
		pVerts[3].z = i_depth;
		pVerts[3].rhw = 1.0f;
		pVerts[3].color = D3DCOLOR_RGBA( i_color.r, i_color.g, i_color.b, 0xff );

		pDynamicVB->Unlock( 4 * sizeof( struct QuadVertex ) );

		HRESULT result = D3D_OK;

		result = g_pD3DDevice->SetStreamSource( 0, pDynamicVB->GetDeviceObject(), 0, sizeof( struct QuadVertex ) );
		assert( result == D3D_OK );

		result = g_pD3DDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
		assert( result == D3D_OK );

		result = g_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, iQuadBaseIndex, 2 );
		assert( result == D3D_OK );

		return true;
	}

	return false;
}

} // namespace Cheesy