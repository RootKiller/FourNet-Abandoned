// Copyright (C) 2016 by DVO Games

#pragma once

#if defined(_WIN32) && (! defined(_WIN64))

#define PF_SIZE_T "Iu"

#elif defined(_WIN64)

#define PF_SIZE_T "zu"

#endif

#define PF_SINT64 "lld"

/* eof */
