#ifndef _NEW_OVERRIDE_H
#define _NEW_OVERRIDE_H

#include<stdio.h>
#include<Windows.h>
#include"DebugPrint.h"

#define DEBUG_NEW new


//inline void * operator new (const size_t size, const char* file, const size_t line)
inline void * operator new (const size_t size)
{
	if(0 == size)
	{
		return 0;
	}

	void *p = malloc(size);
	return p;
}

//inline void operator delete (void * pointer, const char* file, const size_t line)
inline void operator delete (void * pointer)
{
	if(0 != pointer)
	{
		free(pointer);
	}
}

inline void * operator new [](const size_t size, const char* file, const size_t line)
{
	JimEngine::ConsolePrint("new[] - File: %s,Line: %d Size: %d \n", file,line,size);
	return operator new(size);
}

inline void operator delete[] (void * pointer,const char* file, const size_t line)
{
	operator delete(pointer);
}

#endif