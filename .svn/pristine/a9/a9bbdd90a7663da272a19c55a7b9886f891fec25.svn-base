#ifndef _DEBUG_PRINT_H
#define _DEBUG_PRINT_H
namespace JimEngine
{
	void ConsolePrint(const char * i_fmt,...);
	void Nothing(const char * i_fmt,...);

	#if defined(_DEBUG)
	#define FNL "%s, %d "
	#define DEBUG_PRINT(i_fmt,...) ConsolePrint((FNL i_fmt),__FILE__,__LINE__,__VA_ARGS__)
	
	#else

	#define DEBUG_PRINT(i_fmt,...) Nothing(i_fmt,__VA_ARGS__);
	#endif
}
#endif