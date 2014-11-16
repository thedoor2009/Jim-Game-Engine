#ifndef __MESH_H
#define __MESH_H

#include <d3d9.h>
#include <d3dx9.h>

namespace Cheesy
{
	class LargeIndexBuffer;
	class LargeVertexBuffer;
	class Material;

class Mesh
{
public:
	static Mesh * Create( const struct _MeshData & i_MeshData );
	~Mesh();

	void Draw( const D3DXMATRIX * i_pToWorld, const Material & i_Material ) const;

private:
	struct _DrawInfo
	{
		D3DPRIMITIVETYPE	m_PrimType;
		INT					m_BaseVertexIndex;
		UINT				m_MinIndex;
		UINT				m_NumVertices;
		UINT				m_StartIndex;
		UINT				m_PrimCount;
	};

	LargeVertexBuffer *		m_pVB;
	IDirect3DVertexDeclaration9 * m_pVBDecl;
	UINT					m_VBStride;

	LargeIndexBuffer *		m_pIB;
	struct _DrawInfo		m_DrawInfo;

	Mesh( LargeVertexBuffer * i_pVB, IDirect3DVertexDeclaration9 * i_pVBDecl, UINT i_VBStride, LargeIndexBuffer * i_pIB, const struct _DrawInfo & i_DrawInfo );
	void Activate( void ) const;
} ;

} // namespace Cheesy

#endif // __MESH_H