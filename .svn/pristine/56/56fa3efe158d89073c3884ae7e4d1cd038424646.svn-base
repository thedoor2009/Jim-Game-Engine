#include <assert.h>

#include "DXUT/DXUT.h"

#include "Device/ChangeCallback.h"
#include "Exports/Text.h"
#include "Exports/Types.h"
#include "Flow.h"


namespace Cheesy {
namespace Text {

// fwd declarations
bool OnDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
bool OnDeviceLost( void );
bool OnDeviceReset( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
bool OnDeviceDestroyed( void );

// local variables
static bool						s_bRenderingText = false;
static unsigned int				s_StringsRendered = 0;

static const unsigned int		s_FontNameWCHARLen = 128;
static wchar_t					s_FontName[s_FontNameWCHARLen] = { L"Arial" };
static unsigned int				s_FontHeight = 16;

static ID3DXFont *				s_pFont = NULL;
static ID3DXSprite *			s_pFontSprite = NULL;

static const ChangeCallback		s_TextCallbacks( OnDeviceCreated, OnDeviceLost, OnDeviceReset, OnDeviceDestroyed );

void SetFontInfo( const char * i_pFontName, unsigned int i_FontHeight )
{
	assert( i_pFontName != NULL );
	assert( i_FontHeight > 0 );

	s_FontHeight = i_FontHeight;

	MultiByteToWideChar( CP_ACP, 0, i_pFontName, -1, s_FontName, s_FontNameWCHARLen );
}

bool OnDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc )
{
	assert( i_pD3DDevice != NULL );

	if( s_pFont == NULL )
	{
		HRESULT result = D3DXCreateFont( i_pD3DDevice, 25, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
							DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, s_FontName, &s_pFont );
		assert( result == D3D_OK );
	}

	if( s_pFontSprite == NULL )
	{
		HRESULT result = D3DXCreateSprite( i_pD3DDevice, &s_pFontSprite );
		assert( result == D3D_OK );
	}

	return true;
}

bool OnDeviceLost( void )
{
	if( s_pFont != NULL )
		s_pFont->OnLostDevice();

	return true;
}

bool OnDeviceReset( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc )
{
	if( s_pFont )
		return s_pFont->OnResetDevice() == D3D_OK;

	if( s_pFontSprite )
		return s_pFontSprite->OnResetDevice() == D3D_OK;

	return true;
}

bool OnDeviceDestroyed( void )
{
	if( s_pFont )
	{
		s_pFont->Release();
		s_pFont = NULL;
	}

	if( s_pFontSprite )
	{
		s_pFontSprite->Release();
		s_pFontSprite = NULL;
	}

	return true;
}

bool BeginText( void )
{
	assert( s_pFontSprite != NULL );
	assert( CanSubmit() );
	
	if( s_bRenderingText == false )
	{
		HRESULT result = s_pFontSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );
		assert( result == D3D_OK );

		s_bRenderingText = true;
		s_StringsRendered = 0;
	}

	return true;
}

bool DrawText( const char * i_pText, const Point2D & i_UpperLeft, const Point2D & i_LowerRight, const ColorRGBA & i_Color )
{
	assert( i_pText != NULL );
	assert( s_pFont != NULL );
	assert( s_pFontSprite != NULL );
	assert( s_bRenderingText );

	RECT	TextRect = { static_cast<long>( i_UpperLeft.x ), static_cast<long>( i_UpperLeft.y ), static_cast<long>( i_LowerRight.x ), static_cast<long>( i_LowerRight.y ) };
	D3DCOLOR Color = D3DCOLOR_RGBA( i_Color.r, i_Color.g, i_Color.b, i_Color.a );

	HRESULT result = s_pFont->DrawTextA( s_pFontSprite, i_pText, -1, &TextRect, DT_CENTER | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE, Color );
	assert( result != 0 );

	s_StringsRendered++;

	return true;
}

bool EndText( void )
{
	assert( s_pFontSprite != NULL );

	if( s_bRenderingText )
	{
		HRESULT result = s_pFontSprite->End();
		assert( result == D3D_OK );

		s_bRenderingText = false;
	}

	return true;
}

} // namespace Text
} // namespace Cheesy