#include "MemoryPool.h"
namespace JimEngine
{
	MemoryPool::~MemoryPool()
	{
		delete []m_pMemoryPool;
		delete  m_bitArray;
	}

	void *MemoryPool::alloc(const size_t i_size)
	{
		assert(i_size == m_ItemSize);

		if(((m_bitArray->getFirstFreeBit()) * i_size) >= m_ItemCount * i_size)
		{
			cout<<"ATTENTION!!!!!!!!"<<endl;
			return NULL;
		}
		m_bitArray->setFirstFreeBit();
		return m_pMemoryPool + (m_bitArray->getFirstFreeBit()-1) * i_size;
	}

	void MemoryPool::Free(void* i_pPtr)
	{
		unsigned int iFreeBit;
		iFreeBit = ((DWORD)i_pPtr - (DWORD)m_pMemoryPool)/ m_ItemSize;
		assert(m_bitArray->UsedorFree(iFreeBit));
		m_bitArray->clearOneBit(iFreeBit);
	}
}
