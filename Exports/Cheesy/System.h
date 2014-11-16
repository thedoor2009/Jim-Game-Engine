#ifndef __SYSTEM_H
#define __SYSTEM_H

namespace Cheesy
{

	bool Create( const char * i_pAppName, unsigned int i_WindowWidth, unsigned int i_WindowHeight, bool i_DebugVS = false, bool i_DebugPS = false );
	bool Service( bool & o_bQuitRequested );
	void Shutdown( void );
	int	GetExitCode( void );

} // namespace Cheesy

#endif // __SYSTEM_H