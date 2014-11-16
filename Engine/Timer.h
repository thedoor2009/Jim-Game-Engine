#include <windows.h>

namespace JimEngine
{
	class Timer {
	public:

		Timer(void);

		double getFrequency(void);
		void   startTimer(void) ;
		double stopTimer(void);
		double getCurrentTick( void );

	private:

		LARGE_INTEGER start;
		LARGE_INTEGER stop;

		double frequency;
	};
}