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
#undef max
#undef min
#include <float.h>
#include "../../Src/Platform/inc/platformdetect.h"
//***************************************************************************

namespace NGTech {
	static const float M_PI = 3.14159265358979323846f;
	static const float TWOPI = 1.57079632679489f;
	static const float M_HALF_PI = 1.570796f;
	static const float M_INV_PI = 1.0f / M_PI;
	static const float EPSILON = 1e-6f;
	static ENGINE_INLINE bool IS_POWEROF2(int x) { return (((x) & ((x)-1)) == 0) && ((x) > 0); }

	class Vec2;
	class Vec3;
	class Vec4;
	class Mat4;

	/**
	Some math functions
	*/
	struct Math
	{
		// Nick: equal std::clamp (C++17)
		template<class T>
		static ENGINE_INLINE T Clamp(T v, T min/*x*/, T max/*y*/) {
			/*if (v < min) v = min;
			if (v > max) v = max;
			return v;*/
			return Min(max, Max(min, v));
		}

		/*linear interpolation*/
		template<typename type>
		static ENGINE_INLINE type Lerp(type a, type b, type w) {
			return (1.0 - w)*a + w * b;
		}

		static float angleBetweenVec(const Vec3 &a, const Vec3 &b);
		static bool insidePolygon(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, const Vec3 &point);
		static bool intersectPlaneByRay(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, const Vec3 &src, const Vec3 &dst, Vec3 &point);
		static bool intersectPolygonByRay(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, const Vec3 &src, const Vec3 &dst, Vec3 &point);
		static bool intersectSphereByRay(const Vec3 &center, float radius, const Vec3 &src, const Vec3 &dst);

		template<typename type>
		static ENGINE_INLINE type DegreesToRadians(type value) {
			return value * (M_PI / 180.0);
		}

		template<typename type>
		static ENGINE_INLINE type RadiansToDegrees(type value) {
			return value * (180.0 / M_PI);
		}

		static ENGINE_INLINE float tosRGBFloat(float rgba)
		{
			float srgb = (rgba*rgba)*(rgba*0.2848 + 0.7152);
			return srgb;
		}

		template <typename T>
		static ENGINE_INLINE const T& Max(const T& a, const T& b) {
			return ((a > b) ? a : b);
		}

		template <typename T>
		static ENGINE_INLINE const T& Min(const T& a, const T& b) {
			return a < b ? a : b;
		}

		static ENGINE_INLINE float mod(float x, float y) {
			return ::fmodf(x, y);
		}
		static ENGINE_INLINE float mod(double x, double y) {
			return ::fmod(x, y);
		}

		static ENGINE_INLINE float sign(float a) { if (a > ZEROFLOAT) return Math::ONEFLOAT; if (a < Math::ZEROFLOAT) return -Math::ONEFLOAT; return Math::ZEROFLOAT; }
		static ENGINE_INLINE bool FloatToBool(float f) { /*it is not-a-number*/if (isnan(f)) return false; return std::abs(f) > std::numeric_limits<float>::epsilon(); }

		// Used for comparing floats and etc
		template <typename t1, typename t2>
		static ENGINE_INLINE bool IsEqual(const t1& v1, const t2& v2)
		{
			return ::abs(v1 - v2) <=
				std::max(std::numeric_limits<t1>::epsilon(),
					std::numeric_limits<t2>::epsilon());
		};

		// Constatns
		static const float ZEROFLOAT;
		static const float ONEFLOAT;
		// DeltaConstatns
		static const TimeDelta ZERODELTA;
		static const TimeDelta ONEDELTA;

		// Axis
		static const Vec3 X_AXIS;
		static const Vec3 Y_AXIS;
		static const Vec3 Z_AXIS;
	};

