// Copyright (C) 2016 by Rage MP Team

#include "Entity.h"

CVector CEntity::GetPosition(void) const
{
	if (m_matrixLink) {
		const CMatrix &matrix = *m_matrixLink;
		return CVector(matrix(3, 0), matrix(3, 1), matrix(3, 2));
	}
	return m_position;
}

/* eof */
