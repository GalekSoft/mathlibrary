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
	const Vec4 Vec4::ZERO(0, 0, 0, 0);
	const Vec4 Vec4::ONE(1, 1, 1, 1);

	/*
	*/
	Vec4::Vec4() {
		x = y = z = w = 0.0;
	}

	Vec4::~Vec4() {}

	Vec4::Vec4(float cx, float cy, float cz, float cw) {
		x = cx;
		y = cy;
		z = cz;
		w = cw;
	}

	Vec4::Vec4(const Vec4 &in) {
		x = in.x;
		y = in.y;
		z = in.z;
		w = in.w;
	}

	Vec4::Vec4(const Vec3 &in) {
		x = in.x;
		y = in.y;
		z = in.z;
		w = 1.0;
	}

	Vec4::Vec4(const Vec2 &in) {
		x = in.x;
		y = in.y;
		z = 0;
		w = 1.0;
	}

	Vec4::Vec4(const Vec3 &in, float cw) {
		x = in.x;
		y = in.y;
		z = in.z;
		w = cw;
	}

	Vec4 &Vec4::operator=(const Vec4 &in) {
		x = in.x;
		y = in.y;
		z = in.z;
		w = in.w;
		return *this;
	}

	float& Vec4::operator[](intptr_t index) {
		ASSERT(index < 4, "incorrect infex"); //-V112
		return ((float*)this)[index];
	}

	float Vec4::operator[](intptr_t index) const {
		ASSERT(index < 4, "incorrect infex"); //-V112
		return ((float*)this)[index];
	}

	Vec4::operator float*() {
		return &x;
	}

	Vec4::operator const float*() const {
		return &x;
	}

	Vec4 Vec4::operator-() const {
		return Vec4(-x, -y, -z, -w);
	}

	Vec4 Vec4::operator+() const {
		return *this;
	}

	Vec4 &Vec4::operator+=(const Vec4 &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Vec4 &Vec4::operator-=(const Vec4 &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	Vec4 &Vec4::operator*=(const Vec4 &v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	Vec4 &Vec4::operator/=(const Vec4 &v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	Vec4 & Vec4::operator*=(const float & v)
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
		return *this;
	}

	bool Vec4::operator==(const Vec4 &v) const {
		return (x == v.x && y == v.y && z == v.z && w == v.w);
	}

	bool Vec4::operator!=(const Vec4 &v) const {
		return (x != v.x || y != v.y || z != v.z || w != v.w);
	}

	Vec4 operator+(const Vec4 &a, const Vec4 &b) {
		return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	Vec4 operator+(const Vec4 &a, float b) {
		return Vec4(a.x + b, a.y + b, a.z + b, a.w + b);
	}

	Vec4 operator-(const Vec4 &a, const Vec4 &b) {
		return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	Vec4 operator*(const Vec4 &a, const Vec4 &b) {
		return Vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	Vec4 operator*(const Vec4 &v, float c) {
		return Vec4(v.x * c, v.y * c, v.z * c, v.w * c);
	}

	Vec4 operator*(float c, const Vec4 &v) {
		return Vec4(v.x * c, v.y * c, v.z * c, v.w * c);
	}

	Vec4 operator/(const Vec4 &a, const Vec4 &b) {
		return Vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	Vec4 operator/(const Vec4 &v, float c) {
		return Vec4(v.x / c, v.y / c, v.z / c, v.w / c);
	}

	Vec4 operator/(float c, const Vec4 &v) {
		return Vec4(v.x / c, v.y / c, v.z / c, v.w / c);
	}

	Vec4 Vec4::normalize(const Vec4 &_vec)
	{
		Vec4 vec = _vec;
		auto _length = vec.length();
		vec.x /= _length;
		vec.y /= _length;
		vec.z /= _length;
		vec.w /= _length;
		return vec;
	}
}