#ifndef __PROFILER_H
#define __PROFILER_H

#include <assert.h>

#include <map>
#include <string>

#include "Timer.h"
#include "DebugPrint.h"

namespace JimEngine
{
	namespace Profiling
	{
		class Profiler
		{
			struct Accumulator
			{
				unsigned int	m_Count;
				unsigned int	m_Sum;
				unsigned int	m_Max;
				unsigned int	m_Min;

				Accumulator()
				{
					m_Count = 0;
					m_Sum = 0;
					m_Max = 0;
					m_Min = UINT_MAX;
				}
			} ;

			std::map<std::string, struct Accumulator> s_Accumulators;

		public:
			Profiler()
			{
				
			}

			~Profiler()
			{
				std::map<std::string, struct Accumulator>::iterator iter = s_Accumulators.begin();

				for( iter ; iter != s_Accumulators.end(); )
				{
					s_Accumulators.erase( iter++ );
				}
			}

			void addTiming( const char * i_pName, float i_MS );
			void PrintAccumulators( void );
		} ; 

		extern Profiler g_Profiler;

		class ScopedTimer
		{
			const char *		m_pScopeName;
			LARGE_INTEGER		m_Start;
			LARGE_INTEGER		m_End;
			double			    frequency;

		public:
			ScopedTimer( const char * i_pName )
			{
				DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);

				::QueryPerformanceCounter(&m_Start);

				::SetThreadAffinityMask(::GetCurrentThread(), oldmask);
				m_pScopeName = i_pName;

				LARGE_INTEGER proc_freq;

				if (QueryPerformanceFrequency(&proc_freq))
				{
					frequency = (double)proc_freq.QuadPart;
				}
				else
				{
					frequency = 0.0f;
				}

			#if defined(_PROFILE)
				JimEngine::ConsolePrint( "Scoped Timer %s started at Tick %lld\n", m_pScopeName ? m_pScopeName : "Unnamed", m_Start );
			#endif
				assert( i_pName );
			}

			~ScopedTimer()
			{
				DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);

				::QueryPerformanceCounter(&m_End);

				::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

			#if defined(_PROFILE)
				JimEngine::ConsolePrint( "Scoped Timer %s ended at Tick %lld ran for %f \n", m_pScopeName ? m_pScopeName : "Unnamed", m_End, ((m_End.QuadPart - m_Start.QuadPart) / frequency) );
			#endif
				g_Profiler.addTiming( m_pScopeName, (float)((m_End.QuadPart - m_Start.QuadPart) / frequency) * 1000 );
			}

		} ;
	}
}


#if defined( ENABLE_PROFILE )
#define PROFILE_CONCAT_HELPER(left, right) left##right
#define PROFILE_CONCAT(left, right) PROFILE_CONCAT_HELPER(left, right)

#define PROFILE_SCOPE_BEGIN(str)	{ Profiling::ScopedTimer PROFILE_CONCAT(__Timer, __LINE__)( str );
#define PROFILE_SCOPE_END()			}

#define PROFILE_UNSCOPED(str)		Profiling::ScopedTimer PROFILE_CONCAT(__Timer, __LINE__)( str );
#define PROFILE_PRINT_RESULTS()		Profiling::g_Profiler.PrintAccumulators();
#else
#define PROFILE_SCOPE_BEGIN(str)	__noop
#define PROFILE_SCOPE_END			__noop
#define PROFILE_UNSCOPED(str)		__noop
#define PROFILE_PRINT_RESULTS()		__noop
#endif // ENABLE_PROFILING

#endif // __PROFILER_H