#include "DXUT/DXUT.h"

#include "Device/ChangeCallback.h"
#include "Exports/Keyboard.h"

namespace Cheesy {

namespace Keyboard {

// fwd declarations
static bool OnDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
static void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );

// local variables
enum KeyState
{
	DOWN,
	UP,
	UNKNOWN
} ;

const ChangeCallback	s_KeyboardCallbacks( OnDeviceCreated, NULL, NULL, NULL );

const unsigned int	NUM_KEYS = 255;

KeyState			KeyStates[NUM_KEYS];

KeyStateCallback	KeyDownCallback = NULL;
KeyStateCallback	KeyPressCallback = NULL;


static bool OnDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc )
{
	for( unsigned int i = 0; i < NUM_KEYS; i++ )
		KeyStates[i] = UNKNOWN;

	DXUTSetCallbackKeyboard( OnKeyboard );

	return true;
}

//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
	if( (bKeyDown == true)  &&  (KeyStates[nChar] != DOWN) )
	{
		KeyStates[nChar] = DOWN;

		if( KeyDownCallback != NULL )
			KeyDownCallback( nChar );

#ifdef SHOW_KEY_STATES
		char buffer[256];
		sprintf_s( buffer, sizeof( buffer ), "C: %d KD: %d AD: %d UC: %08x\n", nChar, bKeyDown, bAltDown, pUserContext );
		OutputDebugStringA( buffer );
#endif // SHOW_KEY_STATES

	}
	else if( (bKeyDown == false)  &&  (KeyStates[nChar] != UP) )
	{
		KeyStates[nChar] = UP;

		if( KeyPressCallback != NULL )
			KeyPressCallback( nChar );

#ifdef SHOW_KEY_STATES
		char buffer[256];
		sprintf_s( buffer, sizeof( buffer ), "C: %d KD: %d AD: %d UC: %08x\n", nChar, bKeyDown, bAltDown, pUserContext );

		OutputDebugStringA( buffer );
#endif // SHOW_KEY_STATES
	}

}

} // namespace Keyboard

void SetKeyDownCallback( KeyStateCallback i_Callback )
{
	Keyboard::KeyDownCallback = i_Callback;
}

void SetKeyPressCallback( KeyStateCallback i_Callback )
{
	Keyboard::KeyPressCallback = i_Callback;
}

} // namespace Cheesy