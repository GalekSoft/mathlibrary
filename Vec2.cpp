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
	const Vec2 Vec2::ZERO(0, 0);
	const Vec2 Vec2::ONE(1, 1);

	//---------------------------------------------------------------------------
	//Desc: 2D Vector class
	//---------------------------------------------------------------------------
	Vec2::Vec2() {
		x = y = 0.0;
	}

	Vec2::~Vec2() {}

	Vec2::Vec2(float cx, float cy) {
		x = cx;
		y = cy;
	}

	Vec2::Vec2(const Vec2 &in) {
		x = in.x;
		y = in.y;
	}

	Vec2::Vec2(const Vec3 &in) {
		x = in.x;
		y = in.y;
	}

	Vec2::Vec2(const Vec4 &in) {
		x = in.x;
		y = in.y;
	}

	Vec2 &Vec2::operator=(const Vec2 &in) {
		x = in.x;
		y = in.y;
		return *this;
	}

	float &Vec2::operator[](intptr_t index) {
		return *(index + &x);
	}

	float Vec2::operator[](intptr_t index) const {
		return *(index + &x);
	}

	Vec2::operator float*() {
		return &x;
	}

	Vec2::operator const float*() const {
		return &x;
	}

	Vec2 Vec2::operator-() const {
		return Vec2(-x, -y);
	}

	Vec2 Vec2::operator+() const {
		return *this;
	}

	Vec2 &Vec2::operator+=(const Vec2 &v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2 &Vec2::operator-=(const Vec2 &v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2 &Vec2::operator*=(const Vec2 &v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vec2 &Vec2::operator/=(const Vec2 &v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vec2 & Vec2::operator*=(const float & v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	bool Vec2::operator==(const Vec2 &v) const {
		return (x == v.x && y == v.y);
	}

	bool Vec2::operator!=(const Vec2 &v) const {
		return (x != v.x || y != v.y);
	}

	Vec2 operator+(const Vec2 &a, const Vec2 &b) {
		return Vec2(a.x + b.x, a.y + b.y);
	}

	Vec2 operator+(const Vec2 &a, float b) {
		return Vec2(a.x + b, a.y + b);
	}

	Vec2 operator-(const Vec2 &a, const Vec2 &b) {
		return Vec2(a.x - b.x, a.y - b.y);
	}

	Vec2 operator*(const Vec2 &a, const Vec2 &b) {
		return Vec2(a.x * b.x, a.y * b.y);
	}

	Vec2 operator*(const Vec2 &v, float c) {
		return Vec2(v.x * c, v.y * c);
	}

	Vec2 operator*(float c, const Vec2 &v) {
		return Vec2(v.x * c, v.y * c);
	}

	Vec2 operator/(const Vec2 &a, const Vec2 &b) {
		return Vec2(a.x / b.x, a.y / b.y);
	}

	Vec2 operator/(const Vec2 &v, float c) {
		return Vec2(v.x / c, v.y / c);
	}

	Vec2 operator/(float c, const Vec2 &v) {
		return Vec2(v.x / c, v.y / c);
	}

	Vec2 Vec2::normalize(const Vec2 &_vec) {
		Vec2 vec = _vec;
		auto _length = vec.length();
		vec.x /= _length;
		vec.y /= _length;
		return vec;
	}
}