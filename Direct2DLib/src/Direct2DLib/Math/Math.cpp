#include "Direct2DLibpch.h"
#include "Math.h"

namespace D2DLib
{

	float DegreesToRadians(float degrees)
	{
		return Cast<float>(degrees * (M_PI / 180.0f));
	}

}