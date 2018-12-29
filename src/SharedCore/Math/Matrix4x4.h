// Copyright (C) 2016 by DVO Games

#pragma once

#include "Debug/Debug.h"

/**
 * The matrix 4x4 class.
 */
class Matrix4x4
{
private:
	/** The matrix data */
	float		m_data[4][4];
public:
	/** Setup identity matrix */
	Matrix4x4(void)
	{
		Identity();
	}

	/** Setup identity matrix */
	Matrix4x4(const Matrix4x4 &mat)
	{
		for (size_t x = 0; x < 4; ++x) {
			for (size_t y = 0; y < 4; ++y) {
				m_data[x][y] = mat(x, y);
			}
		}
	}

	/** Setup transform matrix*/
	Matrix4x4(const float x, const float y, const float z)
	{
		Identity();

		m_data[3][0] = x;
		m_data[3][1] = y;
		m_data[3][2] = z;
	}

	/** Make this matrix identity */
	void Identity(void)
	{
		for (size_t x = 0; x < 4; ++x) {
			for (size_t y = 0; y < 4; ++y) {
				const float value = x == y ? 1.0f : 0.0f;
				m_data[x][y] = value;
			}
		}
	}

	/** Get matrix data stored inside this matrix. */
	const float *GetData(void) const
	{
		return &m_data[0][0];
	}

	/** Get matrix scalar at x and y */
	float& operator()(const size_t x, const size_t y)
	{
		ASSERT(x < 4 && y < 4);
		return m_data[x][y];
	}

	/** Get matrix scalar at x and y */
	const float operator()(const size_t x, const size_t y) const
	{
		ASSERT(x < 4 && y < 4);
		return m_data[x][y];
	}

	/** Make product of two matrices */
	void operator*=(const Matrix4x4 &mat)
	{
		Matrix4x4 me(*this);

		// Not sure if correct.
		m_data[0][0] = me(0, 0) * mat(0, 0) + me(0, 1) * mat(1, 0) + me(0, 2) * mat(2, 0) + me(0, 3) * mat(3, 0);
		m_data[0][1] = me(0, 0) * mat(0, 1) + me(0, 1) * mat(1, 1) + me(0, 2) * mat(2, 1) + me(0, 3) * mat(3, 1);
		m_data[0][2] = me(0, 0) * mat(0, 2) + me(0, 1) * mat(1, 2) + me(0, 2) * mat(2, 2) + me(0, 3) * mat(3, 2);
		m_data[0][3] = me(0, 0) * mat(0, 3) + me(0, 1) * mat(1, 3) + me(0, 2) * mat(2, 3) + me(0, 3) * mat(3, 3);

		m_data[1][0] = me(1, 0) * mat(0, 0) + me(1, 1) * mat(1, 0) + me(1, 2) * mat(2, 0) + me(1, 3) * mat(3, 0);
		m_data[1][1] = me(1, 0) * mat(0, 1) + me(1, 1) * mat(1, 1) + me(1, 2) * mat(2, 1) + me(1, 3) * mat(3, 1);
		m_data[1][2] = me(1, 0) * mat(0, 2) + me(1, 1) * mat(1, 2) + me(1, 2) * mat(2, 2) + me(1, 3) * mat(3, 2);
		m_data[1][3] = me(1, 0) * mat(0, 3) + me(1, 1) * mat(1, 3) + me(1, 2) * mat(2, 3) + me(1, 3) * mat(3, 3);

		m_data[2][0] = me(2, 0) * mat(0, 0) + me(2, 1) * mat(1, 0) + me(2, 2) * mat(2, 0) + me(2, 3) * mat(3, 0);
		m_data[2][1] = me(2, 0) * mat(0, 1) + me(2, 1) * mat(1, 1) + me(2, 2) * mat(2, 1) + me(2, 3) * mat(3, 1);
		m_data[2][2] = me(2, 0) * mat(0, 2) + me(2, 1) * mat(1, 2) + me(2, 2) * mat(2, 2) + me(2, 3) * mat(3, 2);
		m_data[2][3] = me(2, 0) * mat(0, 3) + me(2, 1) * mat(1, 3) + me(2, 2) * mat(2, 3) + me(2, 3) * mat(3, 3);

		m_data[3][0] = me(3, 0) * mat(0, 0) + me(3, 1) * mat(1, 0) + me(3, 2) * mat(2, 0) + me(3, 3) * mat(3, 0);
		m_data[3][1] = me(3, 0) * mat(0, 1) + me(3, 1) * mat(1, 1) + me(3, 2) * mat(2, 1) + me(3, 3) * mat(3, 1);
		m_data[3][2] = me(3, 0) * mat(0, 2) + me(3, 1) * mat(1, 2) + me(3, 2) * mat(2, 2) + me(3, 3) * mat(3, 2);
		m_data[3][3] = me(3, 0) * mat(0, 3) + me(3, 1) * mat(1, 3) + me(3, 2) * mat(2, 3) + me(3, 3) * mat(3, 3);
	}

	/** Make product of two matrices */
	Matrix4x4& operator*(const Matrix4x4 &mat)
	{
		Matrix4x4 copy(*this);
		copy *= mat;
		return copy;
	}
};
/* eof */
