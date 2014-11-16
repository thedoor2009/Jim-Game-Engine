#include "BitArray.h"

namespace JimEngine
{
	unsigned int BitArray::getFirstFreeBit(void)
	{
		unsigned int i_index = 0;

		while(i_index < m_BitCount)
		{
			if(m_pBitMemory[i_index] != 0xffffffff)
			{
				break;
			}
			i_index++;
		}
		unsigned int bit = m_pBitMemory[i_index];
		for(unsigned int i = 0; i < 32; i++)
		{
			if((bit & 1) == 0)
			{
				if((i_index * 32 + i) > m_BitCount)
				{
					cout<<endl;
					return (m_BitCount);
				}
				return (i_index * 32 + i);	
			}
			bit = bit>>1;
		}
		return -1;
	}

	void BitArray::setFirstFreeBit(void)
	{
		unsigned int i_index = 0;

		while(i_index < m_BitCount)
		{
			if(m_pBitMemory[i_index] != 0xffffffff)
			{
				break;
			}
			i_index++;
		}
		unsigned int bit = m_pBitMemory[i_index];
		for(double i = 0.0; i < 32; i++)
		{
			
			if((bit & 1) == 0)
			{
				if((i_index * 32 + i) > m_BitCount)
				{

				}
				else
				{
					unsigned int second = (unsigned int)pow(2.0,i);
					m_pBitMemory[i_index] = m_pBitMemory[i_index]|second;
					break;
				}
			}
			bit = bit>>1;
		}
	}

	////////////////////////////////////////////////////////////////////
	void BitArray::clearOneBit(const unsigned int i_index)
	{
		assert(UsedorFree(i_index));
		unsigned int num = i_index / 32;
		unsigned int index = i_index % 32;
		unsigned int second = (unsigned int)pow(2.0,(double)index);
		m_pBitMemory[num] = m_pBitMemory[num]&(~second);
	}


	//////////////////////////////////////////////////////////////////////
	bool BitArray::UsedorFree(const size_t i_index)
	{
		assert(i_index < (m_BitCount * 32));
		unsigned int num = i_index / 32;
		unsigned int bit = i_index % 32;
		unsigned int take_bit = m_pBitMemory[num];
		if(((take_bit >> bit) & 1) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}