#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
namespace JimEngine
{
	void ConsolePrint(const char * i_fmt,...)
	{
		const unsigned int str_length = 128;
		char str[str_length];

		va_list args;

		va_start(args, i_fmt);

		vsprintf_s(str,str_length,i_fmt,args);

		va_end(args);
		OutputDebugStringA(str);
	}

	void Nothing(const char * i_fmt,...)
	{

	}
}