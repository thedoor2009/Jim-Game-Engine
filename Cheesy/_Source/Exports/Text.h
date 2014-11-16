#ifndef __TEXT_H
#define __TEXT_H

#include "Types.h"

namespace Cheesy
{
namespace Text
{
	void SetTextInfo( const char * i_pFontName, unsigned int i_FontHeight );

	bool BeginText( void );
	bool DrawText( const char * i_pText, const Point2D & i_UpperLeft, const Point2D & i_LowerRight, const ColorRGBA & i_Color );
	bool EndText( void );

} // namespace Text
} // namespace Cheesy

#endif // __TEXT_H