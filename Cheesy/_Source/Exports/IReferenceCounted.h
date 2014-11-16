#ifndef __I_REFERENCE_COUNTED_H
#define __I_REFERENCE_COUNTED_H

namespace Cheesy
{

class IReferenceCounted
{
	mutable unsigned int		i_RefCount;

protected:
	virtual ~IReferenceCounted() {}

public:
	IReferenceCounted();

	void Acquire() const;
	unsigned int Release() const;
} ;

} // namespace Cheesy

#include "IReferenceCounted.inl"

#endif // __I_REFERENCE_COUNTED_H