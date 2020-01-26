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

namespace NGTech
{
	/**/
	const Mat4 Mat4::ZERO(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
	const Mat4 Mat4::ZEROAFFINE(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 1);
	const Mat4 Mat4::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	const Mat4 Mat4::CLIPSPACE2DTOIMAGESPACE(
		0.5, 0, 0, 0.5,
		0, -0.5, 0, 0.5,
		0, 0, 1, 0,
		0, 0, 0, 1);

	/**/
	Mat4::Mat4() {
		Identity();
	}

	Mat4::~Mat4() {}

	void Mat4::Identity() {
		e[0] = Math::ONEFLOAT; e[4] = Math::ZEROFLOAT; e[8] = Math::ZEROFLOAT; e[12] = Math::ZEROFLOAT;
		e[1] = Math::ZEROFLOAT; e[5] = Math::ONEFLOAT; e[9] = Math::ZEROFLOAT; e[13] = Math::ZEROFLOAT;
		e[2] = Math::ZEROFLOAT; e[6] = Math::ZEROFLOAT; e[10] = Math::ONEFLOAT; e[14] = Math::ZEROFLOAT;
		e[3] = Math::ZEROFLOAT; e[7] = Math::ZEROFLOAT; e[11] = Math::ZEROFLOAT; e[15] = Math::ONEFLOAT;
	}

	void Mat4::SetZero() {
		e[0] = Math::ZEROFLOAT; e[4] = Math::ZEROFLOAT; e[8] = Math::ZEROFLOAT; e[12] = Math::ZEROFLOAT;
		e[1] = Math::ZEROFLOAT; e[5] = Math::ZEROFLOAT; e[9] = Math::ZEROFLOAT; e[13] = Math::ZEROFLOAT;
		e[2] = Math::ZEROFLOAT; e[6] = Math::ZEROFLOAT; e[10] = Math::ZEROFLOAT; e[14] = Math::ZEROFLOAT;
		e[3] = Math::ZEROFLOAT; e[7] = Math::ZEROFLOAT; e[11] = Math::ZEROFLOAT; e[15] = Math::ZEROFLOAT;
	}

	Mat4::Mat4(float e0, float e4, float e8, float e12,
		float e1, float e5, float e9, float e13,
		float e2, float e6, float e10, float e14,
		float e3, float e7, float e11, float e15) {
		e[0] = e0; e[4] = e4; e[8] = e8;  e[12] = e12;
		e[1] = e1; e[5] = e5; e[9] = e9;  e[13] = e13;
		e[2] = e2; e[6] = e6; e[10] = e10; e[14] = e14;
		e[3] = e3; e[7] = e7; e[11] = e11; e[15] = e15;
	}

	Mat4::Mat4(const Mat4& in) {
		e[0] = in.e[0]; e[4] = in.e[4]; e[8] = in.e[8];  e[12] = in.e[12];
		e[1] = in.e[1]; e[5] = in.e[5]; e[9] = in.e[9];  e[13] = in.e[13];
		e[2] = in.e[2]; e[6] = in.e[6]; e[10] = in.e[10]; e[14] = in.e[14];
		e[3] = in.e[3]; e[7] = in.e[7]; e[11] = in.e[11]; e[15] = in.e[15];
	}

	Mat4::Mat4(const Mat3& in) {
		e[0] = in.e[0]; e[4] = in.e[3]; e[8] = in.e[6];  e[12] = 0.0;
		e[1] = in.e[1]; e[5] = in.e[4]; e[9] = in.e[7];  e[13] = 0.0;
		e[2] = in.e[2]; e[6] = in.e[5]; e[10] = in.e[8]; e[14] = 0.0;
		e[3] = 0.0;  e[7] = 0.0;  e[11] = 0.0;  e[15] = 1.0;
	}

	Mat4& Mat4::operator=(const Mat4& in) {
		e[0] = in.e[0]; e[4] = in.e[4]; e[8] = in.e[8];  e[12] = in.e[12];
		e[1] = in.e[1]; e[5] = in.e[5]; e[9] = in.e[9];  e[13] = in.e[13];
		e[2] = in.e[2]; e[6] = in.e[6]; e[10] = in.e[10]; e[14] = in.e[14];
		e[3] = in.e[3]; e[7] = in.e[7]; e[11] = in.e[11]; e[15] = in.e[15];
		return *this;
	}

	Mat4& Mat4::operator*=(const Mat4& in) {
		*this = *this * in;
		return *this;
	}

	float& Mat4::operator[](intptr_t index) {
		return e[index];
	}

	float Mat4::operator[](intptr_t index) const {
		return e[index];
	}

	Mat4::operator float* () {
		return &e[0];
	}

	Mat4::operator const float* () const {
		return &e[0];
	}

	float Mat4::getDeterminant() {
		float d;
		d = e[0] * e[5] * e[10];
		d += e[4] * e[9] * e[2];
		d += e[8] * e[1] * e[6];
		d -= e[8] * e[5] * e[2];
		d -= e[4] * e[1] * e[10];
		d -= e[0] * e[9] * e[6];

		return d;
	}

	Mat4 Mat4::getRotation() const {
		Mat4 _out;

		_out.e[0] = e[0]; _out.e[4] = e[4]; _out.e[8] = e[8];  _out.e[12] = 0;
		_out.e[1] = e[1]; _out.e[5] = e[5]; _out.e[9] = e[9];  _out.e[13] = 0;
		_out.e[2] = e[2]; _out.e[6] = e[6]; _out.e[10] = e[10]; _out.e[14] = 0;
		_out.e[3] = 0;    _out.e[7] = 0;    _out.e[11] = 0;     _out.e[15] = 1;

		return _out;
	}

	Mat4 Mat4::transpose(const Mat4& m) {
		return Mat4(m.e[0], m.e[1], m.e[2], m.e[3],
			m.e[4], m.e[5], m.e[6], m.e[7],
			m.e[8], m.e[9], m.e[10], m.e[11],
			m.e[12], m.e[13], m.e[14], m.e[15]);
	}

	Mat4 Mat4::inverse(const Mat4& m) {
		Mat4 iMat = m;

		float iDet = Math::ONEFLOAT / iMat.getDeterminant();

		iMat.e[0] = (m.e[5] * m.e[10] - m.e[9] * m.e[6]) * iDet;
		iMat.e[1] = -(m.e[1] * m.e[10] - m.e[9] * m.e[2]) * iDet;
		iMat.e[2] = (m.e[1] * m.e[6] - m.e[5] * m.e[2]) * iDet;
		iMat.e[3] = 0.0;

		iMat.e[4] = -(m.e[4] * m.e[10] - m.e[8] * m.e[6]) * iDet;
		iMat.e[5] = (m.e[0] * m.e[10] - m.e[8] * m.e[2]) * iDet;
		iMat.e[6] = -(m.e[0] * m.e[6] - m.e[4] * m.e[2]) * iDet;
		iMat.e[7] = 0.0;

		iMat.e[8] = (m.e[4] * m.e[9] - m.e[8] * m.e[5]) * iDet;
		iMat.e[9] = -(m.e[0] * m.e[9] - m.e[8] * m.e[1]) * iDet;
		iMat.e[10] = (m.e[0] * m.e[5] - m.e[4] * m.e[1]) * iDet;
		iMat.e[11] = 0.0;

		iMat.e[12] = -(m.e[12] * iMat[0] + m.e[13] * iMat[4] + m.e[14] * iMat[8]);
		iMat.e[13] = -(m.e[12] * iMat[1] + m.e[13] * iMat[5] + m.e[14] * iMat[9]);
		iMat.e[14] = -(m.e[12] * iMat[2] + m.e[13] * iMat[6] + m.e[14] * iMat[10]);
		iMat.e[15] = 1.0;

		return iMat;
	}

	Mat4 Mat4::translate(const Vec3& trans) {
		Mat4 out;
		out.e[12] = trans.x;
		out.e[13] = trans.y;
		out.e[14] = trans.z;
		return out;
	}

	Mat4 Mat4::rotate(float angle, const Vec3& axis) {
		float s = sinf(Math::DegreesToRadians(angle));
		float c = cosf(Math::DegreesToRadians(angle));

		Mat4 rMat;

		float ux = axis.x;
		float uy = axis.y;
		float uz = axis.z;

		rMat.e[0] = c + (1 - c) * ux;
		rMat.e[1] = (1 - c) * ux * uy + s * uz;
		rMat.e[2] = (1 - c) * ux * uz - s * uy;
		rMat.e[3] = 0;

		rMat.e[4] = (1 - c) * uy * ux - s * uz;
		rMat.e[5] = c + (1 - c) * pow(uy, 2);
		rMat.e[6] = (1 - c) * uy * uz + s * ux;
		rMat.e[7] = 0;

		rMat.e[8] = (1 - c) * uz * ux + s * uy;
		rMat.e[9] = (1 - c) * uz * uz - s * ux;
		rMat.e[10] = c + (1 - c) * pow(uz, 2);
		rMat.e[11] = 0;

		rMat.e[12] = 0;
		rMat.e[13] = 0;
		rMat.e[14] = 0;
		rMat.e[15] = 1;

		return rMat;
	}

	Mat4 Mat4::scale(const Vec3& scale) {
		Mat4 out;
		out.e[0] = scale.x;
		out.e[5] = scale.y;
		out.e[10] = scale.z;
		return out;
	}

	Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
		Mat4 out;
		Vec3 x, y, z;
		Mat4 m0;

		z = eye - center;
		z = Vec3::normalize(z);
		x = Vec3::cross(up, z);

		x = Vec3::normalize(x);
		y = Vec3::cross(z, x);
		y = Vec3::normalize(y);

		m0[0] = x.x; m0[4] = x.y; m0[8] = x.z; m0[12] = 0.0;
		m0[1] = y.x; m0[5] = y.y; m0[9] = y.z; m0[13] = 0.0;
		m0[2] = z.x; m0[6] = z.y; m0[10] = z.z; m0[14] = 0.0;
		m0[3] = 0.0; m0[7] = 0.0; m0[11] = 0.0; m0[15] = 1.0;

		out = m0 * translate(-eye);
		return out;
	}

