#include <assert.h>

namespace Cheesy
{

inline IReferenceCounted::IReferenceCounted() : 
	i_RefCount( 1 )
{
}

inline void IReferenceCounted::Acquire() const
{ 
	i_RefCount++; 
}

inline unsigned int IReferenceCounted::Release() const
{
	assert( i_RefCount > 0 );

	unsigned int newRefCount = --i_RefCount;

	if( newRefCount == 0 )
		delete this;

	return newRefCount;
}

} // namespace Cheesy
