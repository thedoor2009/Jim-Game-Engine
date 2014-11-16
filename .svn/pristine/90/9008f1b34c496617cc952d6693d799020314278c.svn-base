#include "BufferNode.h"
#include "OrNew.h"
#include <crtdbg.h>
#include <cctype>
#define new DEBUG_NEW 
#ifndef RINGBUFFER_CLASS
#define RINGBUFFER_CLASS

namespace JimEngine
{
	
	template<class __Type__>
	class RingBuffer
	{
	
	public:
		inline RingBuffer(const int m_MaxBuffer)
		{
			BufferNum = 1;
			MaxBuffer = m_MaxBuffer;
		}

		template<class __Type__>
		void InitList(void)
		{
			head = new BufferNode<__Type__>;
			head->next = NULL;
		}
		
		template<class __Type__>
		void ClearList()
		{
			delete head;
			cout<<"The RingBuffer has been cleared out."<<endl;
		}

		template<class __Type__>
		bool ListEmpty()
		{
			if(head->next == NULL)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		template<class __Type__>
		int ListLength()
		{
			if(head)
			{
				return 0;
			}
			BufferNode<__Type__> *p = head;
			int j = 1;
			while(p->next)
			{
				p = p->next;
				j++;
			}
			return j;
		}
		
		template<class __Type__>
		const int Size()
		{
			return MaxBuffer;
		}

		
		bool ListInsert(const __Type__ a)
		{
		
			if(BufferNum <= MaxBuffer)
			{
				BufferNode<__Type__> *p;
				BufferNode<__Type__> *s = new BufferNode<__Type__>;
		
				p = head;
				for(int i = 1; i < BufferNum; i++)
				{
					p = p->next;
			
				}
		
				s->data = a;
				s->next = NULL;
				p->next = s;
				BufferNum++;
				return true;
			}
			else
			{
				int num = BufferNum % MaxBuffer;
				if( BufferNum % MaxBuffer == 0)
				{
					num = MaxBuffer;
				}
				BufferNode<__Type__> *p;
				p = head->next;
				for(int i = 1; i < num; i++)
				{
					p = p->next;
				}
				p->data = a;
				BufferNum++;
				return true;
			}

		
		}

		
		__Type__  GetElem(const int i)
		{
			// This function get the ith element, and the head is the 0 the one.
			int j =1;
			BufferNode<__Type__> *p;
			p = head->next;
			if(i<0) 
			{
				return NULL;
			}
			if((i+1) == 0) 
			{
				return head->data;
			}
			while (p && j < i)
			{
				p = p->next;
				j++;
			}
			return p->data;
		}

		template<class __Type__>
		void DestroyList()
		{
			BufferNode<__Type__> *q = NULL;
			q = head->next;
			if(q!=NULL)
			{
				while(q->next != NULL)
				{
					head->next = q->next;
					//delete q->data;
					delete q;
					//cout<<"delete q"<<endl;
					q = head->next;
				}
				if(q->next == NULL)
				{
					//delete q->data;
					delete q;
					delete head;
					//cout<<"delete head"<<endl;
				}
			}
			else
			{
				delete head;
			}

			cout<<"The RingBuffer has been destroyed!"<<endl;
		}

		__Type__ operator [](const int i)
		{
			if(BufferNum <= MaxBuffer)
			{
				int relative_num = (BufferNum - i);
				__Type__ x = GetElem(relative_num);
			}
			else
			{
				int relative_num = (BufferNum - i) & MaxBuffer; 
				if(relative_num == 0)
				{
					relative_num = MaxBuffer;
				}
				__Type__ x = GetElem(relative_num);
				return x;
			}
		return 0;
		}
		

	private:
		BufferNode<__Type__> *head;
		int BufferNum;
		int MaxBuffer;
	};
}


#endif