	Mat4 Mat4::perspective(float fovy, float aspect, float n, float f) {
		Mat4 out;
		float sine, cotangent, delta_z;
		float radians = (fovy / 2.0f) * (M_PI / 180.0f);

		delta_z = f - n;
		sine = sinf(radians);
		if ((delta_z == 0) || (sine == 0) || (aspect == 0)) {
			out.Identity();
			return out;
		}
		cotangent = cosf(radians) / sine;

		out.Identity();
		out.e[0] = cotangent / aspect;
		out.e[5] = cotangent;
		out.e[10] = -(f + n) / delta_z;
		out.e[11] = -1;
		out.e[14] = -2 * n * f / delta_z;
		out.e[15] = 0;
		return out;
	}

	Mat4 Mat4::ortho(float left, float right, float bottom, float top, float n, float f) {
		Mat4 out;
		out.e[0] = 2.0f / (right - left);

		out.e[5] = 2.0f / (top - bottom);

		out.e[10] = -2.0f / (f - n);

		out.e[12] = -(right + left) / (right - left);
		out.e[13] = -(top + bottom) / (top - bottom);
		out.e[14] = -(f + n) / (f - n);
		return out;
	}

	Mat4 Mat4::reflect(const Vec4& plane) {
		Mat4 out;
		float x = plane.x;
		float y = plane.y;
		float z = plane.z;

		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;

		out.e[0] = Math::ONEFLOAT - x * x2;
		out.e[4] = -y * x2;
		out.e[8] = -z * x2;
		out.e[12] = -plane.w * x2;
		out.e[1] = -x * y2;
		out.e[5] = Math::ONEFLOAT - y * y2;
		out.e[9] = -z * y2;
		out.e[13] = -plane.w * y2;
		out.e[2] = -x * z2;
		out.e[6] = -y * z2;
		out.e[10] = Math::ONEFLOAT - z * z2;
		out.e[14] = -plane.w * z2;
		out.e[3] = 0.0;
		out.e[7] = 0.0;
		out.e[11] = 0.0;
		out.e[15] = 1.0;
		return out;
	}

