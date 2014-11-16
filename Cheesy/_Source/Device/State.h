#ifndef __STATE_H
#define __STATE_H

#include "DXUT/DXUT.h"

#define D3D_FAILBUTRETURN(result)	\
	if( result != D3D_OK )			\
	{								\
		g_LastD3DError = result;	\
		return false;				\
	}								\

namespace Cheesy
{
	extern IDirect3DDevice9 *	g_pD3DDevice;
	extern HRESULT				g_LastD3DError;

	extern bool					g_bDebugVS;
	extern bool					g_bDebugPS;

} // namespace Cheesy

#endif // __STATE_H