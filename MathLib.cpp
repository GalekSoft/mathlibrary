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
//***************************************************************************
#include "CommonPrivate.h"
//***************************************************************************
#include "MathLib.h"
//***************************************************************************

namespace NGTech {
	//**************************************
	const float Math::ZEROFLOAT(0.0f);
	const float Math::ONEFLOAT(1.0f);

	const TimeDelta Math::ZERODELTA(TimeDelta(0.0));
	const TimeDelta Math::ONEDELTA(TimeDelta(1.0));

	const Vec3 Math::X_AXIS(Vec3(1.0, 0.0, 0.0));
	const Vec3 Math::Y_AXIS(Vec3(0.0, 1.0, 0.0));
	const Vec3 Math::Z_AXIS(Vec3(0.0, 0.0, 1.0));
	//**************************************

	float Math::angleBetweenVec(const Vec3 &a, const Vec3 &b) {
		Vec3 va = a;
		Vec3 vb = b;
		float dot = Vec3::dot(va, vb);
		float length = va.length() * vb.length();

		float angle = acos(dot / length);

		if (angle < EPSILON)
			return Math::ZEROFLOAT;

		return angle;
	}

	bool Math::intersectPlaneByRay(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, const Vec3 &src, const Vec3 &dst, Vec3 &point) {
		Vec3 normal;
		float distance;
		float distance1 = 0, distance2 = 0;

		TBNComputer::computeN(normal, v0, v1, v2);
		distance = -((normal.x * v0.x) + (normal.y * v0.y) + (normal.z * v0.z));

		distance1 = ((normal.x * src.x) + (normal.y * src.y) + (normal.z * src.z)) + distance;
		distance2 = ((normal.x * dst.x) + (normal.y * dst.y) + (normal.z * dst.z)) + distance;

		if (distance1 <= Math::ZERODELTA) {
			return false;
		}

		Vec3 lineDir;
		double n = 0.0, d = 0.0, dist = 0.0;

		lineDir = Vec3::normalize(dst - src);

		n = -(normal.x * src.x + normal.y * src.y + normal.z * src.z + distance);
		d = Vec3::dot(normal, lineDir);

		if (d == Math::ZERODELTA) {
			point = src;
		}

		dist = n / d;
		point.x = (float)(src.x + (lineDir.x * dist));
		point.y = (float)(src.y + (lineDir.y * dist));
		point.z = (float)(src.z + (lineDir.z * dist));

		return true;
	}

	bool Math::insidePolygon(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, const Vec3 &point) {
		const double MATCH_FACTOR = 0.99;
		double angle = 0.0;
		Vec3 a, b;

		a = v0 - point;
		b = v1 - point;
		angle += angleBetweenVec(a, b);

		a = v1 - point;
		b = v2 - point;
		angle += angleBetweenVec(a, b);

		a = v2 - point;
		b = v0 - point;
		angle += angleBetweenVec(a, b);

		if (angle >= (MATCH_FACTOR * (2.0 * M_PI))) {
			return true;
		}

		return false;
	}

	bool Math::intersectPolygonByRay(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, const Vec3 &src, const Vec3 &dst, Vec3 &point) {
		if (!intersectPlaneByRay(v0, v1, v2, src, dst, point))
			return false;

		if (insidePolygon(v0, v1, v2, point))
			return true;

		return false;
	}

	bool Math::intersectSphereByRay(const Vec3 &center, float radius, const Vec3 &src, const Vec3 &dst) {
		Vec3 v1 = center - src;
		Vec3 v2 = Vec3::normalize(dst - src);

		float t = Vec3::dot(v2, v1);

		if (t <= 0 && (center - src).length() > radius)
			return false;

		Vec3 v3 = v2 * t;
		Vec3 cp = src + v3;

		return (cp - center).length() < radius;
	}

	/*
	*/
	Mat3::Mat3() {
		Identity();
	}

	Mat3::~Mat3() {}

	void Mat3::Identity() {
		e[0] = Math::ONEFLOAT; e[3] = Math::ZEROFLOAT; e[6] = Math::ZEROFLOAT;
		e[1] = Math::ZEROFLOAT; e[4] = Math::ONEFLOAT; e[7] = Math::ZEROFLOAT;
		e[2] = Math::ZEROFLOAT; e[5] = Math::ZEROFLOAT; e[8] = Math::ONEFLOAT;
	}

	void Mat3::SetZero() {
		e[0] = Math::ZEROFLOAT; e[3] = Math::ZEROFLOAT; e[6] = Math::ZEROFLOAT;
		e[1] = Math::ZEROFLOAT; e[4] = Math::ZEROFLOAT; e[7] = Math::ZEROFLOAT;
		e[2] = Math::ZEROFLOAT; e[5] = Math::ZEROFLOAT; e[8] = Math::ZEROFLOAT;
	}

	Mat3::Mat3(float e0, float e3, float e6,
		float e1, float e4, float e7,
		float e2, float e5, float e8) {
		e[0] = e0; e[3] = e3; e[6] = e6;
		e[1] = e1; e[4] = e4; e[7] = e7;
		e[2] = e2; e[5] = e5; e[8] = e8;
	}

