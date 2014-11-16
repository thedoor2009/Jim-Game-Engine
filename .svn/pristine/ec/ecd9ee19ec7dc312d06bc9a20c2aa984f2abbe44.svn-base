
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#include "Device/State.h"
#include "Flow.h"
#include "ShaderAssembly.h"

namespace Cheesy
{
// dirty hack
extern D3DXMATRIX	s_Identity;

const D3DXMATRIX *		ShaderAssembly::s_pWorld;
D3DXMATRIXA16			ShaderAssembly::s_View;
D3DXMATRIXA16			ShaderAssembly::s_Proj;

ShaderAssembly::ShaderAssembly( IDirect3DVertexShader9 * i_pVS, ID3DXConstantTable * i_pVSConsts, IDirect3DPixelShader9 * i_pPS, ID3DXConstantTable * i_pPSConsts ) :
	m_pVS( i_pVS ),
	m_pVSConsts( i_pVSConsts ),
	m_pPS( i_pPS ),
	m_pPSConsts( i_pPSConsts )
{
	assert( m_pVS || m_pPS );
}

ShaderAssembly::~ShaderAssembly( )
{
	if( m_pVS )
	{
		ULONG UseCount = m_pVS->Release();
	}

	if( m_pVSConsts )
		m_pVSConsts->Release();

	if( m_pPS )
		m_pPS->Release();

	if( m_pPSConsts )
		m_pPSConsts->Release();

}

bool ShaderAssembly::Activate( void ) const
{
	assert( g_pD3DDevice );
	assert( CanSubmit() );

	const D3DXMATRIX * pWorld = s_pWorld ? s_pWorld : &s_Identity;

	D3DXMATRIXA16 WorldViewProj = (*pWorld) * s_View * s_Proj;

	HRESULT result = m_pVSConsts->SetMatrix( g_pD3DDevice, "mWorldViewProj", &WorldViewProj );
	assert( result == D3D_OK );

	result = g_pD3DDevice->SetVertexShader( m_pVS );
	assert( result == D3D_OK );

	result = g_pD3DDevice->SetPixelShader( m_pPS );
	assert( result == D3D_OK );

	return true;
}


ShaderAssembly * ShaderAssembly::Create( void * i_pShaderData, unsigned int i_ShaderDataSizeB )
{
	assert( i_pShaderData );
	assert( i_ShaderDataSizeB );

	ID3DXBuffer * pVSCode = NULL;
	ID3DXConstantTable * pVSConstants = NULL;

	DWORD VSCompileFlags = g_bDebugVS ? D3DXSHADER_SKIPOPTIMIZATION | D3DXSHADER_DEBUG : 0;

	HRESULT result = D3D_OK;
#ifdef _DEBUG
	ID3DXBuffer * pErrorBuffer = NULL;

	result = D3DXCompileShader( reinterpret_cast<LPCSTR>( i_pShaderData ), i_ShaderDataSizeB, NULL, NULL, "mainVS", "vs_2_0", VSCompileFlags, &pVSCode, &pErrorBuffer, &pVSConstants );
#else
	result = D3DXCompileShader( reinterpret_cast<LPCSTR>( i_pShaderData ), i_ShaderDataSizeB, NULL, NULL, "mainVS", "vs_2_0", VSCompileFlags, &pVSCode, NULL, &pVSConstants );
#endif
	const WCHAR * pErrorString = DXGetErrorDescription( result );
	D3D_FAILBUTRETURN( result );

	IDirect3DVertexShader9 * pVS = NULL;
	result = g_pD3DDevice->CreateVertexShader( reinterpret_cast<DWORD *>( pVSCode->GetBufferPointer() ), &pVS );

	pVSCode->Release();
	D3D_FAILBUTRETURN( result );

	ID3DXBuffer * pPSCode = NULL;
	ID3DXConstantTable * pPSConstants = NULL;

	DWORD PSCompileFlags = g_bDebugVS ? D3DXSHADER_SKIPOPTIMIZATION | D3DXSHADER_DEBUG : 0;

	result = D3DXCompileShader( reinterpret_cast<LPCSTR>( i_pShaderData ), i_ShaderDataSizeB, NULL, NULL, "mainPS", "ps_2_0", PSCompileFlags, &pPSCode, NULL, &pPSConstants );

	IDirect3DPixelShader9 * pPS;
	result = g_pD3DDevice->CreatePixelShader( reinterpret_cast<DWORD *>( pPSCode->GetBufferPointer() ), &pPS );

	pPSCode->Release();
	D3D_FAILBUTRETURN( result );

	return new ShaderAssembly( pVS, pVSConstants, pPS, pPSConstants );
}

ShaderAssembly * ShaderAssembly::Create( const char * i_pShaderFileName )
{
	assert( i_pShaderFileName );

	const unsigned int lengthFilename = 256;
	WCHAR	Filename[lengthFilename];

	int res = MultiByteToWideChar( CP_UTF8, 0, i_pShaderFileName, strlen( i_pShaderFileName ), Filename, lengthFilename );
	assert( res > 0 );
	Filename[res] = 0;

	ID3DXBuffer * pVSCode = NULL;
	ID3DXConstantTable * pVSConstants = NULL;

	DWORD VSCompileFlags = g_bDebugVS ? D3DXSHADER_SKIPOPTIMIZATION | D3DXSHADER_DEBUG : 0;

	HRESULT result = D3D_OK;
#ifdef _DEBUG
	ID3DXBuffer * pErrorBuffer = NULL;
	result = D3DXCompileShaderFromFile( Filename, NULL, NULL, "mainVS", "vs_2_0", VSCompileFlags, &pVSCode, &pErrorBuffer, &pVSConstants );
#else
	result = D3DXCompileShaderFromFile( Filename, NULL, NULL, "mainVS", "vs_2_0", VSCompileFlags, &pVSCode, NULL, &pVSConstants );
#endif
	const WCHAR * pErrorString = DXGetErrorDescription( result );
	D3D_FAILBUTRETURN( result );

	IDirect3DVertexShader9 * pVS = NULL;
	result = g_pD3DDevice->CreateVertexShader( reinterpret_cast<DWORD *>( pVSCode->GetBufferPointer() ), &pVS );

	pVSCode->Release();
	D3D_FAILBUTRETURN( result );

	ID3DXBuffer * pPSCode = NULL;
	ID3DXConstantTable * pPSConstants = NULL;

	DWORD PSCompileFlags = g_bDebugVS ? D3DXSHADER_SKIPOPTIMIZATION | D3DXSHADER_DEBUG : 0;

	result = D3DXCompileShaderFromFile( Filename, NULL, NULL, "mainPS", "ps_2_0", PSCompileFlags, &pPSCode, NULL, &pPSConstants );
	assert( result == D3D_OK );

	IDirect3DPixelShader9 * pPS;
	result = g_pD3DDevice->CreatePixelShader( reinterpret_cast<DWORD *>( pPSCode->GetBufferPointer() ), &pPS );

	pPSCode->Release();
	D3D_FAILBUTRETURN( result );

	return new ShaderAssembly( pVS, pVSConstants, pPS, pPSConstants );
}

} // namespace Cheesy