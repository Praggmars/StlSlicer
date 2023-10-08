#pragma once

#include "formulas.hpp"

namespace mth
{
	template <typename T>
	class quaternion
	{
	public:
		T x;
		T y;
		T z;
		T w;

	public:
		quaternion() :x(0), y(0), z(0), w(0) {}
		quaternion(const T t) :x(0), y(0), z(0), w(t) {}
		quaternion(const T* const q) :x(q[0]), y(q[1]), z(q[2]), w(q[3]) {}
		quaternion(const T x, const T y, const T z, const T w) :x(x), y(y), z(z), w(w) {}
		quaternion(const quaternion& q) :x(q.x), y(q.y), z(q.z), w(q.w) {}
		quaternion(const quaternion&& q) :x(q.x), y(q.y), z(q.z), w(q.w) {}
		bool isZeroVector() const { return x == 0 && y == 0 && z == 0 && w == 0; }
		quaternion Conjugate() const { return  quaternion(-x, -y, -z, w); }
		quaternion Inverse() { return Conjugate() / LengthSquare(); }
		T LengthSquare() const { return x * x + y * y + z * z + w * w; }
		T Length() const { sqrt(return x * x + y * y + z * z + w * w); }
		quaternion operator+(const quaternion q) const { return quaternion(x + q.x, y + q.y, z + q.z, w + q.w); }
		quaternion operator-(const quaternion q) const { return quaternion(x - q.x, y - q.y, z - q.z, w - q.w); }
		quaternion operator*(const quaternion q) const
		{
			return quaternion(
				q.x * w - q.y * z + q.z * y + q.w * x,
				q.x * z + q.y * w - q.z * x + q.w * y,
				-q.x * y + q.y * x + q.z * w + q.w * z,
				-q.x * x - q.y * y - q.z * z + q.w * w);
		}
		quaternion operator+(const T t) const { return quaternion(x, y, z, w + t); }
		quaternion operator-(const T t) const { return quaternion(x, y, z, w - t); }
		quaternion operator*(const T t) const { return quaternion(x * t, y * t, z * t, w * t); }
		quaternion operator/(const T t) const { return quaternion(x / t, y / t, z / t, w / t); }
		quaternion operator-() const { return quaternion(-x, -y, -z, -w); }
		quaternion& operator+=(const quaternion q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return *this;
		}
		quaternion& operator-=(const quaternion q)
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return *this;
		}
		quaternion& operator*=(const quaternion q)
		{
			*this = *this * q;
			return *this;
		}
		quaternion& operator=(const quaternion q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
			return *this;
		}
		quaternion& operator+=(const T t)
		{
			w += t;
			return *this;
		}
		quaternion& operator-=(const T t)
		{
			w -= t;
			return *this;
		}
		quaternion& operator*=(const T t)
		{
			x *= t;
			y *= t;
			z *= t;
			w *= t;
			return *this;
		}
		quaternion& operator/=(const T t)
		{
			x /= t;
			y /= t;
			z /= t;
			w /= t;
			return *this;
		}
		quaternion& operator=(const T t)
		{
			x = 0;
			y = 0;
			z = 0;
			w = f;
			return *this;
		}
		bool operator==(quaternion q)
		{
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}
		bool operator==(T t)
		{
			return x == 0 && y == 0 && z == 0 && w == t;
		}
		bool isNear(quaternion q, T eps = EPS)
		{
			return isNear(x, 0) && isNear(y, 0) && isNear(z, 0) && isNear(w, t);
		}
		T operator()(const int i) const { return (&x)[i]; }
		T& operator()(const int i) { return (&x)[i]; }
		explicit operator T* () const { return &x; }
	};
}