	Mat3::Mat3(const Mat3 &in) {
		e[0] = in.e[0]; e[3] = in.e[3]; e[6] = in.e[6];
		e[1] = in.e[1]; e[4] = in.e[4]; e[7] = in.e[7];
		e[2] = in.e[2]; e[5] = in.e[5]; e[8] = in.e[8];
	}

	Mat3::Mat3(const Mat4 &in) {
		e[0] = in.e[0]; e[3] = in.e[4]; e[6] = in.e[8];
		e[1] = in.e[1]; e[4] = in.e[5]; e[7] = in.e[9];
		e[2] = in.e[2]; e[5] = in.e[6]; e[8] = in.e[10];
	}

	Mat3 &Mat3::operator=(const Mat3 &in) {
		e[0] = in.e[0]; e[3] = in.e[3]; e[6] = in.e[6];
		e[1] = in.e[1]; e[4] = in.e[4]; e[7] = in.e[7];
		e[2] = in.e[2]; e[5] = in.e[5]; e[8] = in.e[8];
		return *this;
	}

	Mat3 &Mat3::operator*=(const Mat3 &in) {
		*this = *this * in;
		return *this;
	}

	float &Mat3::operator[](intptr_t index) {
		return e[index];
	}

	float Mat3::operator[](intptr_t index) const {
		return e[index];
	}

	Mat3::operator float*() {
		return &e[0];
	}

	Mat3::operator const float*() const {
		return &e[0];
	}

	float Mat3::getDeterminant() {
		float d;
		d = e[0] * e[4] * e[8];
		d += e[3] * e[7] * e[2];
		d += e[6] * e[1] * e[5];
		d -= e[6] * e[4] * e[2];
		d -= e[3] * e[1] * e[8];
		d -= e[0] * e[7] * e[5];
		return d;
	}

	Mat3 Mat3::transpose(const Mat3 &m) {
		return Mat3(m.e[0], m.e[1], m.e[2],
			m.e[3], m.e[4], m.e[5],
			m.e[6], m.e[7], m.e[8]);
	}

	Mat3 Mat3::inverse(const Mat3 &m) {
		Mat3 iMat = m;

		float iDet = Math::ONEFLOAT / iMat.getDeterminant();

		iMat.e[0] = (m.e[4] * m.e[8] - m.e[7] * m.e[5]) * iDet;
		iMat.e[1] = -(m.e[1] * m.e[8] - m.e[7] * m.e[2]) * iDet;
		iMat.e[2] = (m.e[1] * m.e[5] - m.e[4] * m.e[2]) * iDet;
		iMat.e[3] = -(m.e[3] * m.e[8] - m.e[6] * m.e[5]) * iDet;
		iMat.e[4] = (m.e[0] * m.e[8] - m.e[6] * m.e[2]) * iDet;
		iMat.e[5] = -(m.e[0] * m.e[5] - m.e[3] * m.e[2]) * iDet;
		iMat.e[6] = (m.e[3] * m.e[7] - m.e[6] * m.e[4]) * iDet;
		iMat.e[7] = -(m.e[0] * m.e[7] - m.e[6] * m.e[1]) * iDet;
		iMat.e[8] = (m.e[0] * m.e[4] - m.e[3] * m.e[1]) * iDet;
		return iMat;
	}

	Mat3 Mat3::rotate(float angle, const Vec3 &axis) {
		float s = sinf(Math::DegreesToRadians(angle));
		float c = cosf(Math::DegreesToRadians(angle));

		Mat3 rMat;

		float ux = axis.x;
		float uy = axis.y;
		float uz = axis.z;

		rMat.e[0] = c + (1 - c) * ux;
		rMat.e[1] = (1 - c) * ux*uy + s * uz;
		rMat.e[2] = (1 - c) * ux*uz - s * uy;

		rMat.e[3] = (1 - c) * uy*ux - s * uz;
		rMat.e[4] = c + (1 - c) * uy * uy;
		rMat.e[5] = (1 - c) * uy*uz + s * ux;

		rMat.e[6] = (1 - c) * uz*ux + s * uy;
		rMat.e[7] = (1 - c) * uz*uz - s * ux;
		rMat.e[8] = c + (1 - c) * uz * uz;

		return rMat;
	}

	Mat3 Mat3::scale(const Vec3 &scale) {
		Mat3 sMat;

		sMat.e[0] = scale.x;
		sMat.e[4] = scale.y;
		sMat.e[8] = scale.z;

		return sMat;
	}

