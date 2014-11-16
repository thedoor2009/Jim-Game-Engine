#ifndef _BIT_ARRAY_H
#define _BIT_ARRAY_H
#include<Windows.h>
#include<assert.h>
#include<stdint.h>
#include<math.h>
#include<iostream>

using namespace std;
namespace JimEngine
{

	class BitArray
	{
		uint32_t * m_pBitMemory;
		unsigned int m_BitCount;
		BitArray(uint32_t * i_pBitMemory, unsigned int i_itemCount):
			m_pBitMemory( i_pBitMemory),
			m_BitCount(i_itemCount)
		{
			for(unsigned int i = 0; i < m_BitCount/32 + 1; i++)
			{
				m_pBitMemory[i] = 0;
			}
		}

	public:
		~BitArray()
		{
			delete []m_pBitMemory;
		}
		
		unsigned int getFirstFreeBit(void);
		void setFirstFreeBit(void);
	

		void setOneBit(const unsigned int i_index);
		void clearOneBit(const unsigned int i_index);
	
		bool UsedorFree(const size_t i_index);
	
		/////////////////////////////////////////////////////////////////////

		static BitArray *create( const unsigned int i_itemCount)
		{
			uint32_t *pBitMemory = (uint32_t*)malloc((i_itemCount + 31)/32 * sizeof(uint32_t));

			if(pBitMemory == NULL)
			{
				return NULL;
			}
			else
			{
				return new BitArray(pBitMemory, i_itemCount);
			}
		}

		static void UnityTest(void)
		{
			BitArray *a = BitArray::create(20);
			for(int i = 0; i < 20; i++)
			{
				cout<<i<<": "<<a->UsedorFree(i)<<endl;
			}
			cout<<endl;

			unsigned int b = a->getFirstFreeBit();
		
			for(int i = 0; i < 12; i++)
			{
				a->setFirstFreeBit();
			}
			for(int i = 0; i < 20; i++)
			{
				cout<<i<<": "<<a->UsedorFree(i)<<endl;
			}
			cout<<endl;

			a->clearOneBit(0);
			for(int i = 0; i < 20; i++)
			{
				cout<<i<<": "<<a->UsedorFree(i)<<endl;
			}
		}

	};
}
#endif
