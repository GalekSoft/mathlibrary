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
#include "MathLib.h"
#include "BSphere.h"

namespace NGTech
{
	BSphere operator*(const Mat4& a, const BSphere& s)
	{
		BSphere result;
		result.center = (*a) * s.center;
		result.radius = s.radius;
		return result;
	}
}