	/**
	2D Vector class
	*/
	class Vec2
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
			};
			float f[2];
		};

		Vec2();
		~Vec2();
		Vec2(float cx, float cy);
		Vec2(const Vec2 &in);
		Vec2(const Vec3 &in);
		Vec2(const Vec4 &in);
		Vec2(const float *ar)
		{
			ASSERT(ar, "[Vec2] INVALID POINTER");
			x = ar[0];
			y = ar[1];
		}

		Vec2& operator=(const Vec2 &in);

		float& operator[](intptr_t index);
		float operator[](intptr_t index) const;

		operator float*();
		operator const float*() const;

		Vec2 operator-() const;
		Vec2 operator+() const;
		Vec2& operator+=(const Vec2 &v);
		Vec2& operator-=(const Vec2 &v);
		Vec2& operator*=(const Vec2 &v);
		Vec2& operator/=(const Vec2 &v);
		Vec2& operator*=(const float &v);

		bool operator==(const Vec2 &v) const;
		bool operator!=(const Vec2 &v) const;

		float length();

		friend Vec2 operator+(const Vec2 &a, const Vec2 &b);
		friend Vec2 operator+(const Vec2 &a, float b);
		friend Vec2 operator-(const Vec2 &a, const Vec2 &b);
		friend Vec2 operator*(const Vec2 &a, const Vec2 &b);
		friend Vec2 operator*(const Vec2 &v, float c);
		friend Vec2 operator*(float c, const Vec2 &v);
		friend Vec2 operator/(const Vec2 &a, const Vec2 &b);
		friend Vec2 operator/(const Vec2 &v, float c);
		friend Vec2 operator/(float c, const Vec2 &v);

		static Vec2 normalize(const Vec2 &a);
		static ENGINE_INLINE float dot(const Vec2 &a, const Vec2 &b) {
			return (a.x * b.x + a.y * b.y);
		}

		ENGINE_INLINE void Set(float _x, float _y)
		{
			this->x = _x;
			this->y = _y;
		}

		ENGINE_INLINE void SetZero()
		{
			x = y = Math::ZEROFLOAT;
		}

		ENGINE_INLINE void SetMin()
		{
			x = y = -std::numeric_limits<float>::max();
		}

		ENGINE_INLINE void SetMax()
		{
			x = y = std::numeric_limits<float>::max();
		}

		ENGINE_INLINE void Clamp()
		{
			x = Math::Clamp(x, Math::ZEROFLOAT, Math::ONEFLOAT);
			y = Math::Clamp(y, Math::ZEROFLOAT, Math::ONEFLOAT);
		}

		static const Vec2 ZERO;
		static const Vec2 ONE;


		operator String() const {
			return "X: " + std::to_string(x) + " Y: " + std::to_string(y);
		}
	};

	extern Vec2 operator+(const Vec2 &a, const Vec2 &b);
	extern Vec2 operator-(const Vec2 &a, const Vec2 &b);
	extern Vec2 operator*(const Vec2 &a, const Vec2 &b);
	extern Vec2 operator*(const Vec2 &v, float c);
	extern Vec2 operator*(float c, const Vec2 &v);
	extern Vec2 operator/(const Vec2 &a, const Vec2 &b);
	extern Vec2 operator/(const Vec2 &v, float c);
	extern Vec2 operator/(float c, const Vec2 &v);

	/**
	3D Vector class
	*/
	class Vec3
	{
	public:

		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float f[3];
		};

		Vec3();
		~Vec3();
		Vec3(float cx, float cy, float cz);
		Vec3(const Vec2 &in);
		Vec3(const Vec3 &in);
		Vec3(const Vec4 &in);
		Vec3(const float *ar)
		{
			ASSERT(ar, "[Vec3] INVALID POINTER");
			x = ar[0];
			y = ar[1];
			z = ar[2];
		}

		Vec3& operator=(const Vec3 &in);

		//!@todo ��� ��������� �������� ����������� - ��� ������ ���������� �������� �� �������?! - ���������� ��� ���� ���������
		float& operator[](intptr_t index);
		float operator[](intptr_t index) const;

		operator float*();
		operator const float*() const;

		/// Unary operators.
		Vec3 operator-() const;
		Vec3 operator+() const;

		/// Assignment operators.
		Vec3& operator+=(const Vec3 &v);
		Vec3& operator-=(const Vec3 &v);
		Vec3& operator*=(const Vec3 &v);
		Vec3& operator/=(const Vec3 &v);
		Vec3& operator*=(const float &v);

		/// Binary comparison operators.
		bool operator==(const Vec3 &v) const;
		bool operator!=(const Vec3 &v) const;

		/// Binary math operators.
		ENGINE_INLINE Vec3 operator^(const Vec3& V) const
		{
			return Vec3
			(
				y * V.z - z * V.y,
				z * V.x - x * V.z,
				x * V.y - y * V.x
			);
		}
		ENGINE_INLINE float operator|(const Vec3& V) const
		{
			return x * V.x + y * V.y + z * V.z;
		}

		float length();

		ENGINE_INLINE void SetMax()
		{
			x = y = z = std::numeric_limits<float>::max();
		}
		ENGINE_INLINE void SetMin()
		{
			x = y = z = -std::numeric_limits<float>::max();
		}
		ENGINE_INLINE void SetZero()
		{
			x = y = z = 0;
		}
		ENGINE_INLINE void Normalize()
		{
			normalize(*this);
		}
		ENGINE_INLINE float DotProduct(const Vec3 &vec) const
		{
			return ((vec.x*x) + (vec.y*y) + (vec.z*z));
		}

		ENGINE_INLINE Vec3 CrossProduct(const Vec3 &vec) const
		{
			return Vec3((y*vec.z) - (z*vec.y),
				(z*vec.x) - (x*vec.z),
				(x*vec.y) - (y*vec.x));
		}

		ENGINE_INLINE void Set(float _x, float _y, float _z)
		{
			this->x = _x;
			this->y = _y;
			this->z = _z;
		}

		ENGINE_INLINE float GetSquaredLength() const
		{
			return ((x*x) + (y*y) + (z*z));
		}

		ENGINE_INLINE float Distance(const Vec3 &vec) const
		{
			return (*this - vec).length();
		}

		ENGINE_INLINE Vec3 GetNormalized() const
		{
			return normalize(*this);
		}

		ENGINE_INLINE void Floor()
		{
			x = floor(x);
			y = floor(y);
			z = floor(z);
		}

		ENGINE_INLINE Vec3 GetFloored()
		{
			Vec3 result(*this);
			result.Floor();
			return result;
		}

		ENGINE_INLINE void Clamp(const Vec3 &mins, const Vec3 &maxes)
		{
			Math::Clamp(x, mins.x, maxes.x);
			Math::Clamp(y, mins.y, maxes.y);
			Math::Clamp(z, mins.z, maxes.z);
		}

		ENGINE_INLINE Vec3 GetClamped(const Vec3 &mins, const Vec3 &maxes)
		{
			Vec3 result(*this);
			result.Clamp(mins, maxes);
			return result;
		}

		ENGINE_INLINE void Scale(float scale)
		{
			x = x * scale;
			y = y * scale;
			z = z * scale;
		}

		friend Vec3 operator+(const Vec3 &a, const Vec3 &b);
		friend Vec3 operator+(const Vec3 &a, float b);
		friend Vec3 operator-(const Vec3 &a, const Vec3 &b);
		friend Vec3 operator*(const Vec3 &a, const Vec3 &b);
		friend Vec3 operator*(const Vec3 &v, float c);
		friend Vec3 operator*(float c, const Vec3 &v);
		friend Vec3 operator/(const Vec3 &a, const Vec3 &b);
		friend Vec3 operator/(const Vec3 &v, float c);
		friend Vec3 operator/(float c, const Vec3 &v);

		static Vec3 normalize(const Vec3 &a);
		static ENGINE_INLINE float dot(const Vec3 &a, const Vec3 &b) {
			return (a.x * b.x + a.y * b.y + a.z * b.z);
		}
		static Vec3 cross(const Vec3 &a, const Vec3 &b);

		static const Vec3 ZERO;
		static const Vec3 ONE;

		operator String() const {
			return "X: " + std::to_string(x) + " Y: " + std::to_string(y) +" Z: " + std::to_string(z);
		}
	};

	extern Vec3 operator+(const Vec3 &a, const Vec3 &b);
	extern Vec3 operator-(const Vec3 &a, const Vec3 &b);
	extern Vec3 operator*(const Vec3 &a, const Vec3 &b);
	extern Vec3 operator*(const Vec3 &v, float c);
	extern Vec3 operator*(float c, const Vec3 &v);
	extern Vec3 operator/(const Vec3 &a, const Vec3 &b);
	extern Vec3 operator/(const Vec3 &v, float c);
	extern Vec3 operator/(float c, const Vec3 &v);

	/**
	4D Vector class
	*/
	class Vec4
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float f[4];
		};

		Vec4();
		~Vec4();
		Vec4(float cx, float cy, float cz, float cw);
		Vec4(const Vec2 &in);
		Vec4(const Vec3 &in);
		Vec4(const Vec3 &in, float cw);
		Vec4(const Vec4 &in);
		Vec4(const float *ar)
		{
			ASSERT(ar, "Vec4] INVALID POINTER");
			x = ar[0]; y = ar[1]; z = ar[2]; w = ar[3];
		}

		Vec4& operator=(const Vec4 &in);
		float& operator[](intptr_t index);
		float operator[](intptr_t index) const;

		operator float*();
		operator const float*() const;

		Vec4 operator-() const;
		Vec4 operator+() const;

		Vec4& operator+=(const Vec4 &v);
		Vec4& operator-=(const Vec4 &v);
		Vec4& operator*=(const Vec4 &v);
		Vec4& operator/=(const Vec4 &v);
		Vec4& operator*=(const float &v);

		bool operator==(const Vec4 &v) const;
		bool operator!=(const Vec4 &v) const;

		float length();

		ENGINE_INLINE void SetMax()
		{
			x = y = z = w = std::numeric_limits<float>::max();
		}

		ENGINE_INLINE void SetMin()
		{
			x = y = z = w = -std::numeric_limits<float>::max();
		}

		ENGINE_INLINE void Normalize()
		{
			normalize(*this);
		}

		ENGINE_INLINE float DotProduct(const Vec4 &vec) const
		{
			return ((vec.x*x) + (vec.y*y) + (vec.z*z) + (vec.w*w));
		}

		ENGINE_INLINE void Set(float _x, float _y, float _z, float _w)
		{
			this->x = _x;
			this->y = _y;
			this->z = _z;
			this->w = _w;
		}

		ENGINE_INLINE void Set(const Vec3 &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = Math::ONEFLOAT;
		}

		ENGINE_INLINE void SetZero()
		{
			x = y = z = w = Math::ZEROFLOAT;
		}

		friend Vec4 operator+(const Vec4 &a, const Vec4 &b);
		friend Vec4 operator+(const Vec4 &a, float b);
		friend Vec4 operator-(const Vec4 &a, const Vec4 &b);
		friend Vec4 operator*(const Vec4 &a, const Vec4 &b);
		friend Vec4 operator*(const Vec4 &v, float c);
		friend Vec4 operator*(float c, const Vec4 &v);
		friend Vec4 operator/(const Vec4 &a, const Vec4 &b);
		friend Vec4 operator/(const Vec4 &v, float c);
		friend Vec4 operator/(float c, const Vec4 &v);

		static Vec4 normalize(const Vec4 &a);
		static ENGINE_INLINE float dot(const Vec4 &a, const Vec4 &b) {
			return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
		}

		ENGINE_INLINE void Clamp() {
			x = Math::Clamp(x, Math::ZEROFLOAT, Math::ONEFLOAT);
			y = Math::Clamp(y, Math::ZEROFLOAT, Math::ONEFLOAT);
			z = Math::Clamp(z, Math::ZEROFLOAT, Math::ONEFLOAT);
			w = Math::Clamp(w, Math::ZEROFLOAT, Math::ONEFLOAT);
		}


		operator String() const {
			return "X: " + std::to_string(x) + " Y: " + std::to_string(y) + " Z: " + std::to_string(z) + " W: " + std::to_string(w);
		}

		static const Vec4 ZERO;
		static const Vec4 ONE;
	};

	extern Vec4 operator+(const Vec4 &a, const Vec4 &b);
	extern Vec4 operator-(const Vec4 &a, const Vec4 &b);
	extern Vec4 operator*(const Vec4 &a, const Vec4 &b);
	extern Vec4 operator*(const Vec4 &v, float c);
	extern Vec4 operator*(float c, const Vec4 &v);
	extern Vec4 operator/(const Vec4 &a, const Vec4 &b);
	extern Vec4 operator/(const Vec4 &v, float c);
	extern Vec4 operator/(float c, const Vec4 &v);

	/*/
	Color Class
	*/
	class Color :public Vec4
	{
	public:
		ENGINE_INLINE Color()
		{
			x = (0);
			y = (0);
			z = (0);
			w = (1);
		}

		ENGINE_INLINE Color(unsigned int argb32)
		{
			x = ArgbA32(argb32) / 255.0f;
			y = ArgbR32(argb32) / 255.0f;
			z = ArgbG32(argb32) / 255.0f;
			w = ArgbB32(argb32) / 255.0f;
		}

		ENGINE_INLINE Color(float _r, float _g, float _b, float _a)
		{
			x = (_r);
			y = (_g);
			z = (_b);
			w = (_a);
		}

		ENGINE_INLINE Color(Vec4 _color)
		{
			x = _color.x;
			y = _color.y;
			z = _color.z;
			w = _color.w;
		}

		static ENGINE_INLINE Color Lerp(const Color& from, const Color& to, float frac)
		{
			Color ret;

			ret.x = from.x * (1 - frac) + to.x * frac;
			ret.y = from.y * (1 - frac) + to.y * frac;
			ret.z = from.z * (1 - frac) + to.z * frac;
			ret.w = from.w * (1 - frac) + to.w * frac;

			return ret;
		}

		static ENGINE_INLINE Color sRGBToLinear(unsigned char red, unsigned char green, unsigned char blue)
		{
			Color ret;

			float lo_r = (float)red / 3294.6f;
			float lo_g = (float)green / 3294.6f;
			float lo_b = (float)blue / 3294.6f;

			float hi_r = powf((red / 255.0f + 0.055f) / 1.055f, 2.4f);
			float hi_g = powf((green / 255.0f + 0.055f) / 1.055f, 2.4f);
			float hi_b = powf((blue / 255.0f + 0.055f) / 1.055f, 2.4f);

			ret.x = (red < 10 ? lo_r : hi_r);
			ret.y = (green < 10 ? lo_g : hi_g);
			ret.z = (blue < 10 ? lo_b : hi_b);
			ret.w = 1;

			return ret;
		}

		static ENGINE_INLINE unsigned char ArgbA32(unsigned int c) {
			return ((unsigned char)((c >> 24) & 0xff));
		}

		static ENGINE_INLINE unsigned char ArgbR32(unsigned int c) {
			return ((unsigned char)((c >> 16) & 0xff));
		}

		static ENGINE_INLINE unsigned char ArgbG32(unsigned int c) {
			return ((unsigned char)((c >> 8) & 0xff));
		}

		static ENGINE_INLINE unsigned char ArgbB32(unsigned int c) {
			return ((unsigned char)(c & 0xff));
		}

		ENGINE_INLINE void Clamp()
		{
			x = Math::Clamp(x, Math::ZEROFLOAT, Math::ONEFLOAT);
			y = Math::Clamp(y, Math::ZEROFLOAT, Math::ONEFLOAT);
			z = Math::Clamp(z, Math::ZEROFLOAT, Math::ONEFLOAT);
			w = Math::Clamp(w, Math::ZEROFLOAT, Math::ONEFLOAT);
		}

		static const Color WHITE;
		static const Color BLACK;
	};

	/**
	3x3 Matrix class
	*/
	class Mat3 {
	public:
		float e[9];

		Mat3();
		~Mat3();

		void Identity();
		void SetZero();

		Mat3(float e0, float e3, float e6,
			float e1, float e4, float e7,
			float e2, float e5, float e8);

		Mat3(const Mat3 &in);
		Mat3(const Mat4 &in);

		Mat3 &operator=(const Mat3 &in);
		Mat3 &operator*=(const Mat3 &in);

		float &operator[](intptr_t index);
		float operator[](intptr_t index) const;
		operator float*();
		operator const float*() const;

		float getDeterminant();

		static Mat3 transpose(const Mat3 &m);
		static Mat3 inverse(const Mat3 &m);

		static Mat3 rotate(float angle, const Vec3 &axis);
		static Mat3 scale(const Vec3 &scale);

		static const Mat3 ZERO;
		static const Mat3 ONE;
	};

	extern Mat3 operator*(const Mat3 &a, const Mat3 &b);
	extern Vec4 operator*(const Mat3 &m, const Vec4 &v);
	extern Vec4 operator*(const Vec4 &v, const Mat3 &m);
	extern Vec3 operator*(const Mat3 &m, const Vec3 &v);
	extern Vec3 operator*(const Vec3 &v, const Mat3 &m);

	/**
	4x4 Matrix class
	*/
	class Mat4 {
	public:
		Mat4();
		~Mat4();
		Mat4(float e0, float e4, float e8, float e12,
			float e1, float e5, float e9, float e13,
			float e2, float e6, float e10, float e14,
			float e3, float e7, float e11, float e15);
		Mat4(const Mat4 &in);
		Mat4(const Mat3 &in);

		Mat4 &operator=(const Mat4 &in);
		Mat4 &operator*=(const Mat4 &in);

		float &operator[](intptr_t index);
		float operator[](intptr_t index) const;
		operator float*();
		operator const float*() const;

		ENGINE_INLINE Vec3 GetScale() const { return Vec3{ e[0], e[5], e[10] }; }
		ENGINE_INLINE float &GetScaleForChange_X() { return e[0]; }
		ENGINE_INLINE float &GetScaleForChange_Y() { return e[5]; }
		ENGINE_INLINE float &GetScaleForChange_Z() { return e[10]; }
		ENGINE_INLINE void SetScale(const Vec3&_v) { e[0] = _v.x; e[5] = _v.y; e[10] = _v.z; }
		/*
		!@ Rotation Matrix from current matrix.
		*/
		Mat4 getRotation() const;
		float getDeterminant();
		/**/
		void Identity();
		void SetZero();

		ENGINE_INLINE Vec3 GetPosition() const { return Vec3{ e[12], e[13], e[14] }; }
		ENGINE_INLINE float &GetPositionForChange_X() { return e[12]; }
		ENGINE_INLINE float &GetPositionForChange_Y() { return e[13]; }
		ENGINE_INLINE float &GetPositionForChange_Z() { return e[14]; }
		void SetPosition(const Vec3&_vec);

		/*
		*/
		static Mat4 transpose(const Mat4 &m);
		static Mat4 inverse(const Mat4 &m);

		static Mat4 translate(const Vec3 &trans);
		/*
		angle-can be only Degrees
		*/
		static Mat4 rotate(float degree, const Vec3 &axis);
		static Mat4 scale(const Vec3 &scale);
		static Mat4 lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up);

		static Mat4 perspective(float fovy, float aspect, float n, float f);
		static Mat4 ortho(float left, float right, float bottom, float top, float n, float f);

		static Mat4 reflect(const Vec4 &plane);
		static Mat4 reflectProjection(const Mat4 &proj, const Vec4 &plane);

		static Mat4 cube(const Vec3 &position, int face);

		static Mat4 texBias();
		/*Arithmetic operators*/
		Mat4 operator * (const Mat4 &m) const;   // M * N
		Vec4 operator*(const Vec4 &v) const;	 // M * V
		Vec3 operator*(const Vec3 &v) const;	 // M * V

		static const Mat4 ZERO;
		static const Mat4 ZEROAFFINE;
		static const Mat4 IDENTITY;
		static const Mat4 CLIPSPACE2DTOIMAGESPACE;
	public:
		float e[16];
	};

	//Implement to Vectors
	extern Vec4 operator*(const Vec4 &v, const Mat4 &m);
	extern Vec3 operator*(const Vec3 &v, const Mat4 &m);

	namespace Utils
	{
		/**
		*/
		struct AffineTransformations
		{
			static ENGINE_INLINE void RotateAndGet(Mat4& out, float degree, const Vec3 &axis)
			{
				out = Mat4::rotate(degree, axis)*out;
			}
		};

		/**
		*/
		static ENGINE_INLINE void TransformCoord(Vec3&out, const Vec3 &v, const Mat4& m)
		{
			Vec4 tmp;

			tmp[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + m[12];
			tmp[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + m[13];
			tmp[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + m[14];
			tmp[3] = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + m[15];

			out[0] = tmp[0] / tmp[3];
			out[1] = tmp[1] / tmp[3];
			out[2] = tmp[2] / tmp[3];
		}

		/**
		TODO: Maybe deprecated
		*/
		static ENGINE_INLINE int isqrt(int n)
		{
			int b = 0;

			while (n >= 0)
			{
				n = n - b;
				b = b + 1;
				n = n - b;
			}

			return b - 1;
		}
	}

	/**
	Quat class
	*/
	class Quat {
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float f[4];
		};

		Quat();
		Quat(float _x, float _y, float _z, float _w);
		Quat(float angle, const Vec3 &axis);

		Quat(const Mat3 &in);

		operator float*();
		operator const float*() const;

		float &operator[](intptr_t i);
		const float operator[](intptr_t i) const;

		Quat operator*(const Quat &q) const;
		static Quat slerp(const Quat &q0, const Quat &q1, float t);
		Mat3 toMatrix() const;

		ENGINE_INLINE void Identity()
		{
			x = y = z = 0;
			w = 1;
		}

		ENGINE_INLINE void Multiply(const Quat &b)
		{
			float tmp[4];

			tmp[0] = w * b[0] + x * b[3] + y * b[2] - z * b[1];
			tmp[1] = w * b[1] + y * b[3] + z * b[0] - x * b[2];
			tmp[2] = w * b[2] + z * b[3] + x * b[1] - y * b[0];
			tmp[3] = w * b[3] - x * b[0] - y * b[1] - z * b[2];

			x = tmp[0];
			y = tmp[1];
			z = tmp[2];
			w = tmp[3];
		}

		ENGINE_INLINE void Rotate(Vec3 &out, Vec3 v)
		{
			Quat cq;
			Quat p = { v[0], v[1], v[2], 0 };

			cq.Conjugate(*this);

			p.Multiply(cq);
			this->Multiply(p);

			out.x = p[0];
			out.y = p[1];
			out.z = p[2];
		}

		ENGINE_INLINE void RotationAxis(const Vec3 &_axisvector, float angle)
		{
			float l = sqrtf(_axisvector.x * _axisvector.x + _axisvector.y * _axisvector.y + _axisvector.z * _axisvector.z);
			float ha = angle * 0.5f;
			float sa = sinf(ha);

			x = (_axisvector.x / l) * sa;
			y = (_axisvector.y / l) * sa;
			z = (_axisvector.z / l) * sa;
			w = cosf(ha);
		}

		ENGINE_INLINE void Conjugate(const Quat& q)
		{
			x = -q[0];
			y = -q[1];
			z = -q[2];
			w = q[3];
		}

		static const Quat ZERO;
	};

	/**
	Computes TBN basis
	*/
	struct TBNComputer {
		static void computeN(Vec3 &n, const Vec3& p0, const Vec3& p1, const Vec3& p2);
		static void computeTBN(Vec3 &t, Vec3 &b, const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec2& t0, const Vec2& t1, const Vec2& t2, const Vec3& n);
	};

	static_assert(sizeof(Vec2) == 2 * sizeof(float), "Invalid Vec2 padding!");
	static_assert(sizeof(Vec3) == 3 * sizeof(float), "Invalid Vec3 padding!");
	static_assert(sizeof(Vec4) == 4 * sizeof(float), "Invalid Vec4 padding!");
	static_assert(sizeof(Mat3) == 9 * sizeof(float), "Invalid Mat3 padding!");
	static_assert(sizeof(Mat4) == 16 * sizeof(float), "Invalid Mat4 padding!");
	static_assert(sizeof(Quat) == 4 * sizeof(float), "Invalid Quat padding!");
};