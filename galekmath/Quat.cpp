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
//***************************************************************************
#include "MathLib.h"
//***************************************************************************

namespace NGTech {
	const Quat Quat::ZERO(0, 0, 0, 0);
	/*
	*/
	Quat::Quat() {
		Identity();
	}

	Quat::Quat(float angle, const Vec3 &axis) {
		Vec3 vdir = axis;
		float length = vdir.length();

		if (length != 0.0) {
			length = Math::ONEFLOAT / length;
			float sinangle = sin(Math::DegreesToRadians(angle / 2.0f));
			x = vdir.x * length * sinangle;
			y = vdir.y * length * sinangle;
			z = vdir.z * length * sinangle;
			w = cos(Math::DegreesToRadians(angle / 2.0f));
		}
		else {
			x = y = z = 0.0;
			w = 1.0;
		}
	}

	Quat::Quat(const Mat3 &in) {
		float trace = in.e[0] + in.e[4] + in.e[8];

		if (trace > 0.0) {
			float s = sqrt(trace + Math::ONEFLOAT);

			w = 0.5f * s;
			s = 0.5f / s;

			x = (in.e[5] - in.e[7]) * s;
			y = (in.e[6] - in.e[2]) * s;
			z = (in.e[1] - in.e[3]) * s;
		}
		else {
			static int next[3] = { 1, 2, 0 };
			float q[4];

			int i = 0;

			if (in.e[4] > in.e[0])
				i = 1;
			if (in.e[8] > in.e[3 * i + i])
				i = 2;

			int j = next[i];
			int k = next[j];

			float s = sqrt(in.e[3 * i + i] - in.e[3 * j + j] - in.e[3 * k + k] + Math::ONEFLOAT);
			q[i] = 0.5f * s;

			if (s != 0) s = 0.5f / s;

			q[3] = (in.e[3 * j + k] - in.e[3 * k + j]) * s;
			q[j] = (in.e[3 * i + j] + in.e[3 * j + i]) * s;
			q[k] = (in.e[3 * i + k] + in.e[3 * k + i]) * s;

			x = q[0];
			y = q[1];
			z = q[2];
			w = q[3];
		}
	}

	Quat::Quat(float _x, float _y, float _z, float _w)
		:x(_x), y(_y), z(_z), w(_w)
	{}

	Quat::operator float*() {
		return (float*)&x;
	}

	Quat::operator const float*() const {
		return (float*)&x;
	}

	float &Quat::operator[](intptr_t i) {
		return ((float*)&x)[i];
	}

	const float Quat::operator[](intptr_t i) const {
		return ((float*)&x)[i];
	}

	Quat Quat::operator*(const Quat &q) const {
		Quat ret;
		ret.x = w * q.x + x * q.x + y * q.z - z * q.y;
		ret.y = w * q.y + y * q.w + z * q.x - x * q.z;
		ret.z = w * q.z + z * q.w + x * q.y - y * q.x;
		ret.w = w * q.w - x * q.x - y * q.y - z * q.z;
		return ret;
	}

	Quat Quat::slerp(const Quat &q0, const Quat &q1, float t) {
		float k0, k1, cosomega = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;

		Quat q;
		if (cosomega < 0.0) {
			cosomega = -cosomega;
			q.x = -q1.x;
			q.y = -q1.y;
			q.z = -q1.z;
			q.w = -q1.w;
		}
		else {
			q.x = q1.x;
			q.y = q1.y;
			q.z = q1.z;
			q.w = q1.w;
		}

		if (1.0 - cosomega > 1e-6) {
			float omega = acos(cosomega);
			float sinomega = sin(omega);
			k0 = sin((Math::ONEFLOAT - t) * omega) / sinomega;
			k1 = sin(t * omega) / sinomega;
		}
		else {
			k0 = Math::ONEFLOAT - t;
			k1 = t;
		}
		q.x = q0.x * k0 + q.x * k1;
		q.y = q0.y * k0 + q.y * k1;
		q.z = q0.z * k0 + q.z * k1;
		q.w = q0.w * k0 + q.w * k1;

		return q;
	}

	Mat3 Quat::toMatrix() const {
		Mat3 r;
		float x2 = x + x;
		float y2 = y + y;
		float z2 = z + z;
		float xx = x * x2;
		float yy = y * y2;
		float zz = z * z2;
		float xy = x * y2;
		float yz = y * z2;
		float xz = z * x2;
		float wx = w * x2;
		float wy = w * y2;
		float wz = w * z2;

		r[0] = Math::ONEFLOAT - (yy + zz); r[3] = xy - wz;          r[6] = xz + wy;
		r[1] = xy + wz;          r[4] = Math::ONEFLOAT - (xx + zz); r[7] = yz - wx;
		r[2] = xz - wy;          r[5] = yz + wx;          r[8] = Math::ONEFLOAT - (xx + yy);
		return r;
	}
}