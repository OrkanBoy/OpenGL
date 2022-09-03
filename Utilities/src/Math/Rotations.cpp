#include "Rotations.hpp"
#include <iostream>

namespace Math
{
	void bound(float& value, float lb, float ub)
	{
		if (value < lb)
			value = lb;
		if (value > ub)
			value = ub;
	}
}