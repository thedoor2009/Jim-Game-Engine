#include <iostream>
#include "LNode.h"
#include "LinkList.h"
#include "Spirte.h"
#include "OrNew.h"
#include <crtdbg.h>
#include <cctype>

using namespace std;

namespace JimEngine
{
	void MyList::InitList(void)
	{
		head = new LNode;
		head->next = NULL;
		
	}
	/////////////////////////////////////
	void MyList::DestroyList()
	{
		LNode *q = NULL;
		q = head->next;
		if(q!=NULL)
		{
			while(q->next != NULL)
			{
				head->next = q->next;
				delete q->data;
				delete q;
				q = head->next;
			}
			if(q->next == NULL)
			{
				delete q->data;
				delete q;
				delete head;
			}
		}
		else
		{
			delete head;
		}
	}
	/////////////////////////////////////
	void MyList::ClearList()
	{
		delete head;
	}
	/////////////////////////////////////
	bool MyList::ListEmpty()
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
	/////////////////////////////////////
	int MyList::ListLength()
	{
		LNode *p = head;
		int j = 0;
		while(p->next)
		{
			p = p->next;
			j++;
		}
		return j;
	}
	/////////////////////////////////////
	 Sprite* MyList::GetElem(const int i)
	{
		// This function get the ith element, and the head is the 0 the one.
		int j =1;
		LNode *p = head->next;
		if(i<0) 
		{
			return NULL;
		}
		if(i == 0) 
		{
			return head->data;
		}
		while (p && j<i)
		{
			p = p->next;
			j++;
		}
		return p->data;
	}
	/////////////////////////////////////
	int MyList::LocateElem(const int x,const int y)
	{
		int i =0;
		LNode *p = head->next;
		while(p!= NULL && p->data->Get_Position().Cor_GetX()!= x && p->data->Get_Position().Cor_GetY()!= y )
		{
			p->next;
			i++;
		}
		if(p==NULL)
		{
			return 0;
		}
		else
		{
			return i+1;
		}
	}
	/////////////////////////////////////

	bool MyList::ListInsert( Sprite* a)
	{
		LNode *p;
		LNode *s;
		
		p = head;
		if(a == NULL)
		{
			return false;
		}
		while(p->next != NULL)
		{
			p = p->next;
			
		}
		if(p==NULL)
		{
			return false;
		}
		s = new LNode;
		s->data = a;
		JimEngine::Coordination temp = s->data->Get_Position();
		temp.Cor_Set(0.0f,0.0f,0.0f);
		s->next = NULL;
		p->next = s;
		return true;
	}
	/////////////////////////////////////

	bool MyList::ListDelete(const int i)
	{
	// This function detele ith element. The head is the 0 one.
		int j;
		LNode *p, *q;
		p = head;
		j = 1;
		while (p->next && j < i )
		{
			p = p->next;
			j++;
		}
		if(!(p->next) || j>i)
		{
			return ERROR;
		}
		q = p->next;
		p->next = q->next;
		delete q->data;
		delete q;
		return true;
	}
	/////////////////////////////////////

	void MyList::PrintList()
	{
		if(ListEmpty())
		{
			cout<<"This list is empty."<<endl;
		}
		else
		{
			cout <<"The elements of list are: "<<endl;
			int i =1;
			LNode *p = head->next;
			
			while(p->next!= NULL)
			{
				cout<<"Monster"<<i<<": ";
				JimEngine::Coordination temp = p->data->Get_Position();
				temp.Cor_Show();
				p = p->next;
				i++;
			}
			cout<<"Monster"<<i<<": ";
			JimEngine::Coordination temp = p->data->Get_Position();
			temp.Cor_Show();
			cout<<endl;
		}
	}

}