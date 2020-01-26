/* Copyright (C) 2009-2020, NG Games (Galek Studios) Ltd. All rights reserved.
*
* This file is part of the NGTech (https://galek.github.io/portfolio/).
*
* Your use and or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the NGTech License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the NGTech License Agreement is available by contacting
* NG Games(Galek Studios) Ltd. at https://galek.github.io/portfolio/
*/

#include "MathLib.h"
#include "BBox.h"

namespace NGTech
{
	BBox operator*(const Mat4 &a, const BBox &b) {
		BBox result;
		result.mins = (*a) * b.mins;
		result.maxes = (*a) * b.maxes;
		return result;
	}

	void BBox::Inflate(const Vec3 &point)
	{
		if (point.x < mins.x)
			mins.x = point.x;
		if (point.y < mins.y)
			mins.y = point.y;
		if (point.z < mins.z)
			mins.z = point.z;
		if (point.x > maxes.x)
			maxes.x = point.x;
		if (point.y > maxes.y)
			maxes.y = point.y;
		if (point.z > maxes.z)
			maxes.z = point.z;
	}

	void BBox::_ComputeCenter()
	{
		m_vCenter = (mins + maxes) * 0.5f;
		m_vCenterHalf = (maxes - mins) * 0.5f;
	}
}