#ifndef _MEMORY_POOL_H
#define _MEMORY_POOP_H

#include<assert.h>
#include<Windows.h>
#include"BitArray.h"

namespace JimEngine
{
	class MemoryPool
	{
		char* m_pMemoryPool;
		BitArray *m_bitArray;
		unsigned int m_ItemSize;
		unsigned int m_ItemCount;

		MemoryPool(char * i_pPoolMemory,BitArray *i_bitArray,const unsigned int i_itemSize,const unsigned int i_itemsCount):
			m_pMemoryPool(i_pPoolMemory),
			m_bitArray(i_bitArray),
			m_ItemSize(i_itemSize),
			m_ItemCount(i_itemsCount)
		
		{
			assert( i_pPoolMemory != NULL);
			if(m_bitArray == NULL)
			{
				m_bitArray = BitArray::create(m_ItemCount);
			}
		}

	public:
		~MemoryPool();

		void *alloc(const size_t i_size);
		void Free(void *i_pPtr);

		/////////////////////////////////////////////////////////////////////////////

		static MemoryPool * create( const unsigned int i_itemSize, const unsigned int i_itemCount)
		{
			char * pPoolMemory = new char[i_itemCount * i_itemSize];
			BitArray *bitarray = BitArray::create(i_itemCount);

			//If new operation fails.
			if(pPoolMemory == NULL )
			{
			
				return NULL;
			}
			else
			{
				return new MemoryPool(pPoolMemory,bitarray,i_itemSize,i_itemCount);
			}
		}
	};
}
#endif