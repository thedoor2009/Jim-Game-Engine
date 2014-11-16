#include <assert.h>

#include "ChangeCallback.h"

namespace Cheesy
{

ChangeCallback * s_pRoot = NULL;

ChangeCallback::ChangeCallback( ChangeCallback::OnDeviceCreated i_pfOnCreated, ChangeCallback::OnDeviceLost i_pfOnLost, ChangeCallback::OnDeviceReset i_pfOnReset, ChangeCallback::OnDeviceDestroyed i_pfOnDestroyed ) :
	m_pfOnCreated( i_pfOnCreated ),
	m_pfOnLost( i_pfOnLost ),
	m_pfOnReset( i_pfOnReset ),
	m_pfOnDestroyed( i_pfOnDestroyed ),
	m_pNext( s_pRoot )
{
	s_pRoot = this;
}

bool ChangeCallback::HandleDeviceCreated( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc )
{
	ChangeCallback * pCurrent = s_pRoot;

	while( pCurrent )
	{
		if( pCurrent->m_pfOnCreated )
		{
			if( pCurrent->m_pfOnCreated( i_pD3DDevice, i_pBackBufferSurfaceDesc ) == false )
				return false;
		}

		pCurrent = pCurrent->m_pNext;
	}

	return true;
}

bool ChangeCallback::HandleDeviceLost( void )
{
	ChangeCallback * pCurrent = s_pRoot;

	while( pCurrent )
	{
		if( pCurrent->m_pfOnLost )
			pCurrent->m_pfOnLost();

		pCurrent = pCurrent->m_pNext;
	}

	return true;
}

bool ChangeCallback::HandleDeviceReset( IDirect3DDevice9 * i_pD3DDevice, const D3DSURFACE_DESC * i_pBackBufferSurfaceDesc )
{
	ChangeCallback * pCurrent = s_pRoot;

	while( pCurrent )
	{
		if( pCurrent->m_pfOnReset )
		{
			if( pCurrent->m_pfOnReset( i_pD3DDevice, i_pBackBufferSurfaceDesc ) == false )
				return false;
		}

		pCurrent = pCurrent->m_pNext;
	}

	return true;
}

bool ChangeCallback::HandleDeviceDestroyed( void )
{
	ChangeCallback * pCurrent = s_pRoot;

	while( pCurrent )
	{
		if( pCurrent->m_pfOnDestroyed )
			pCurrent->m_pfOnDestroyed();

		pCurrent = pCurrent->m_pNext;
	}

	return true;
}

} // namespace Cheesy