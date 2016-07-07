// Copyright (C) 2016 by DVO Games

#pragma once

#include "Vector2.h"

/**
 * Rectangle holding class.
 *
 * This class holds an rectangle
 */
class Rect
{
public:
	float left, top;
	float width, height;

	// Default constructor.
	Rect()
		: left(0.0f)
		, top(0.0f)
		, width(1.0f)
		, height(1.0f)
	{
	}

	// Constructor creating rectangle from all components.
	Rect(const float _left, const float _top, const float _width, const float _height)
		: left(_left)
		, top(_top)
		, width(_width)
		, height(_height)
	{
	}

	// Copy constructor.
	Rect(const Rect& rect)
	{
		(*this) = rect;
	}

	// Move constructor.
	Rect(Rect&& rect)
	{
		(*this) = rect;
	}

	// Copy assignment operator.
	Rect& operator=(const Rect& rect)
	{
		left = rect.left;
		top = rect.top;
		width = rect.width;
		height = rect.height;
		return *this;
	}

	// Move asignment operator.
	Rect& operator=(Rect&& rect)
	{
		left = rect.left;
		top = rect.top;
		width = rect.width;
		height = rect.height;
		return *this;
	}

	/**
	 * Check if point lies inside the rectangle.
	 *
	 * @param[in] x Point X coordinate.
	 * @param[in] y Point Y coordinate.
	 * @return @c true if point lies inside rectangle @c false otherwise.
	 */
	bool IsPointInside(const float x, const float y) const
	{
		return (x >= left) && (x <= (left + width)) && (y >= top) && (y <= (top + height));
	}

	/**
	 * Check if point lies inside the rectangle.
	 *
	 * @param[in] point The point.
	 * @return @c true if point lies inside rectangle @c false otherwise.
	 */
	bool IsPointInside(const Point& point) const
	{
		return (point.x >= left) && (point.x <= (left + width)) && (point.y >= top) && (point.y <= (top + height));
	}

	/**
	 * Check if rectangle A intersects another rectangle B.
	 *
	 * @param[in] rect The another rectangle.
	 * @return @c true if rectangle intersects @c false otherwise.
	 */
	bool Intersects(const Rect& rect) const
	{
		return rect.left < left + width && left < rect.left + rect.width && rect.top < top + height && top < rect.top + rect.height;
	}

	// Get center point of the rectangle.
	void GetCenter	(float& x, float& y) const
	{
		x = left + width / 2.0f;
		y = top + height / 2.0f;
	}

	// Compare two rectangles.
	bool operator==	(const Rect& rect)
	{
		return left == rect.left && top == rect.top && width == rect.width && height == rect.height;
	}

	// Compare two rectangles.
	bool operator!=	(const Rect& rect)
	{
		return !((*this) == rect);
	}

	// Get right value.
	float right(void) const
	{
		return left + width;
	}

	// Get bottom value.
	float bottom(void) const
	{
		return top + height;
	}
};

/* eof */
