#pragma once

#include "Base.h"

namespace D2DLib
{
	
	class D2DLIB_API Color
	{
	public:
		Color(
			float r = 0.0f,
			float g = 0.0f,
			float b = 0.0f,
			float a = 255.0f
		)
			: m_Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f)
		{
		}

		Color(const Color& other)
			: m_Color(other.m_Color)
		{
		}

		Color& operator=(const Color& other)
		{
			m_Color = other.m_Color;
			return *this;
		}

		operator const D2D1::ColorF& () const { return m_Color; }
	public:
		float& r = m_Color.r;
		float& g = m_Color.g;
		float& b = m_Color.b;
		float& a = m_Color.a;
	private:
		D2D1::ColorF m_Color;
	};

}