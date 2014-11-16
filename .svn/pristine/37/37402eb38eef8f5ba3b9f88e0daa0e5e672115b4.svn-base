#ifndef EQUAL_H
#define EQUAL_H

#include <iostream>
#include "Zero.h"
namespace JimEngine
{
	inline bool areAproxEuql(const float i_lhs,const float i_rhs)
	{
		float diff = i_lhs - i_rhs;
		float largest = i_lhs> i_rhs ? i_lhs : i_rhs;

		if(isAproxZero(i_lhs) || isAproxZero(i_rhs))
		{
			if(fabs(diff) < 0.000001f)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if(fabs(diff) < fabs(largest) * 0.000001f)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
#endif