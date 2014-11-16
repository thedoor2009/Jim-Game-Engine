#ifndef ZERO_H
#define ZERO_H

#include <iostream>
namespace JimEngine
{
	inline bool isAproxZero(const float i_lhs)
	{
		float diff = i_lhs - 0.0f;

		if(fabs(diff) <  0.000001f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#endif