#include "Profiling.h"

namespace JimEngine
{
	namespace Profiling
	{
		Profiler g_Profiler;

		void Profiler::addTiming( const char * i_pName, float i_MS )
		{
			struct Accumulator & myAccumulator = s_Accumulators[i_pName];

			if( i_MS < myAccumulator.m_Min )
				myAccumulator.m_Min = ( unsigned int )i_MS;
			if( i_MS > myAccumulator.m_Max )
				myAccumulator.m_Max = ( unsigned int )i_MS;

			myAccumulator.m_Count++;
			myAccumulator.m_Sum += ( unsigned int )i_MS;
		}

		void Profiler::PrintAccumulators( void )
		{
			std::map<std::string, struct Accumulator>::iterator iter = s_Accumulators.begin();

			for( iter ; iter != s_Accumulators.end(); ++iter )
			{
				float Average = iter->second.m_Count ? ((float) iter->second.m_Sum ) / iter->second.m_Count : 0.0f;
				JimEngine::ConsolePrint( "[%s]    Count: %d    Sum: %d    Min: %d    Max: %d    Ave: %f\n", iter->first.c_str(), iter->second.m_Count, iter->second.m_Sum, iter->second.m_Min, iter->second.m_Max, Average );
			}
		} 
	}
};