/* Copyright (C) 2009-2020, Nick Galko Ltd. All rights reserved.
*
* This file is part of the NGTech (https://galek.github.io/portfolio/).
*
* Your use and or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the NGTech License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the NGTech License Agreement is available by contacting
* Nick Galko Ltd. at https://galek.github.io/portfolio/
*/
#pragma once

#if IS_NGTECH_BUILD
#include "../../Platform/inc/platformdetect.h"
#else

//***************************************************************************
#include <assert.h>
//***************************************************************************

#ifndef ENGINE_INLINE
#define ENGINE_INLINE inline
#endif

#ifndef USE_SINGLE_PRECISION
#define USE_SINGLE_PRECISION 1
#endif

#if USE_SINGLE_PRECISION
typedef float TimeDelta;
#else
typedef double TimeDelta;
#endif

#ifndef ASSERT(x, ...)
#define ASSERT(x, ...) assert(x, __VA_ARGS__)
#endif


#endif // IS_NGTECH_BUILD