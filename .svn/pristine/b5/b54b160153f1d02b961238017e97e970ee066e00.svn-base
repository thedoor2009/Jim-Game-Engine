#ifndef __DC_CALLBACK_H
#define __DC_CALLBACK_H

#include "DXUT/DXUT.h"

namespace Cheesy
{

class ChangeCallback
{

public:
	typedef bool (*OnDeviceCreated)( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
	typedef bool (*OnDeviceLost)( void );
	typedef bool (*OnDeviceReset)( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
	typedef bool (*OnDeviceDestroyed)( void );

private:
	class ChangeCallback * m_pNext;

	OnDeviceCreated		m_pfOnCreated;
	OnDeviceLost		m_pfOnLost;
	OnDeviceReset		m_pfOnReset;
	OnDeviceDestroyed	m_pfOnDestroyed;

public:
	ChangeCallback( OnDeviceCreated i_pfOnCreated, OnDeviceLost i_pfOnLost, OnDeviceReset i_pfnOnReset, OnDeviceDestroyed i_pfnOnDestroyed );

	static bool HandleDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
	static bool HandleDeviceLost();
	static bool HandleDeviceReset( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc );
	static bool HandleDeviceDestroyed();

} ;

} // namespace Cheesy

#endif // __DC_CALLBACK_H