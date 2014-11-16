#ifndef __FLOW_H
#define __FLOW_H
 
#include <d3dx9.h>
#include "Types.h"

namespace Cheesy
{
	void CreateProjection( float i_YFOV, float i_ZNear, float i_ZFar );
	void CreateCamera( const D3DXVECTOR3 & i_Eye, const D3DXVECTOR3 & i_LookAt, const D3DXVECTOR3 & i_Up  );

	bool BeginFrame( const ColorRGBA & i_FrameClearColor );

	bool Begin3D( void );
	bool Begin2D( void );

	bool EndFrame( void );

} // namespace Cheesy

#endif // __FLOW_H
