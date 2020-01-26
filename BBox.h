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
#include <limits>
#include <algorithm>
#undef max
#undef min
//***************************************************************************
#include "MathLib.h"
//***************************************************************************

namespace NGTech
{
	/**
	Bounding box
	*/
	class BBox
	{
	public:
		Vec3 mins, maxes;

		/**
		*/
		BBox()
		{
			mins = Vec3(-Math::ONEFLOAT, -Math::ONEFLOAT, -Math::ONEFLOAT);
			maxes = Vec3(Math::ONEFLOAT, Math::ONEFLOAT, Math::ONEFLOAT);
			_ComputeCenter();
		}

		/**
		*/
		BBox(const Vec3 &_min, const Vec3 &_max) :
			mins(_min),
			maxes(_max)
		{
			_ComputeCenter();
		}

		/**
		*/
		BBox(const BBox &_box) :
			mins(_box.mins),
			maxes(_box.maxes),
			m_vCenter(_box.m_vCenter),
			m_vCenterHalf(_box.m_vCenterHalf)
		{}

		/**
		*/
		ENGINE_INLINE BBox &operator=(const BBox &_box)
		{
			if (this != &_box)
			{
				mins = _box.mins;
				maxes = _box.maxes;
				m_vCenter = _box.m_vCenter;
				m_vCenterHalf = _box.m_vCenterHalf;
			}

			return *this;
		}

		ENGINE_INLINE bool operator==(const BBox& _box) {
			return (mins == _box.mins)
				&& (maxes == _box.maxes)
				&& (m_vCenter == _box.m_vCenter)
				&& (m_vCenterHalf == _box.m_vCenterHalf);
		}

		/**
		*/
		ENGINE_INLINE void AddPoint(const Vec3 &point)
		{
			if (maxes.x < point.x) maxes.x = point.x;
			if (maxes.y < point.y) maxes.y = point.y;
			if (maxes.z < point.z) maxes.z = point.z;

			if (mins.x > point.x) mins.x = point.x;
			if (mins.y > point.y) mins.y = point.y;
			if (mins.z > point.z) mins.z = point.z;

			_ComputeCenter();
		}

		ENGINE_INLINE void GetPoints(Vec3 *points, int num_points) const {
			points[0].Set(mins.x, mins.y, mins.z);
			points[1].Set(maxes.x, mins.y, mins.z);
			points[2].Set(mins.x, maxes.y, mins.z);
			points[3].Set(maxes.x, maxes.y, mins.z);
			points[4].Set(mins.x, mins.y, maxes.z);
			points[5].Set(maxes.x, mins.y, maxes.z);
			points[6].Set(mins.x, maxes.y, maxes.z);
			points[7].Set(maxes.x, maxes.y, maxes.z);
		}

		/**
		*/
		ENGINE_INLINE void AddBBox(const BBox &box)
		{
			if (maxes.x < box.maxes.x) maxes.x = box.maxes.x;
			if (maxes.y < box.maxes.y) maxes.y = box.maxes.y;
			if (maxes.z < box.maxes.z) maxes.z = box.maxes.z;

			if (mins.x > box.mins.x) mins.x = box.mins.x;
			if (mins.y > box.mins.y) mins.y = box.mins.y;
			if (mins.z > box.mins.z) mins.z = box.mins.z;

			_ComputeCenter();
		}

		/**
		*/
		ENGINE_INLINE bool IsPointInside(const Vec3 &point)
		{
			return (point.x >= mins.x && point.x <= maxes.x &&
				point.y >= mins.y && point.y <= maxes.y &&
				point.z >= mins.z && point.z <= maxes.z);
		}

		/**
		*/
		ENGINE_INLINE const Vec3& GetCenter() const
		{
			return m_vCenter;
		}

		/**
		*/
		ENGINE_INLINE const Vec3& GetHalfSize() const
		{
			return m_vCenterHalf;
		}

		/**
		*/
		ENGINE_INLINE float GetCenterLength()
		{
			return m_vCenter.length();
		}

		/**
		*/
		ENGINE_INLINE float GetHalfSizeLength()
		{
			return m_vCenterHalf.length();
		}

		/**
		 sets mins to std::numeric_limits<float>::max() and maxes to -std::numeric_limits<float>::max()
		 */
		ENGINE_INLINE void Clear()
		{
			mins.SetMax();
			maxes.SetMin();
			_ComputeCenter();
		}

		void Inflate(const Vec3 &point);

