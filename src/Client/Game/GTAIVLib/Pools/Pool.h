// Copyright (C) 2016 by Rage MP Team

#pragma once

class CPool
{
public:
	void			*New_2			(void);

	static CPool	*TaskPoolInstance(void);
};

/* eof */
