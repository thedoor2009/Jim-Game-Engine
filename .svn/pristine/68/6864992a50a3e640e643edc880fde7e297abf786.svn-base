#include <assert.h>
#include <vector>

#include "DXUT/DXUT.h"

#include "Exports/Types.h"
#include "Exports/Flow.h"

#include "Device/State.h"
#include "Device/ChangeCallback.h"
#include "Rendering/Classes/LargeVertexBuffer.h"
#include "Rendering/Classes/ShaderAssembly.h"

namespace Cheesy
{
// fwd declarations
static bool OnDeviceCreatedOrReset( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );

// local variables
static bool					s_bDeviceAvailable = false;
static bool					s_bInFrame = false;

static float				s_DisplayWidth;
static float				s_DisplayHeight;

static D3DXMATRIX			s_Camera;
static D3DXMATRIX			s_OrthoProjection;
static D3DXMATRIX			s_PerspProjection;

D3DXMATRIX					s_Identity;

static const ChangeCallback	s_FlowCallbacks( OnDeviceCreatedOrReset, NULL, OnDeviceCreatedOrReset, NULL );

static bool OnDeviceCreatedOrReset( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc )
{
	assert( i_pD3DDevice != NULL );
	assert( i_pBackBufferSurfaceDesc != NULL );

	g_pD3DDevice = i_pD3DDevice;

	s_bDeviceAvailable = true;

	s_DisplayWidth = float( i_pBackBufferSurfaceDesc->Width );
	s_DisplayHeight = float( i_pBackBufferSurfaceDesc->Height );

	D3DXMatrixOrthoLH( &s_OrthoProjection, s_DisplayWidth, s_DisplayHeight, 0.0f, 1.0f );

	D3DXMatrixIdentity( &s_Identity );

	return true;
}

void CreateProjection( float i_YFOV, float i_ZNear, float i_ZFar )
{
	assert( s_DisplayHeight > 0.0f );
	assert( s_DisplayWidth > 0.0f );

	float aspect = s_DisplayWidth / s_DisplayHeight;

	D3DXMatrixPerspectiveFovLH( &ShaderAssembly::s_Proj, i_YFOV, aspect, i_ZNear, i_ZFar );

}

void CreateCamera( const D3DXVECTOR3 & i_Eye, const D3DXVECTOR3 & i_LookAt, const D3DXVECTOR3 & i_Up  )
{
	D3DXMatrixLookAtLH( &ShaderAssembly::s_View, &i_Eye, &i_LookAt, &i_Up );

}
bool BeginFrame( const ColorRGBA & i_ClearColor )
{
	assert( s_bDeviceAvailable == true );

	if( g_pD3DDevice )
	{
		// Clear the render target and the zbuffer 
		HRESULT result = g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( i_ClearColor.r, i_ClearColor.g, i_ClearColor.b, i_ClearColor.a ), 1.0f, 0 );
		D3D_FAILBUTRETURN( result );

		// Begin Scene
		result = g_pD3DDevice->BeginScene();
		D3D_FAILBUTRETURN( result );

		s_bDeviceAvailable = true;
	}

	s_bInFrame = true;

	return true;
}

bool CanSubmit( void )
{
	return s_bDeviceAvailable && s_bInFrame;
}

bool Begin2D( void )
{
	if( CanSubmit() )
	{
		assert( g_pD3DDevice );

		g_pD3DDevice->SetTransform( D3DTS_PROJECTION, &s_OrthoProjection );
		g_pD3DDevice->SetTransform( D3DTS_VIEW, &s_Identity );

		return true;
	}

	return false;
}

bool Begin3D( void )
{
	if( CanSubmit() )
	{
		assert( g_pD3DDevice );

		g_pD3DDevice->SetTransform( D3DTS_PROJECTION, &s_PerspProjection );
		g_pD3DDevice->SetTransform( D3DTS_VIEW, &s_Camera );
		return true;
	}

	return false;
}

bool EndFrame( void )
{
	assert( s_bDeviceAvailable == true );

	if( s_bInFrame )
	{
		assert( g_pD3DDevice );

		HRESULT result = g_pD3DDevice->EndScene();
		D3D_FAILBUTRETURN( result );

		result = g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
		D3D_FAILBUTRETURN( result );

		s_bInFrame = false;
	}

	return true;
}

} // namespace Cheesy