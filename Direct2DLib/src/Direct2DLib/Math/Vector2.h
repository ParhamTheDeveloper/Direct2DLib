#pragma once

#include "Direct2DLib/Core/Base.h"

namespace D2DLib
{
	// classes

	/// <summary>
	/// A Vector class that holds two float variables named X and Y.
	/// </summary>
	class D2DLIB_API Vector2
	{
	public:
		Vector2();
		Vector2(float scalar);
		Vector2(float x, float y);
		Vector2(const Vector2& other);

		void Normalize();
		bool IsNonZero() const;
		static const Vector2 FromAngle(float angleRadian);
		static float Distance(const Vector2& vec1, const Vector2& vec2);

		Vector2& operator=(const Vector2& other);
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		operator const bool() const;

		const Vector2 operator+(float scalar) const;
		const Vector2 operator-(float scalar) const;
		const Vector2 operator*(float scalar) const;
		const Vector2 operator/(float scalar) const;

		const Vector2 operator+(const Vector2& other) const;
		const Vector2 operator-(const Vector2& other) const;
		const Vector2 operator*(const Vector2& other) const;
		const Vector2 operator/(const Vector2& other) const;

		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(const Vector2& other);
		Vector2& operator/=(const Vector2& other);

		Vector2& operator+=(float scalar);
		Vector2& operator-=(float scalar);
		Vector2& operator*=(float scalar);
		Vector2& operator/=(float scalar);
	public:
		float X, Y;
	};

}