		/**
		*/
		ENGINE_INLINE float Radius() const
		{
			return (mins - maxes).length() * 0.5f;
		}

		/**
		*/
		ENGINE_INLINE void TransformAxisAligned(const Mat4& traf)
		{
			Vec3 vertices[8] =
			{
				{ mins[0], mins[1], mins[2] },
				{ mins[0], mins[1], maxes[2] },
				{ mins[0], maxes[1], mins[2] },
				{ mins[0], maxes[1], maxes[2] },
				{ maxes[0], mins[1], mins[2] },
				{ maxes[0], mins[1], maxes[2] },
				{ maxes[0], maxes[1], mins[2] },
				{ maxes[0], maxes[1], maxes[2] }
			};

			for (int i = 0; i < 8; ++i)
				Utils::TransformCoord(vertices[i], vertices[i], traf);

			mins[0] = mins[1] = mins[2] = std::numeric_limits<float>::max();
			maxes[0] = maxes[1] = maxes[2] = -std::numeric_limits<float>::max();

			for (int i = 0; i < 8; ++i)
				AddPoint(vertices[i]);
		}

		/**
		*/
		ENGINE_INLINE float Nearest(const Vec4& from) const
		{
#define ASGN_IF(a, op, b) \
	if( (a) op (b) ) (a) = (b);

#define FAST_DISTANCE(_x, _y, _z, _p, _op) \
	d = from.x * _x + from.y * _y + from.z * _z + from.w; \
	ASGN_IF(dist, _op, d);
			// END

			float d, dist = std::numeric_limits<float>::max();

			FAST_DISTANCE(mins.x, mins.y, mins.z, from, > );
			FAST_DISTANCE(mins.x, mins.y, maxes.z, from, > );
			FAST_DISTANCE(mins.x, maxes.y, mins.z, from, > );
			FAST_DISTANCE(mins.x, maxes.y, maxes.z, from, > );
			FAST_DISTANCE(maxes.x, mins.y, mins.z, from, > );
			FAST_DISTANCE(maxes.x, mins.y, maxes.z, from, > );
			FAST_DISTANCE(maxes.x, maxes.y, mins.z, from, > );
			FAST_DISTANCE(maxes.x, maxes.y, maxes.z, from, > );

			return dist;

#undef FAST_DISTANCE
#undef ASGN_IF
		}

		/**
		*/
		ENGINE_INLINE float Farthest(const Vec4& from) const
		{
#define ASGN_IF(a, op, b) \
	if( (a) op (b) ) (a) = (b);

#define FAST_DISTANCE(_x, _y, _z, _p, _op) \
	d = from.x * _x + from.y * _y + from.z * _z + from.w; \
	ASGN_IF(dist, _op, d);

			float d, dist = -std::numeric_limits<float>::max();

			FAST_DISTANCE(mins.x, mins.y, mins.z, from, < );
			FAST_DISTANCE(mins.x, mins.y, maxes.z, from, < );
			FAST_DISTANCE(mins.x, maxes.y, mins.z, from, < );
			FAST_DISTANCE(mins.x, maxes.y, maxes.z, from, < );
			FAST_DISTANCE(maxes.x, mins.y, mins.z, from, < );
			FAST_DISTANCE(maxes.x, mins.y, maxes.z, from, < );
			FAST_DISTANCE(maxes.x, maxes.y, mins.z, from, < );
			FAST_DISTANCE(maxes.x, maxes.y, maxes.z, from, < );

			return dist;

#undef FAST_DISTANCE
#undef ASGN_IF
		}

		/**
		*/
		ENGINE_INLINE void FitToBox(float& outnear, float& outfar, const Vec3&eye, const Vec3&look)
		{
			Vec4 refplane;

			refplane.x = look.x - eye.x;
			refplane.y = look.y - eye.y;
			refplane.z = look.z - eye.z;
			refplane.w = -(refplane.x * eye.x + refplane.y * eye.y + refplane.z * eye.z);

			refplane.Normalize();

			outnear = Nearest(refplane) - 0.02f;	// 2mm
			outfar = Farthest(refplane) + 0.02f;	// 2mm

			outnear = std::max<float>(outnear, 0.1f);
			outfar = std::max<float>(outfar, 0.2f);
		}
	private:
		void	_ComputeCenter();
	private:
		Vec3	m_vCenter;
		Vec3	m_vCenterHalf;
	};
	extern BBox operator*(const Mat4 &a, const BBox &b);
}