	Mat4 Mat4::reflectProjection(const Mat4& proj, const Vec4& plane) {
		Mat4 out;
		Vec4 q; //= Vec4(sign(plane.x), 1.0, sign(plane.z), 1.0);
				//q = q * Mat4::inverse(proj);
		q.x = (Math::sign(plane.x) + proj.e[8]) / proj.e[0];
		q.y = (Math::sign(plane.y) + proj.e[9]) / proj.e[5];
		q.z = -1.0;
		q.w = (1.0 + proj.e[10]) / proj.e[14];

		Vec4 c = plane * (2.0 / Vec3::dot(plane, q));

		auto mproj = proj;
		mproj.e[2] = c.x;
		mproj.e[6] = c.y;
		mproj.e[10] = c.z + 1.0;
		mproj.e[14] = c.w;

		out = mproj;
		return out;
	}

	Mat4 Mat4::cube(const Vec3& position, int face) {
		Mat4 out;
		switch (face)
		{
		case 0:
			out *= rotate(90.0f, Vec3(Math::ZEROFLOAT, Math::ONEFLOAT, Math::ZEROFLOAT));
			out *= rotate(180.0f, Vec3(Math::ONEFLOAT, Math::ZEROFLOAT, Math::ZEROFLOAT));
			break;
		case 1: rotate(-90.0f, Vec3(Math::ZEROFLOAT, Math::ONEFLOAT, Math::ZEROFLOAT));
			out *= rotate(180.0f, Vec3(Math::ONEFLOAT, Math::ZEROFLOAT, Math::ZEROFLOAT));
			break;
		case 2: out *= rotate(-90.0f, Vec3(Math::ONEFLOAT, Math::ZEROFLOAT, Math::ZEROFLOAT)); break;
		case 3: out *= rotate(90.0f, Vec3(Math::ONEFLOAT, Math::ZEROFLOAT, Math::ZEROFLOAT)); break;
		case 4: out *= rotate(180.0f, Vec3(Math::ONEFLOAT, Math::ZEROFLOAT, Math::ZEROFLOAT)); break;
		case 5: out *= rotate(180.0f, Vec3(Math::ONEFLOAT, Math::ZEROFLOAT, Math::ZEROFLOAT));
			out *= rotate(180.0f, Vec3(Math::ZEROFLOAT, Math::ONEFLOAT, Math::ZEROFLOAT)); break;
		}

		out *= Mat4::translate(-position);
		return out;
	}

