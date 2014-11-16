#include "Timer.h"

namespace JimEngine
{
	Timer::Timer(void)
	: start(),
	stop(),
	frequency()
	{
		frequency = this->getFrequency();
	}

	double Timer::getFrequency(void)
	{
		LARGE_INTEGER proc_freq;

		if (QueryPerformanceFrequency(&proc_freq))
		{
			return (double)proc_freq.QuadPart;
		}
		return 0.0f;
	}

	void Timer::startTimer(void)
	{
		DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);

		::QueryPerformanceCounter(&start);

		::SetThreadAffinityMask(::GetCurrentThread(), oldmask);
	}

	double Timer::stopTimer(void)
	{
		DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);

		::QueryPerformanceCounter(&stop);

		::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

		return ((stop.QuadPart - start.QuadPart) / frequency);
	}

	double Timer::getCurrentTick( void )
	{
		DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);

		::QueryPerformanceCounter(&start);

		::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

		return (double)start.QuadPart;
	}
}