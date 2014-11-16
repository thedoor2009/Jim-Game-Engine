#ifndef __SHADER_ASSEMBLY_H
#define __SHADER_ASSEMBLY_H

#include <d3d9.h>
#include <d3dx9.h>

namespace Cheesy
{

class ShaderAssembly
{
public:
	static const D3DXMATRIX *		s_pWorld;
	static D3DXMATRIXA16			s_View;
	static D3DXMATRIXA16			s_Proj;

	static ShaderAssembly * Create( const char * i_pShaderFileName );
	static ShaderAssembly * Create( void * i_pShaderData, unsigned int i_ShaderDataSizeB );

	~ShaderAssembly();
	bool Activate( void ) const;

private:
	IDirect3DVertexShader9 *	m_pVS;
	ID3DXConstantTable *		m_pVSConsts;

	IDirect3DPixelShader9 *		m_pPS;
	ID3DXConstantTable *		m_pPSConsts;

	ShaderAssembly( IDirect3DVertexShader9 * i_pVS, ID3DXConstantTable * i_pVSConsts, IDirect3DPixelShader9 * i_pPS, ID3DXConstantTable * i_pPSConsts );

};

} // namespace Cheesy

#endif // __SHADER_ASSEMBLY_H