#ifndef __BUFFERS_H
#define __BUFFERS_H

namespace Cheesy
{
	class LargeIndexBuffer;
	class LargeVertexBuffer;

	LargeVertexBuffer * GetDynamicVB( void );
	LargeIndexBuffer *	GetDynamicIB( void );

	LargeIndexBuffer *	GetStaticIB( unsigned int i_numIndices );
	LargeVertexBuffer * GetStaticVB( unsigned int i_numVertices, unsigned int i_strideVertex );

	bool AddStaticVertices( void * i_pVertices, unsigned int i_numVertices, unsigned int i_strideVertex, LargeVertexBuffer * & o_pBuffer, unsigned int & o_BaseVertex );
	bool AddStaticIndices( WORD * i_pIndices, unsigned int i_numIndices, LargeIndexBuffer * & o_pBuffer, unsigned int & o_pBaseIndex );


} // namespace Cheesy

#endif // __RENDERING_H