#include "pch.h"
#include "Vector2.h"

namespace D2DLib
{

	Vector2::Vector2()
		: X(0.0f), Y(0.0f)
	{
	}

	Vector2::Vector2(float scalar)
		: X(scalar), Y(scalar)
	{
	}

	Vector2::Vector2(float x, float y)
		: X(x), Y(y)
	{
	}

	Vector2::Vector2(const Vector2& other)
	{
		X = other.X;
		Y = other.Y;
	}

	void Vector2::Normalize()
	{
		float magnitude = std::sqrt(X * X + Y * Y);

		if (magnitude)
		{
			X /= magnitude;
			Y /= magnitude;
		}
	}

	bool Vector2::IsNonZero() const
	{
		return X != 0 || Y != 0;
	}

	const Vector2 Vector2::FromAngle(float angleRadian)
	{
		float x = std::sin(angleRadian);
		float y = std::cos(angleRadian);
		return Vector2(x, y);
	}

	float Vector2::Distance(const Vector2& vec1, const Vector2& vec2)
	{
		Vector2 distance = vec1 - vec2;
		return std::sqrt(distance.X * distance.X + distance.Y * distance.Y);
	}

	Vector2& Vector2::operator=(const Vector2& other)
	{
		X = other.X;
		Y = other.Y;
		return *this;
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return (X == other.X && Y == other.Y);
	}

	bool Vector2::operator!=(const Vector2& other) const
	{
		return (*this == other);
	}

	Vector2::operator bool() const
	{
		return X != 0.0f && Y != 0.0f;
	}


	const Vector2 Vector2::operator+(float scalar) const
	{
		return Vector2(X + scalar, Y + scalar);
	}

	const Vector2 Vector2::operator-(float scalar) const
	{
		return Vector2(X - scalar, Y - scalar);
	}

	const Vector2 Vector2::operator*(float scalar) const
	{
		return Vector2(X * scalar, Y * scalar);
	}

	const Vector2 Vector2::operator/(float scalar) const
	{
		return Vector2(X / scalar, Y / scalar);
	}

	const Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	const Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Vector2(X - other.X, Y - other.Y);
	}

	const Vector2 Vector2::operator*(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	const Vector2 Vector2::operator/(const Vector2& other) const
	{
		return Vector2(X / other.X, Y / other.Y);
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& other)
	{
		X *= other.X;
		Y *= other.Y;
		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& other)
	{
		X /= other.X;
		Y /= other.Y;
		return *this;
	}


	Vector2& Vector2::operator+=(float scalar)
	{
		X += scalar;
		Y += scalar;
		return *this;
	}

	Vector2& Vector2::operator-=(float scalar)
	{
		X -= scalar;
		Y -= scalar;
		return *this;
	}

	Vector2& Vector2::operator*=(float scalar)
	{
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	Vector2& Vector2::operator/=(float scalar)
	{
		X /= scalar;
		Y /= scalar;
		return *this;
	}

}