	Mat4 Mat4::texBias() {
		return Mat4::translate(Vec3(0.5, 0.5, 1)) * Mat4::scale(Vec3(0.5, 0.5, 0));
	}

	/**
	*/
	void Mat4::SetPosition(const Vec3& _vec)
	{
		// TODO: Add support of SCALE
		auto mas = (Mat4::translate(_vec) * this->getRotation()).e;
		memcpy(e, mas, sizeof(float) * 16);
	}

	/*Arithmetic operators*/
	Mat4 Mat4::operator*(const Mat4& b) const {
		Mat4 result;

		const Mat4& a = *this;
		result.e[0] = (a.e[0] * b.e[0]) + (a.e[4] * b.e[1]) + (a.e[8] * b.e[2]) + (a.e[12] * b.e[3]);
		result.e[1] = (a.e[1] * b.e[0]) + (a.e[5] * b.e[1]) + (a.e[9] * b.e[2]) + (a.e[13] * b.e[3]);
		result.e[2] = (a.e[2] * b.e[0]) + (a.e[6] * b.e[1]) + (a.e[10] * b.e[2]) + (a.e[14] * b.e[3]);
		result.e[3] = (a.e[3] * b.e[0]) + (a.e[7] * b.e[1]) + (a.e[11] * b.e[2]) + (a.e[15] * b.e[3]);

		result.e[4] = (a.e[0] * b.e[4]) + (a.e[4] * b.e[5]) + (a.e[8] * b.e[6]) + (a.e[12] * b.e[7]);
		result.e[5] = (a.e[1] * b.e[4]) + (a.e[5] * b.e[5]) + (a.e[9] * b.e[6]) + (a.e[13] * b.e[7]);
		result.e[6] = (a.e[2] * b.e[4]) + (a.e[6] * b.e[5]) + (a.e[10] * b.e[6]) + (a.e[14] * b.e[7]);
		result.e[7] = (a.e[3] * b.e[4]) + (a.e[7] * b.e[5]) + (a.e[11] * b.e[6]) + (a.e[15] * b.e[7]);

		result.e[8] = (a.e[0] * b.e[8]) + (a.e[4] * b.e[9]) + (a.e[8] * b.e[10]) + (a.e[12] * b.e[11]);
		result.e[9] = (a.e[1] * b.e[8]) + (a.e[5] * b.e[9]) + (a.e[9] * b.e[10]) + (a.e[13] * b.e[11]);
		result.e[10] = (a.e[2] * b.e[8]) + (a.e[6] * b.e[9]) + (a.e[10] * b.e[10]) + (a.e[14] * b.e[11]);
		result.e[11] = (a.e[3] * b.e[8]) + (a.e[7] * b.e[9]) + (a.e[11] * b.e[10]) + (a.e[15] * b.e[11]);

		result.e[12] = (a.e[0] * b.e[12]) + (a.e[4] * b.e[13]) + (a.e[8] * b.e[14]) + (a.e[12] * b.e[15]);
		result.e[13] = (a.e[1] * b.e[12]) + (a.e[5] * b.e[13]) + (a.e[9] * b.e[14]) + (a.e[13] * b.e[15]);
		result.e[14] = (a.e[2] * b.e[12]) + (a.e[6] * b.e[13]) + (a.e[10] * b.e[14]) + (a.e[14] * b.e[15]);
		result.e[15] = (a.e[3] * b.e[12]) + (a.e[7] * b.e[13]) + (a.e[11] * b.e[14]) + (a.e[15] * b.e[15]);

		return result;
	}

