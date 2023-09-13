#include "Direct2DLibpch.h"
#include "Math.h"

namespace D2DLib
{

	float DegreesToRadians(float degrees)
	{
		return Cast<float>(degrees * (D2DLIB_PI / 180.0f));
	}

	float FastSqrt(float number)
	{
		long i = 0;
		float x2 = 0;
		float y = 0;

		const float threehalfs = 1.5f;

		x2 = number * 0.5f;
		y = number;
		i = *reinterpret_cast<long*>(&y);
		i = 0x5f3759df - (i >> 1);
		y = *reinterpret_cast<float*>(&i);
		y *= (threehalfs - (x2 * y * y));

		return y;
	}

}