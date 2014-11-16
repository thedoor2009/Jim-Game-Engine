#ifndef __MATERIAL_H
#define __MATERIAL_H

namespace Cheesy
{
class ShaderAssembly;
class Texture;

class Material
{
public:
	static Material * Create( const char * i_pShaderFileName, const char ** i_pTextureFilenames, unsigned int i_TextureCount );
	~Material();

	bool Activate( void ) const;

private:
	ShaderAssembly * m_pShaderAssembly;
	Texture **		 m_pTextures;
	unsigned int	 m_TextureCount;

	Material( ShaderAssembly * i_pShaderAssembly, Texture ** i_pTextures, unsigned int i_TextureCount );
};

} // namespace Cheesy

#endif // __MATERIAL_H