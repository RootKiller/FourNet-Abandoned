// Copyright (C) 2016 by DVO Games

#pragma once

#include "Debug/Debug.h"

#include <cmath>

/**
 * 2D Vector class.
 */
class Vector2
{
public:
	// X-component.
	float x;

	// Y-component.
	float y;

	// Default constructor.
	Vector2		()
		: x(0.0f)
		, y(0.0f)
	{
	}

	// Constructor creating vector from X and Y coordinate.
	Vector2		(const float _x, const float _y)
		: x(_x)
		, y(_y)
	{
	}

	// Copy-constructor.
	Vector2		(const Vector2& vec)
	{
		(*this) = vec;
	}

	// Move-constructor.
	Vector2		(Vector2&& vec)
	{
		(*this) = vec;
	}

	// Destructor.
	~Vector2		()
	{
	}

	// Copy-assignment operator.
	Vector2& operator=(const Vector2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	// Move-assignment operator.
	Vector2& operator=(Vector2&& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	bool operator==(const Vector2& vec) const
	{
		return x == vec.x && y == vec.y;
	}

	bool operator!=(const Vector2& vec) const
	{
		return x != vec.x && y != vec.y;
	}

	float& operator[](const unsigned index)
	{
		ASSERT(index <= 2);
		return *(&x + index);
	}

	float operator[](const unsigned index) const
	{
		ASSERT(index <= 2);
		return *(&x + index);
	}

	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 operator*(const Vector2& vec) const
	{
		return Vector2(x * vec.x, y * vec.y);
	}

	Vector2 operator/(const Vector2& vec) const
	{
		return Vector2(x / vec.x, y / vec.y);
	}

	Vector2 operator+(const float scalar) const
	{
		return Vector2(x + scalar, y + scalar);
	}

	Vector2 operator-(const float scalar) const
	{
		return Vector2(x - scalar, y - scalar);
	}

	Vector2 operator*(const float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(const float scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

	Vector2& operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& operator*=(const Vector2& vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}

	Vector2& operator/=(const Vector2& vec)
	{
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	Vector2& operator+=(const float scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}

	Vector2& operator-=(const float scalar)
	{
		x -= scalar;
		y -= scalar;
		return *this;
	}

	Vector2& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	// Calculate dot product of this and second vector.
	float Dot(const Vector2& vec) const
	{
		return x * y + vec.x * vec.y;
	}

	// Calculate length of the vector.
	float Length(void) const
	{
		return sqrtf(x * x + y * y);
	}

	// Calculate squared length of the vector.
	float LengthSquared(void) const
	{
		return x * x + y * y;
	}

	// Normalize this vector.
	void Normalize(void)
	{
		const float s = 1.0f / Length();
		x *= s;
		y *= s;
	}

	// Make normalized vector from this vector.
	Vector2 Normalized(void) const
	{
		Vector2 copy(*this);
		copy.Normalize();
		return copy;
	}

	// Negate current vector.
	void Negate(void)
	{
		x = -x;
		y = -y;
	}

	// Make nagated vector from this vector.
	Vector2 Negated(void) const
	{
		Vector2 copy(*this);
		copy.Negate();
		return copy;
	}

	// Rotate vector by given radian rotation.
	void Rotate(const float angle)
	{
		const float cos = cosf(angle);
		const float sin = sinf(angle);

		Vector2 tmp(*this);
		x = tmp.x * cos - tmp.y * sin;
		y = tmp.x * sin + tmp.y * cos;
	}

	// Make rotated vector by given radian rotation.
	Vector2 Rotated(const float angle) const
	{
		Vector2 copy(*this);
		copy.Rotate(angle);
		return copy;
	}

	/**
	 * Linear interpolation between this and @a end vector.
	 *
	 * @param[out] out  The destination vector where interpolated value will be stored.
	 * @param[in]  end  The end vector used for interpolation.
	 * @param[in] alpha The alpha used for interpolation. (Can be out of 0.0 - 1.0 range)
	 */
	void Lerp(Vector2& out, const Vector2& end, const float alpha) const
	{
		out.x = x * (1.0f - alpha) + end.x * alpha;
		out.y = y * (1.0f - alpha) + end.y * alpha;
	}

	// Calculate distance between this and b.
	float Distance(const Vector2& b) const
	{
		return (b - *this).Length();
	}

	// Create vector with the biggest components.
	static Vector2 Max(const Vector2& a, const Vector2& b)
	{
		Vector2 vec;

		if (a.x > b.x) vec.x = a.x;
		else vec.x = b.x;

		if (a.y > b.y) vec.y = a.y;
		else vec.y = b.y;
		return vec;
	}

	// Create vector with the smallest components.
	static Vector2 Min(const Vector2& a, const Vector2& b)
	{
		Vector2 vec;

		if (a.x < b.x) vec.x = a.x;
		else vec.x = b.x;

		if (a.y < b.y) vec.y = a.y;
		else vec.y = b.y;
		return vec;
	}

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 UnitX;
	static const Vector2 UnitY;

	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Right;
	static const Vector2 Left;
};

using Point = Vector2;

/* eof */