	Vec4 Mat4::operator*(const Vec4& v) const {
		Vec4 result;

		const Mat4& m = *this;
		result.x = m.e[0] * v.x + m.e[4] * v.y + m.e[8] * v.z + m.e[12] * v.w;
		result.y = m.e[1] * v.x + m.e[5] * v.y + m.e[9] * v.z + m.e[13] * v.w;
		result.z = m.e[2] * v.x + m.e[6] * v.y + m.e[10] * v.z + m.e[14] * v.w;
		result.w = m.e[3] * v.x + m.e[7] * v.y + m.e[11] * v.z + m.e[15] * v.w;
		return result;
	}

	Vec3 Mat4::operator*(const Vec3& v) const {
		Vec3 result;

		const Mat4& m = *this;
		result.x = m.e[0] * v.x + m.e[4] * v.y + m.e[8] * v.z + m.e[12];
		result.y = m.e[1] * v.x + m.e[5] * v.y + m.e[9] * v.z + m.e[13];
		result.z = m.e[2] * v.x + m.e[6] * v.y + m.e[10] * v.z + m.e[14];
		return result;
	}

	//============FOR ANOTHER==========

	Vec4 operator*(const Vec4& v, const Mat4& m) {
		Vec4 result;

		result.x = m.e[0] * v.x + m.e[4] * v.y + m.e[8] * v.z + m.e[12] * v.w;
		result.y = m.e[1] * v.x + m.e[5] * v.y + m.e[9] * v.z + m.e[13] * v.w;
		result.z = m.e[2] * v.x + m.e[6] * v.y + m.e[10] * v.z + m.e[14] * v.w;
		result.w = m.e[3] * v.x + m.e[7] * v.y + m.e[11] * v.z + m.e[15] * v.w;
		return result;
	}

	Vec3 operator*(const Vec3& v, const Mat4& m) {
		Vec3 result;

		result.x = m.e[0] * v.x + m.e[4] * v.y + m.e[8] * v.z + m.e[12];
		result.y = m.e[1] * v.x + m.e[5] * v.y + m.e[9] * v.z + m.e[13];
		result.z = m.e[2] * v.x + m.e[6] * v.y + m.e[10] * v.z + m.e[14];
		return result;
	}
}