
#include <MeshData.h>

struct _CubeVertex
{
	D3DXVECTOR3		position;
	D3DXVECTOR3		normal;
	D3DCOLOR		diffuse;
	D3DXVECTOR2		uv;
} ;

struct _CubeVertex cubeVertices[] = 
{
	// -Z
	{ D3DXVECTOR3( -1.0,  1.0, -1.0 ), D3DXVECTOR3(  0.0,  0.0, -1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 0.0f ) },
	{ D3DXVECTOR3(  1.0,  1.0, -1.0 ), D3DXVECTOR3(  0.0,  0.0, -1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 0.0f ) },
	{ D3DXVECTOR3( -1.0, -1.0, -1.0 ), D3DXVECTOR3(  0.0,  0.0, -1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 1.0f ) },
	{ D3DXVECTOR3(  1.0, -1.0, -1.0 ), D3DXVECTOR3(  0.0,  0.0, -1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 1.0f ) },

	// +X
	{ D3DXVECTOR3(  1.0,  1.0, -1.0 ), D3DXVECTOR3(  1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 0.0f ) },
	{ D3DXVECTOR3(  1.0,  1.0,  1.0 ), D3DXVECTOR3(  1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 0.0f ) },
	{ D3DXVECTOR3(  1.0, -1.0, -1.0 ), D3DXVECTOR3(  1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 1.0f ) },
	{ D3DXVECTOR3(  1.0, -1.0,  1.0 ), D3DXVECTOR3(  1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 1.0f ) },

	// +Z
	{ D3DXVECTOR3(  1.0,  1.0,  1.0 ), D3DXVECTOR3(  0.0,  0.0,  1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 0.0f ) },
	{ D3DXVECTOR3( -1.0,  1.0,  1.0 ), D3DXVECTOR3(  0.0,  0.0,  1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 0.0f ) },
	{ D3DXVECTOR3(  1.0, -1.0,  1.0 ), D3DXVECTOR3(  0.0,  0.0,  1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 1.0f ) },
	{ D3DXVECTOR3( -1.0, -1.0,  1.0 ), D3DXVECTOR3(  0.0,  0.0,  1.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 1.0f ) },

	// -X
	{ D3DXVECTOR3( -1.0,  1.0,  1.0 ), D3DXVECTOR3( -1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 0.0f ) },
	{ D3DXVECTOR3( -1.0,  1.0, -1.0 ), D3DXVECTOR3( -1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 0.0f ) },
	{ D3DXVECTOR3( -1.0, -1.0,  1.0 ), D3DXVECTOR3( -1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 1.0f ) },
	{ D3DXVECTOR3( -1.0, -1.0, -1.0 ), D3DXVECTOR3( -1.0,  0.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 1.0f ) },

	// +Y
	{ D3DXVECTOR3( -1.0,  1.0,  1.0 ), D3DXVECTOR3(  0.0,  1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 0.0f ) },
	{ D3DXVECTOR3(  1.0,  1.0,  1.0 ), D3DXVECTOR3(  0.0,  1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 0.0f ) },
	{ D3DXVECTOR3( -1.0,  1.0, -1.0 ), D3DXVECTOR3(  0.0,  1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 1.0f ) },
	{ D3DXVECTOR3(  1.0,  1.0, -1.0 ), D3DXVECTOR3(  0.0,  1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 1.0f ) },

	// -Y
	{ D3DXVECTOR3( -1.0, -1.0, -1.0 ), D3DXVECTOR3(  0.0, -1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 0.0f ) },
	{ D3DXVECTOR3(  1.0, -1.0, -1.0 ), D3DXVECTOR3(  0.0, -1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 0.0f ) },
	{ D3DXVECTOR3( -1.0, -1.0,  1.0 ), D3DXVECTOR3(  0.0, -1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 0.0f, 1.0f ) },
	{ D3DXVECTOR3(  1.0, -1.0,  1.0 ), D3DXVECTOR3(  0.0, -1.0,  0.0 ), D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ), D3DXVECTOR2( 1.0f, 1.0f ) }

} ;

D3DVERTEXELEMENT9 cubeDecl[] =
{
	{ 0,  0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, 12, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	{ 0, 24, D3DDECLTYPE_D3DCOLOR,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, 28, D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

WORD cubeIndices[] = 
{
	0,  1,  2,  
	2,  1,  3,

	4,  5,  6,
	6,  5,  7,

	8,  9, 10,
	10,  9, 11,

	12, 13, 14,
	14, 13, 15,

	16, 17, 18,
	18, 17, 19,

	20, 21, 22,
	22, 21, 23
} ;

struct Cheesy::_MeshData CubeData = 
{ 
	cubeVertices, sizeof( cubeVertices[0] ), sizeof( cubeVertices ) / sizeof( cubeVertices[0] ),
	cubeDecl, D3DPT_TRIANGLELIST,
	cubeIndices, sizeof( cubeIndices ) / sizeof( cubeIndices[0] ) 
} ;
