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
	const Vec3 Vec3::ZERO(0, 0, 0);
	const Vec3 Vec3::ONE(1, 1, 1);

	/*
	*/
	Vec3::Vec3() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	Vec3::~Vec3() {}

	Vec3::Vec3(float cx, float cy, float cz) {
		x = cx;
		y = cy;
		z = cz;
	}

	Vec3::Vec3(const Vec2 &in) {
		x = in.x;
		y = in.y;
		z = 0;
	}

	Vec3::Vec3(const Vec3 &in) {
		x = in.x;
		y = in.y;
		z = in.z;
	}

	Vec3::Vec3(const Vec4 &in) {
		x = in.x;
		y = in.y;
		z = in.z;
	}

	Vec3 &Vec3::operator=(const Vec3 &in) {
		x = in.x;
		y = in.y;
		z = in.z;
		return *this;
	}

	float& Vec3::operator[](intptr_t index) {
		assert(index < 3);
		return ((float*)this)[index];
	}

	float Vec3::operator[](intptr_t index) const {
		assert(index < 3);
		return ((float*)this)[index];
	}

	Vec3::operator float*() {
		return &x;
	}

	Vec3::operator const float*() const {
		return &x;
	}

	Vec3 Vec3::operator-() const {
		return Vec3(-x, -y, -z);
	}

	Vec3 Vec3::operator+() const {
		return *this;
	}

	Vec3 &Vec3::operator+=(const Vec3 &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec3 &Vec3::operator-=(const Vec3 &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3 &Vec3::operator*=(const Vec3 &v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vec3 &Vec3::operator/=(const Vec3 &v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vec3 & Vec3::operator*=(const float & v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	bool Vec3::operator==(const Vec3 &v) const {
		return (x == v.x && y == v.y && z == v.z);
	}

	bool Vec3::operator!=(const Vec3 &v) const {
		return (x != v.x || y != v.y || z != v.z);
	}

	Vec3 operator+(const Vec3 &a, const Vec3 &b) {
		return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	Vec3 operator+(const Vec3 &a, float b) {
		return Vec3(a.x + b, a.y + b, a.z + b);
	}

	Vec3 operator-(const Vec3 &a, const Vec3 &b) {
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	Vec3 operator*(const Vec3 &a, const Vec3 &b) {
		return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	Vec3 operator*(const Vec3 &v, float c) {
		return Vec3(v.x * c, v.y * c, v.z * c);
	}

	Vec3 operator*(float c, const Vec3 &v) {
		return Vec3(v.x * c, v.y * c, v.z * c);
	}

	Vec3 operator/(const Vec3 &a, const Vec3 &b) {
		return Vec3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	Vec3 operator/(const Vec3 &v, float c) {
		return Vec3(v.x / c, v.y / c, v.z / c);
	}

	Vec3 operator/(float c, const Vec3 &v) {
		return Vec3(v.x / c, v.y / c, v.z / c);
	}

	float Vec2::length() {
		return sqrt(x*x + y * y);
	}

	float Vec3::length() {
		return sqrt(x*x + y * y + z * z);
	}

	float Vec4::length() {
		return sqrt(x*x + y * y + z * z + w * w);
	}

	Vec3 Vec3::normalize(const Vec3 &_vec) {
		Vec3 vec = _vec;
		auto _length = vec.length();
		vec.x /= _length;
		vec.y /= _length;
		vec.z /= _length;
		return vec;
	}

	Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
		return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
}