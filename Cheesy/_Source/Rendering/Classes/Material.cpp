
#include "Exports/Material.h"
#include "ShaderAssembly.h"
#include "Exports/Texture.h"

namespace Cheesy
{

Material::Material( ShaderAssembly * i_pShaderAssembly, Texture ** i_pTextures, unsigned int i_TextureCount ) :
	m_pShaderAssembly( i_pShaderAssembly ),
	m_pTextures( i_pTextures ),
	m_TextureCount( i_TextureCount )
{
	assert( m_pTextures  ||  (i_TextureCount == 0) );
}

Material::~Material()
{
	if( m_pShaderAssembly )
		delete m_pShaderAssembly;

	if( m_pTextures )
	{
		for( unsigned int i = 0; i < m_TextureCount; i++ )
		{
			if( m_pTextures[i] )
				m_pTextures[i]->Release();
		}

		delete [] m_pTextures;
	}
}

bool Material::Activate( void ) const
{
	if( m_pShaderAssembly )
		m_pShaderAssembly->Activate();

	for( unsigned int i = 0; i < m_TextureCount; i++ )
		if( m_pTextures[i] )
			m_pTextures[i]->Activate( i );

	return true;
}

Material * Material::Create( const char * i_pShaderFileName, const char * i_pTextureFilenames[], unsigned int i_TextureCount )
{
	assert( i_pShaderFileName  ||  i_pTextureFilenames );

	ShaderAssembly * pMyAssemply = NULL;
	
	if( i_pShaderFileName )
	{
		pMyAssemply = ShaderAssembly::Create( i_pShaderFileName );
	
		if( pMyAssemply == NULL )
			return NULL;
	}

	Texture ** pMyTextures = NULL;

	if( i_pTextureFilenames )
	{
		pMyTextures = new Texture *[i_TextureCount];

		for( unsigned int i = 0; i < i_TextureCount; i++ )
		{
			if( i_pTextureFilenames[i] )
				pMyTextures[i] = Texture::Create( i_pTextureFilenames[i] );
			else
				pMyTextures[i] = NULL;
		}
	}

	return new Material( pMyAssemply, pMyTextures, i_TextureCount );	
}

} // namespace Cheesy