	Mat3 operator*(const Mat3 &a, const Mat3 &b) {
		Mat3 result;

		result.e[0] = a.e[0] * b.e[0] + a.e[3] * b.e[1] + a.e[6] * b.e[2];
		result.e[1] = a.e[1] * b.e[0] + a.e[4] * b.e[1] + a.e[7] * b.e[2];
		result.e[2] = a.e[2] * b.e[0] + a.e[5] * b.e[1] + a.e[8] * b.e[2];
		result.e[3] = a.e[0] * b.e[3] + a.e[3] * b.e[4] + a.e[6] * b.e[5];
		result.e[4] = a.e[1] * b.e[3] + a.e[4] * b.e[4] + a.e[7] * b.e[5];
		result.e[5] = a.e[2] * b.e[3] + a.e[5] * b.e[4] + a.e[8] * b.e[5];
		result.e[6] = a.e[0] * b.e[6] + a.e[3] * b.e[7] + a.e[6] * b.e[8];
		result.e[7] = a.e[1] * b.e[6] + a.e[4] * b.e[7] + a.e[7] * b.e[8];
		result.e[8] = a.e[2] * b.e[6] + a.e[5] * b.e[7] + a.e[8] * b.e[8];

		return result;
	}

	Vec4 operator*(const Mat3 &m, const Vec4 &v) {
		Vec4 result;
		result.x = m.e[0] * v.x + m.e[3] * v.y + m.e[6] * v.z;
		result.y = m.e[1] * v.x + m.e[4] * v.y + m.e[7] * v.z;
		result.z = m.e[2] * v.x + m.e[5] * v.y + m.e[8] * v.z;
		result.w = v.w;
		return result;
	}

	Vec4 operator*(const Vec4 &v, const Mat3 &m) {
		Vec4 result;
		result.x = m.e[0] * v.x + m.e[3] * v.y + m.e[6] * v.z;
		result.y = m.e[1] * v.x + m.e[4] * v.y + m.e[7] * v.z;
		result.z = m.e[2] * v.x + m.e[5] * v.y + m.e[8] * v.z;
		result.w = v.w;
		return result;
	}

	Vec3 operator*(const Mat3 &m, const Vec3 &v) {
		Vec3 result;
		result.x = m.e[0] * v.x + m.e[3] * v.y + m.e[6] * v.z;
		result.y = m.e[1] * v.x + m.e[4] * v.y + m.e[7] * v.z;
		result.z = m.e[2] * v.x + m.e[5] * v.y + m.e[8] * v.z;
		return result;
	}

	Vec3 operator*(const Vec3 &v, const Mat3 &m) {
		Vec3 result;
		result.x = m.e[0] * v.x + m.e[3] * v.y + m.e[6] * v.z;
		result.y = m.e[1] * v.x + m.e[4] * v.y + m.e[7] * v.z;
		result.z = m.e[2] * v.x + m.e[5] * v.y + m.e[8] * v.z;
		return result;
	}

	/*
	*/
	void TBNComputer::computeN(Vec3 &n, const Vec3& p0, const Vec3& p1, const Vec3& p2) {
		Vec3 s = p1 - p0;
		Vec3 t = p2 - p0;
		Vec3 normal = Vec3::cross(s, t);

		n = normal;
	}

	void TBNComputer::computeTBN(Vec3 &t, Vec3 &b, const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec2& t0, const Vec2& t1, const Vec2& t2, const Vec3& n) {
		Vec3 position[3];
		Vec2 texcoords[3];

		Vec3 tangent;
		Vec3 binormal;
		Vec3 normal;

		normal = n;
		position[0] = p0;
		position[1] = p1;
		position[2] = p2;

		texcoords[0] = t0;
		texcoords[1] = t1;
		texcoords[2] = t2;

		Vec3 e0(position[1].x - position[0].x,
			texcoords[1].x - texcoords[0].x,
			texcoords[1].y - texcoords[0].y);
		Vec3 e1(position[2].x - position[0].x,
			texcoords[2].x - texcoords[0].x,
			texcoords[2].y - texcoords[0].y);

		Vec3 cp = Vec3::cross(e0, e1);

		if (fabs(cp.x) > EPSILON) {
			tangent.x = -cp.y / cp.x;
			binormal.x = -cp.z / cp.x;
		}
		else {
			tangent.x = 0;
			binormal.x = 0;
		}

		e0.x = position[1].y - position[0].y;
		e1.x = position[2].y - position[0].y;
		cp = Vec3::cross(e0, e1);

		// TODO:CHECK REPLACE ON OWN FUNCTION
		if (fabs(cp.x) > EPSILON) {
			tangent.y = -cp.y / cp.x;
			binormal.y = -cp.z / cp.x;
		}
		else {
			tangent.y = 0;
			binormal.y = 0;
		}

		e0.x = position[1].z - position[0].z;
		e1.x = position[2].z - position[0].z;
		cp = Vec3::cross(e0, e1);

		if (fabs(cp.x) > EPSILON) {
			tangent.z = -cp.y / cp.x;
			binormal.z = -cp.z / cp.x;
		}
		else {
			tangent.z = 0;
			binormal.z = 0;
		}

		Vec3 temp = Vec3(tangent.y * binormal.z - tangent.z * binormal.y,
			tangent.z * binormal.x - tangent.x * binormal.z,
			tangent.x * binormal.y - tangent.y * binormal.x);
		TimeDelta scalar = normal.x * temp.x + normal.y * temp.y + normal.z * temp.z;

		//!@todo CHECK, check it's with eps
		if (scalar < 0) tangent = -tangent;

		t = tangent;
		b = binormal;
	}
}