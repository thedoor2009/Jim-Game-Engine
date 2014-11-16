#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "IReferenceCounted.h"


namespace Cheesy
{

class Texture : public IReferenceCounted
{
public:
	static Texture * Create( void * i_pData, unsigned int i_DataSizeB );
	static Texture * Create( const char * i_pTextureFilename );

	void Activate( unsigned int i_Stage ) const;

private:
	IDirect3DTexture9 *	m_pData;

	Texture( IDirect3DTexture9 * i_pData );
	~Texture();

};

} // namespace Cheesy

#endif // __TEXTURE_H