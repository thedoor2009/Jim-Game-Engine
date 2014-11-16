#ifndef RENDERSPRITE_H
#define RENDERSPRITE_H

#include "..\Cheesy\_Source\Exports\Sprite.h"
#include "..\Cheesy\_Source\Exports\Material.h"
#include "..\Cheesy\_Source\Exports\Mesh.h"
#include <cstddef>

namespace JimEngine
{
	class RenderSprite
	{
	public:
		RenderSprite(void){}
		~RenderSprite(void)
		{
			if(Actor_Pointer != NULL)
			{
				delete Actor_Pointer;
			}

			if(Actor_Material != NULL)
			{
				delete Actor_Material;
			}

			if(Actor_Mesh != NULL)
			{
				delete Actor_Mesh;
			}
		}
		
		void Draw( const D3DXMATRIX * i_ToWorld, const Cheesy::Material & i_Material ) const;

		Cheesy::Sprite		*Actor_Pointer;
		Cheesy::Material	*Actor_Material;
		Cheesy::Mesh		*Actor_Mesh;
	};

}
#endif