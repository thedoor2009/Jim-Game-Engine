#ifndef __SPRITE_H
#define __SPRITE_H

#include "Types.h"

namespace Cheesy
{

class Texture;
class LargeVertexBuffer;

class Sprite
{

	LargeVertexBuffer *			m_pVB;
	unsigned int				m_VBStartVertex;

	Texture *					m_pTexture;

	Sprite( LargeVertexBuffer * i_pVB, unsigned int i_VBStartVertex, Texture * i_pTexture );
public:
	~Sprite();

	bool Draw( const Point2D & i_Offset, float i_RotationDegrees = 0.0f ) const;

	static Sprite * Create( const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color );
	static Sprite * Create( const Point2D & i_Center, float i_Depth, const Point2D & i_Dimensions, const ColorRGBA & i_Color, Texture & i_pTexture, const UVSet & i_UVs );
} ;



} // namespace Cheesy


#endif // __SPRITE_H