//--------------------------------------------------------------------------------------
// Cheesy Renderer
//
// Copyright (c) JoeCorp. All rights reserved.
//--------------------------------------------------------------------------------------
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include <assert.h>
#include <stdlib.h>

#include "DXUT/DXUT.h"
#include "DXUT/DXUTmisc.h"

#include "Device/ChangeCallback.h"

#include "Device/State.h"

namespace Cheesy
{

//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext );
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
void CALLBACK OnD3D9LostDevice( void* pUserContext );
void CALLBACK OnD3D9DestroyDevice( void* pUserContext );

//--------------------------------------------------------------------------------------
// Local Variables 
//--------------------------------------------------------------------------------------

bool Create( const char * i_pAppName, unsigned int i_WindowWidth, unsigned int i_WindowHeight, bool i_DebugVS, bool i_DebugPS )
{
    // DXUT will create and use the best device (either D3D9 or D3D10) 
    // that is available on the system depending on which D3D callbacks are set below

    // Set DXUT callbacks
    DXUTSetCallbackDeviceChanging( Cheesy::ModifyDeviceSettings );

    DXUTSetCallbackD3D9DeviceAcceptable( Cheesy::IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( Cheesy::OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( Cheesy::OnD3D9ResetDevice );
    DXUTSetCallbackD3D9DeviceLost( Cheesy::OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( Cheesy::OnD3D9DestroyDevice );

	HRESULT result = S_OK;

    result = DXUTInit( true, true, NULL ); // Parse the command line, show message boxes on error, no extra command line params
	if( result != S_OK )
		return false;

    DXUTSetCursorSettings( false, false );

	const char * pAppName = (i_pAppName != NULL) ? i_pAppName : "Cheesy Render";

	const unsigned int NameWCHARLen = 128;
	wchar_t	wcAppName[NameWCHARLen];
	MultiByteToWideChar( CP_ACP, 0, pAppName, -1, wcAppName, NameWCHARLen );

	result = DXUTCreateWindow( wcAppName );
	if( result != S_OK )
		return false;

    result = DXUTCreateDevice( true, i_WindowWidth, i_WindowHeight );

	g_bDebugVS = i_DebugVS;
	g_bDebugPS = i_DebugPS;

	IDirect3DDevice9 * pD3DDevice = DXUTGetD3D9Device();
	assert( pD3DDevice );

	IDirect3DSurface9 * pBBSurface = NULL;
	result = pD3DDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBBSurface );
	assert( result == D3D_OK );
	assert( pBBSurface != NULL );

	D3DSURFACE_DESC	BBDesc;

	result = pBBSurface->GetDesc( &BBDesc );
	assert( result == D3D_OK );

	pBBSurface->Release();

	return ChangeCallback::HandleDeviceCreated( pD3DDevice, &BBDesc );

}

bool Service( bool & o_bQuitRequested )
{
	o_bQuitRequested = false;

    HWND hWnd = DXUTGetHWND();
    BOOL bGotMsg = FALSE;
    
	do
	{
		MSG  msg;
		msg.message = WM_NULL;
		bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );

		if( bGotMsg )
		{
			if( TranslateAccelerator( hWnd, NULL, &msg ) == 0 )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}

			if( msg.message == WM_QUIT )
				o_bQuitRequested = true;
		}
	} while( (bGotMsg == TRUE)  &&  (o_bQuitRequested == false) );

	return true;
}

void Shutdown( void )
{
	ChangeCallback::HandleDeviceDestroyed();

	DXUTDestroyState();
}

int GetExitCode( void )
{
	return DXUTGetExitCode();
}

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    // Skip backbuffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    // No fallback defined by this app, so reject any device that 
    // doesn't support at least ps2.0
    if( pCaps->PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Called right before creating a D3D9 or D3D10 device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    if( pDeviceSettings->ver == DXUT_D3D9_DEVICE )
    {
        IDirect3D9* pD3D = DXUTGetD3D9Object();
        D3DCAPS9 Caps;
        pD3D->GetDeviceCaps( pDeviceSettings->d3d9.AdapterOrdinal, pDeviceSettings->d3d9.DeviceType, &Caps );

        // If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW 
        // then switch to SWVP.
        if( ( Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) == 0 || Caps.VertexShaderVersion < D3DVS_VERSION( 1, 1 ) )
        {
            pDeviceSettings->d3d9.BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        }

        // Debugging vertex shaders requires either REF or software vertex processing 
        // and debugging pixel shaders requires REF.  
		if( g_bDebugVS )
		{
			if( pDeviceSettings->d3d9.DeviceType != D3DDEVTYPE_REF )
			{
				pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
				pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_PUREDEVICE;
				pDeviceSettings->d3d9.BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			}
		}

		if( g_bDebugPS )
	        pDeviceSettings->d3d9.DeviceType = D3DDEVTYPE_REF;
    }

    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pD3DDevice, const D3DSURFACE_DESC * pBackBufferSurfaceDesc, void * pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pD3DDevice, const D3DSURFACE_DESC * pBackBufferSurfaceDesc, void * pUserContext )
{
	bool bResult = ChangeCallback::HandleDeviceReset( pD3DDevice, pBackBufferSurfaceDesc );

	return bResult == true ? S_OK : GetLastError();
}

//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
	ChangeCallback::HandleDeviceLost();
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
}

} ;