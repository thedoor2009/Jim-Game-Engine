#include "RenderSprite.h"

namespace JimEngine
{
	void RenderSprite::Draw( const D3DXMATRIX * i_ToWorld, const Cheesy::Material & i_Material ) const
	{
		Actor_Mesh->Draw( i_ToWorld, i_Material );
	}
}
