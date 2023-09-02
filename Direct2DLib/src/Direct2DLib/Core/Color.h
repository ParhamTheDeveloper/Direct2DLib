#pragma once

#include "Base.h"

namespace D2DLib
{

	class D2DLIB_API ColorValue
	{
	public:
		ColorValue(const Function<const float()>& getter, const Function<void(float, float)>& setter)
			: m_Getter(getter), m_Setter(setter), m_Value(0.0f)
		{
		}

		ColorValue& operator=(const float& value)
		{
			m_Setter(m_Value, value);
			m_Value = value;
			return *this;
		}

		operator const float () const
		{
			return m_Getter();
		}
	private:
		float m_Value;
		Function<const float()> m_Getter;
		Function<void(float, float)> m_Setter;
	};
	
	class D2DLIB_API Color
	{
	public:
		Color(
			float r = 0.0f,
			float g = 0.0f,
			float b = 0.0f,
			float a = 255.0f
		)
			: m_Color(0.0f, 0.0f, 0.0f, 0.0f)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		Color(const Color& other)
			: m_Color(0.0f, 0.0f, 0.0f, 0.0f)
		{
			m_Color = other.m_Color;
		}

		Color& operator=(const Color& other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
			m_Color = other.m_Color;
			return *this;
		}

		operator const D2D1::ColorF& () const { return m_Color; }
	public:
		ColorValue r = ColorValue(
			[&]
			{
				return m_Color.r * 255.0f;
			},
			[&](float prev, float value)
			{
				m_Color.r = value / 255.0f;
			});
		ColorValue g = ColorValue(
			[&]
			{
				return m_Color.g * 255.0f;
			},
			[&](float prev, float value)
			{
				m_Color.g = value / 255.0f;
			});
		ColorValue b = ColorValue(
			[&]
			{
				return m_Color.b * 255.0f;
			},
			[&](float prev, float value)
			{
				m_Color.b = value / 255.0f;
			});
		ColorValue a = ColorValue(
			[&]
			{
				return m_Color.a * 255.0f;
			},
			[&](float prev, float value)
			{
				m_Color.a = value / 255.0f;
			});
	private:
		D2D1::ColorF m_Color;
	};

}