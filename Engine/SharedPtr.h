#ifndef _SHAREDPTR_H
#define _SHAREDPTR_H

#include <assert.h>

namespace JimEngine
{
	namespace Ptr
	{
		template <class T>
		class SharePtr
		{
			T* m_pPtr;
			unsigned int *m_pReferenceCount;

		public:
			SharePtr( T* i_pPtr = NULL):
				m_pPtr (i_pPtr),
				m_pReferenceCount( new (unsigned int))
			{
				assert( m_pReferenceCount != NULL);
				*m_pReferenceCount = 1;
			}

			SharePtr( const SharePtr<T> & i_other):
				m_pPtr (i_other.m_pPtr),
				m_pReferenceCount (i_other.m_pReferenceCount)
			{
				assert(m_pReferenceCount != NULL);
				*m_pReferenceCount = *m_pReferenceCount + 1;
			}
			
			void Decrement(void)
			{
				assert( m_pReferenceCount );
				assert( *m_pReferenceCount > 0 );
				assert(m_pReferenceCount != NULL);
				*m_pReferenceCount = *m_pReferenceCount - 1;
					if((*m_pReferenceCount) ==0)
					{
						//if(m_pPtr == NULL)
						//{
							delete m_pPtr;
						//}
						m_pPtr = NULL;
						delete m_pReferenceCount;
						m_pReferenceCount = NULL;
					}
			}

			SharePtr<T> & operator = (SharePtr<T> &i_other)
			{
				if(this != &i_other)
				{
					Decrement();
					m_pPtr = i_other.m_pPtr;
					m_pReferenceCount = i_other.m_pReferenceCount;

					assert(m_pReferenceCount != NULL);
					*m_pReferenceCount = *m_pReferenceCount + 1;
					return *this;
				}
				return *this;
			}

			~SharePtr()
			{
				assert( m_pReferenceCount );
				assert( *m_pReferenceCount > 0 );
				assert(m_pReferenceCount != NULL);
			
					*m_pReferenceCount = *m_pReferenceCount - 1;
					if((*m_pReferenceCount) ==0)
					{
						//if(m_pPtr == NULL)
						//{
							delete m_pPtr;
						//}
						m_pPtr = NULL;
						delete m_pReferenceCount;
						m_pReferenceCount = NULL;
				}
			}

			unsigned int Get_Count(void)
			{
				return *m_pReferenceCount;
			}

			T* Get_Pointer(void) const
			{
				assert(m_pPtr != NULL);
				return m_pPtr;
			}

			T* operator->(void)
			{
				assert(m_pPtr != NULL);
				return m_pPtr;
			}
		};
	}
}
#endif