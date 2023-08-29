#pragma once

#include "Direct2DLib/Math/Vector2.h"

namespace D2DLib
{

	class D2DLIB_API Boundary
	{
	public:
		Boundary()
			: Start(), End()
		{
		}

		Boundary(const Vector2& start, const Vector2& end)
			: Start(start), End(end)
		{
		}
	public:
		Vector2 Start, End;
	};

}