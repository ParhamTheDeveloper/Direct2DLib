#pragma once

#include "Resource.h"

namespace D2DLib
{

	class D2DLIB_API Brush : public Resource
	{
	public:
		Brush() = default;

		Brush(std::nullptr_t)
		{
		}

		Brush(ID2D1Brush* brush)
			: m_Brush(brush)
		{
		}

		Brush(ID2D1SolidColorBrush* brush)
			: m_Brush(brush)
		{
		}

		Brush(ID2D1LinearGradientBrush* brush)
			: m_Brush(brush)
		{
		}

		Brush(ID2D1RadialGradientBrush* brush)
			: m_Brush(brush)
		{
		}

		void Release() override
		{
			SafeRelease(&m_Brush);
		}

		operator ID2D1Brush* () const { return m_Brush; }
		operator const bool () const override { return m_Brush; }
	private:
		ID2D1Brush* m_Brush = nullptr;
		ID2D1SolidColorBrush* m_SolidBrush = nullptr;
		ID2D1LinearGradientBrush* m_LinearGradientBrush = nullptr;
		ID2D1RadialGradientBrush* m_RadialGradientBrush = nullptr;
	};

}