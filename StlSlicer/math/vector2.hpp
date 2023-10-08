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
	class vec2
	{
	public:
		T x;
		T y;

	public:
		explicit vec2() :x(0), y(0) {}
		explicit vec2(T t) :x(t), y(t) {}
		explicit vec2(const T* const v) :x(v[0]), y(v[1]) {}
		explicit vec2(T x, T y) :x(x), y(y) {}
		vec2(const vec2<T>& v) :x(v.x), y(v.y) {}
		vec2(vec2<T>&& v) :x(v.x), y(v.y) {}
		explicit vec2(vec3<T> v) :x(v.x), y(v.y) {}
		explicit vec2(vec4<T> v) :x(v.x), y(v.y) {}
		bool isZeroVector() const { return x == 0 && y == 0; }
		T Dot(vec2<T> v) const { return x * v.x + y * v.y; }
		T Cross(vec2<T> v) const { return x * v.y - v.x * y; }
		T LengthSquare() const { return x * x + y * y; }
		T Length() const { return std::sqrt(LengthSquare()); }
		T Angle() const { return std::atan2(y, x); }
		void Abs() { x = std::fabs(x); y = std::fabs(y); }
		T Max() const { return x > y ? x : y; }
		T Min() const { return x < y ? x : y; }
		T Sum() const { return x + y; }
		void Normalize() { *this /= Length(); }
		vec2<T> Normalized() const { return *this / Length(); }
		vec2<T> operator+(vec2<T> v) const { return vec2<T>(x + v.x, y + v.y); }
		vec2<T> operator-(vec2<T> v) const { return vec2<T>(x - v.x, y - v.y); }
		vec2<T> operator*(vec2<T> v) const { return vec2<T>(x * v.x, y * v.y); }
		vec2<T> operator/(vec2<T> v) const { return vec2<T>(x / v.x, y / v.y); }
		vec2<T> operator+(T t) const { return vec2<T>(x + t, y + t); }
		vec2<T> operator-(T t) const { return vec2<T>(x - t, y - t); }
		vec2<T> operator*(T t) const { return vec2<T>(x * t, y * t); }
		vec2<T> operator/(T t) const { return vec2<T>(x / t, y / t); }
		vec2<T> operator-() const { return vec2<T>(-x, -y); }
		vec2<T>& operator+=(vec2<T> v) { x += v.x; y += v.y; return *this; }
		vec2<T>& operator-=(vec2<T> v) { x -= v.x; y -= v.y; return *this; }
		vec2<T>& operator*=(vec2<T> v) { x *= v.x; y *= v.y; return *this; }
		vec2<T>& operator/=(vec2<T> v) { x /= v.x; y /= v.y; return *this; }
		vec2<T>& operator=(vec2<T> v) { x = v.x; y = v.y; return *this; }
		vec2<T>& operator+=(T t) { x += t; y += t; return *this; }
		vec2<T>& operator-=(T t) { x -= t; y -= t; return *this; }
		vec2<T>& operator*=(T t) { x *= t; y *= t; return *this; }
		vec2<T>& operator/=(T t) { x /= t; y /= t; return *this; }
		vec2<T>& operator=(T t) { x = t; y = t; return *this; }
		vec2<T> operator*(const mat2x2<T>& m) const
		{
			return vec2<T>(
				x * m(0, 0) + y * m(1, 0),
				x * m(0, 1) + y * m(1, 1));
		}
		bool operator==(vec2<T> v) const { return x == v.x && y == v.y; }
		bool operator!=(vec2<T> v) const { return x != v.x || y != v.y; }
		bool isNear(vec2<T> v, T eps = EPS)
		{
			return
				isNear(x, v.x, eps) &&
				isNear(y, v.y, eps);
		}
		T operator()(int i) const { return (&x)[i]; }
		T& operator()(int i) { return (&x)[i]; }
		explicit operator vec3<T>() const { return vec3<T>(*this, 0); }
		explicit operator vec4<T>() const { return vec4<T>(*this, 0, 0); }
		explicit operator T* () const { return &x; }
		template <typename S>
		explicit operator vec2<S>() const { return vec2<S>(x, y); }
		template <typename S>
		vec2<S> WithType() const { return (vec2<S>) * this; }
	};

	template <typename T>
	vec2<T> operator+(T t, vec2<T> v) { return v + t; }
	template <typename T>
	vec2<T> operator-(T t, vec2<T> v) { return vec2<T>(t) - v; }
	template <typename T>
	vec2<T> operator*(T t, vec2<T> v) { return v * t; }
	template <typename T>
	std::ostream& operator<<(std::ostream& os, vec2<T> v)
	{
		os << v.x << ' ' << v.y;
		return os;
	}
	template <typename T>
	std::istream& operator>>(std::istream& is, vec2<T>& v)
	{
		is >> v.x >> v.y;
		return is;
	}
	template <typename T>
	std::wostream& operator<<(std::wostream& os, vec2<T> v)
	{
		os << v.x << ' ' << v.y;
		return os;
	}
	template <typename T>
	std::wistream& operator>>(std::wistream& is, vec2<T>& v)
	{
		is >> v.x >> v.y;
		return is;
	}
}