// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Math/Matrix.h"
#include "Types.h"

class CVector
{
public:
	float x, y, z;

	CVector(const float theX, const float theY, const float theZ)
		: x(theX)
		, y(theY)
		, z(theZ)
	{
	}
};

#include "Math/Matrix.h"

class CEntity
{
public:
	virtual			~CEntity		() = 0;
	virtual void	SetMatrix		(const CMatrix &matrix, const int unknown, const int unknown2)		= 0;
	virtual void	SetPosition		(const CVector &position, const int unknown, const int unknown2)	= 0;
	virtual void	SetRotationZ	(const float newRotation) = 0; // Seems to not work on peds.. probably not used at all in game(?)
	// TODO: Rest of the vtable elements.

	/** Our helper method to get entity position */
	CVector			GetPosition		(void) const;

	uint8							pad4[12];			// 0004 - 0016
	CVector							m_position;			// 0016 - 0028
	uint32							pad28;				// 0028 - 0032
	CMatrix							*m_matrixLink;		// 0032 - 0036
	uint32							m_unknownFlags36;	// 0036 - 0040 some flags?
	uint8							pad40[25];			// 0040 - 0065
	uint8							m_unknownByte65;	// 0065 - 0066 Set to 2 when creating ped.
	uint8							pad66[46];			// 0066 - 0112
};
static_assert(sizeof(CEntity) == 112, "Incorrect CEntity size");

/* eof */
