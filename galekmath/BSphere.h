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

//***************************************************************************
#include <math.h>
//***************************************************************************
#include "MathLib.h"
//***************************************************************************

namespace NGTech
{
	/**
	Bounding sphere
	*/
	class BSphere
	{
	public:
		Vec3 center;
		float radius;

		/**
		*/
		BSphere()
			:center(Vec3(-Math::ZEROFLOAT, -Math::ZEROFLOAT, -Math::ZEROFLOAT)), radius(Math::ONEFLOAT)
		{}

		/**
		*/
		BSphere(const Vec3& _center, float _radius)
			: center(_center), radius(_radius)
		{}

		/**
		*/
		BSphere(const BSphere& sphere)
			: center(sphere.center), radius(sphere.radius)
		{}

		/**
		*/
		ENGINE_INLINE BSphere& operator=(const BSphere& sphere)
		{
			if (this != &sphere)
			{
				center = sphere.center;
				radius = sphere.radius;
			}

			return *this;
		}

		ENGINE_INLINE bool operator==(const BSphere& sphere) {
			return (center == sphere.center)
				&& (Math::IsEqual(radius, sphere.radius));
		}

		/**
		*/
		ENGINE_INLINE void AddPoint(const Vec3& point)
		{
			Vec3 d = point - center;
			float length = d.length();

			if (radius < length)
			{
				radius = length;
			}
		}

		/**
		*/
		ENGINE_INLINE void AddSphere(const BSphere& sphere)
		{
			Vec3 dc = sphere.center - center;
			float lc = dc.length();
			float dr = sphere.radius - radius;

			radius = 0.5f * (radius + sphere.radius + lc);
			center = (center + dc * (0.5f * (lc + dr) / lc));
		}

		/**
		*/
		ENGINE_INLINE bool IsPointInside(const Vec3& point)
		{
			return (point - center).length() < radius;
		}

		/**
		*/
		ENGINE_INLINE bool IntersectsSphere(const BSphere& sphere)
		{
			return (center - sphere.center).length() <= (radius + sphere.radius);
		}
	};

	extern BSphere operator*(const Mat4& a, const BSphere& s);
}
