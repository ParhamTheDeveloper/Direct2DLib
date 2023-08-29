#pragma once

#include "Direct2DLib/Core/Base.h"
#include "Utils.h"

namespace D2DLib
{

	class D2DLIB_API Resource
	{
	public:
		virtual void Release() = 0;
		virtual operator const bool () const = 0;
	};
	
}