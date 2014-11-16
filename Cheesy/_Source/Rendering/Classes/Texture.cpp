#include <assert.h>

#include "DXUT/DXUT.h"

#include "Device/State.h"
#include "Exports/Texture.h"

namespace Cheesy
{

Texture::Texture( IDirect3DTexture9 * i_pData ) :
	m_pData( i_pData )
{
	assert( i_pData );
}

Texture::~Texture()
{
	assert( m_pData );

	ULONG useCount = m_pData->Release();
	assert( useCount == 0 );
}

void Texture::Activate( unsigned int i_Stage ) const
{
	assert( g_pD3DDevice );

	HRESULT result = g_pD3DDevice->SetTexture( i_Stage, m_pData );
	assert( result == D3D_OK );
}

Texture * Texture::Create( const char * i_pTextureFilename )
{
	assert( i_pTextureFilename );
	assert( g_pD3DDevice );

	const unsigned int lengthFilename = 256;
	WCHAR	Filename[lengthFilename];

	int res = MultiByteToWideChar( CP_UTF8, 0, i_pTextureFilename, strlen( i_pTextureFilename ), Filename, lengthFilename );
	assert( res > 0 );
	Filename[res] = 0;

	IDirect3DTexture9 * pNewTexture = NULL;

	HRESULT result = D3DXCreateTextureFromFile( g_pD3DDevice, Filename, &pNewTexture );

	if( result == D3D_OK )
		return new Texture( pNewTexture );

	return NULL;
}

Texture * Texture::Create( void * i_pData, unsigned int i_DataSizeB )
{
	assert( i_pData );
	assert( i_DataSizeB > 0 );

	assert( g_pD3DDevice );

	IDirect3DTexture9 * pNewTexture = NULL;
	
	HRESULT result = D3DXCreateTextureFromFileInMemory( g_pD3DDevice, i_pData, i_DataSizeB, &pNewTexture );

	if( result == D3D_OK )
		return new Texture( pNewTexture );
	
	return NULL;
}

} // namespace Cheesy