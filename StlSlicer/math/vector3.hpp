#pragma once

#include "formulas.hpp"
#include <iostream>

namespace mth
{
	template<typename>class vec2;
	template<typename>class vec3;
	template<typename>class vec4;
	template<typename>class mat2x2;
	template<typename>class mat3x3;
	template<typename>class mat4x4;

	template <typename T>
	class vec3
	{
	public:
		T x;
		T y;
		T z;

	public:
		explicit vec3() : x(0), y(0), z(0) {}
		explicit vec3(T t) : x(t), y(t), z(t) {}
		explicit vec3(const T* const v) : x(v[0]), y(v[1]), z(v[2]) {}
		explicit vec3(T x, T y, T z) : x(x), y(y), z(z) {}
		explicit vec3(vec2<T> v) : x(v.x), y(v.y), z(0) {}
		explicit vec3(vec2<T> v, T z) : x(v.x), y(v.y), z(z) {}
		vec3(const vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}
		vec3(vec3<T>&& v) : x(v.x), y(v.y), z(v.z) {}
		explicit vec3(vec4<T> v) : x(v.x), y(v.y), z(v.z) {}
		bool isZeroVector() const { return x == 0 && y == 0 && z == 0; }
		T Dot(vec3<T> v) const { return x * v.x + y * v.y + z * v.z; }
		vec3<T> Cross(vec3<T> v) const { return vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
		T LengthSquare() const { return x * x + y * y + z * z; }
		T Length() const { return std::sqrt(LengthSquare()); }
		void Abs() { x = std::fabs(x); y = std::fabs(y); z = std::fabs(z); }
		T Max() const { T max = x; if (y > max) max = y; return z > max ? z : max; }
		T Min() const { T min = x; if (y < min) min = y; return z < min ? z : min; }
		T Sum() const { return x + y + z; }
		void Normalize() { *this /= this->Length(); }
		vec3<T> Normalized() const { return *this / this->Length(); }
		vec3<T> operator+(vec3<T> v) const { return vec3<T>(x + v.x, y + v.y, z + v.z); }
		vec3<T> operator-(vec3<T> v) const { return vec3<T>(x - v.x, y - v.y, z - v.z); }
		vec3<T> operator*(vec3<T> v) const { return vec3<T>(x * v.x, y * v.y, z * v.z); }
		vec3<T> operator/(vec3<T> v) const { return vec3<T>(x / v.x, y / v.y, z / v.z); }
		vec3<T> operator+(T t) const { return vec3<T>(x + t, y + t, z + t); }
		vec3<T> operator-(T t) const { return vec3<T>(x - t, y - t, z - t); }
		vec3<T> operator*(T t) const { return vec3<T>(x * t, y * t, z * t); }
		vec3<T> operator/(T t) const { return vec3<T>(x / t, y / t, z / t); }
		vec3<T> operator-() const { return vec3<T>(-x, -y, -z); }
		vec3<T>& operator+=(vec3<T> v) { x += v.x; y += v.y; z += v.z; return *this; }
		vec3<T>& operator-=(vec3<T> v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		vec3<T>& operator*=(vec3<T> v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		vec3<T>& operator/=(vec3<T> v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
		vec3<T>& operator=(vec3<T> v) { x = v.x; y = v.y; z = v.z; return *this; }
		vec3<T>& operator+=(T t) { x += t; y += t; z += t; return *this; }
		vec3<T>& operator-=(T t) { x -= t; y -= t; z -= t; return *this; }
		vec3<T>& operator*=(T t) { x *= t; y *= t; z *= t; return *this; }
		vec3<T>& operator/=(T t) { x /= t; y /= t; z /= t; return *this; }
		vec3<T>& operator=(T t) { x = t; y = t; z = t; return *this; }
		vec3<T> operator*(const mat3x3<T>& m) const
		{
			return vec3<T>(
				x * m(0, 0) + y * m(1, 0) + z * m(2, 0),
				x * m(0, 1) + y * m(1, 1) + z * m(2, 1),
				x * m(0, 2) + y * m(1, 2) + z * m(2, 2));
		}
		bool operator==(vec3<T> v) const { return x == v.x && y == v.y && z == v.z; }
		bool operator!=(vec3<T> v) const { return x != v.x || y != v.y || z != v.z; }
		bool isNear(vec3<T> v, T eps = EPS)
		{
			return
				mth::isNear(x, v.x, eps) &&
				mth::isNear(y, v.y, eps) &&
				mth::isNear(z, v.z, eps);
		}
		T operator()(int i) const { return (&x)[i]; }
		T& operator()(int i) { return (&x)[i]; }
		explicit operator vec2<T>() const { return vec2<T>(x, y); }
		explicit operator vec4<T>() const { return vec4<T>(*this, 0); }
		explicit operator T* () const { return &x; }
		template <typename S>
		explicit operator vec3<S>() const { return vec3<S>(x, y, z); }
		template <typename S>
		vec3<S> WithType() const { return (vec3<S>) * this; }
	};

	template <typename T>
	vec3<T> operator+(T t, vec3<T> v) { return v + t; }
	template <typename T>
	vec3<T> operator-(T t, vec3<T> v) { return vec3<T>(t) - v; }
	template <typename T>
	vec3<T> operator*(T t, vec3<T> v) { return v * t; }
	template <typename T>
	std::ostream& operator<<(std::ostream& os, vec3<T> v)
	{
		os << v.x << ' ' << v.y << ' ' << v.z;
		return os;
	}
	template <typename T>
	std::istream& operator>>(std::istream& is, vec3<T>& v)
	{
		is >> v.x >> v.y >> v.z;
		return is;
	}
	template <typename T>
	std::wostream& operator<<(std::wostream& os, vec3<T> v)
	{
		os << v.x << ' ' << v.y << ' ' << v.z;
		return os;
	}
	template <typename T>
	std::wistream& operator>>(std::wistream& is, vec3<T>& v)
	{
		is >> v.x >> v.y >> v.z;
		return is;
	}
}