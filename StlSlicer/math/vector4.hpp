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
	class vec4
	{
	public:
		T x;
		T y;
		T z;
		T w;

	public:
		explicit vec4() : x(0), y(0), z(0), w(0) {}
		explicit vec4(T t) : x(t), y(t), z(t), w(t) {}
		explicit vec4(const T* const v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}
		explicit vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		explicit vec4(vec2<T> v) : x(v.x), y(v.y), z(0), w(0) {}
		explicit vec4(vec2<T> v, T z, T w) : x(v.x), y(v.y), z(z), w(w) {}
		explicit vec4(vec2<T> v, vec2<T> w) : x(v.x), y(v.y), z(w.x), w(w.z) {}
		explicit vec4(vec3<T> v) : x(v.x), y(v.y), z(v.z), w(w.z) {}
		explicit vec4(vec3<T> v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}
		vec4(const vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
		vec4(vec4<T>&& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}
		bool isZeroVector() const { return x == 0 && y == 0 && z == 0 && w == 0; }
		T Dot(vec4<T> v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
		T LengthSquare() const { return x * x + y * y + z * z + w * w; }
		T Length() const { return std::sqrt(LengthSquare()); }
		void Abs() { x = std::fabs(x); y = std::fabs(y); z = std::fabs(z); w = std::fabs(w); }
		T Max() const
		{
			T max = x;
			if (y > max) max = y;
			if (z > max) max = z;
			return w > max ? w : max;
		}
		T Min() const
		{
			T min = x;
			if (y < min) min = y;
			if (z < min) min = z;
			return w < min ? w : min;
		}
		T Sum() const { return x + y + z + w; }
		void Normalize() { *this /= Length(); }
		vec4<T> Normalized() const { return *this / Length(); }
		vec4<T> operator+(vec4<T> v) const { return vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w); }
		vec4<T> operator-(vec4<T> v) const { return vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w); }
		vec4<T> operator*(vec4<T> v) const { return vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w); }
		vec4<T> operator/(vec4<T> v) const { return vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w); }
		vec4<T> operator+(T t) const { return vec4<T>(x + t, y + t, z + t, w + t); }
		vec4<T> operator-(T t) const { return vec4<T>(x - t, y - t, z - t, w - t); }
		vec4<T> operator*(T t) const { return vec4<T>(x * t, y * t, z * t, w * t); }
		vec4<T> operator/(T t) const { return vec4<T>(x / t, y / t, z / t, w / t); }
		vec4<T> operator-() const { return vec4<T>(-x, -y, -z, -w); }
		vec4<T>& operator+=(vec4<T> v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		vec4<T>& operator-=(vec4<T> v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		vec4<T>& operator*=(vec4<T> v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
		vec4<T>& operator/=(vec4<T> v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
		vec4<T>& operator=(vec4<T> v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
		vec4<T>& operator+=(T t) { x += t; y += t; z += t; w += t; return *this; }
		vec4<T>& operator-=(T t) { x -= t; y -= t; z -= t; w -= t; return *this; }
		vec4<T>& operator*=(T t) { x *= t; y *= t; z *= t; w *= t; return *this; }
		vec4<T>& operator/=(T t) { x /= t; y /= t; z /= t; w /= t; return *this; }
		vec4<T>& operator=(T t) { x = t; y = t; z = t; w = t; return *this; }
		vec4<T> operator*(const mat4x4<T>& m) const
		{
			return vec4<T>(
				x * m(0, 0) + y * m(1, 0) + z * m(2, 0) + w * m(3, 0),
				x * m(0, 1) + y * m(1, 1) + z * m(2, 1) + w * m(3, 1),
				x * m(0, 2) + y * m(1, 2) + z * m(2, 2) + w * m(3, 2),
				x * m(0, 3) + y * m(1, 3) + z * m(2, 3) + w * m(3, 3));
		}
		bool operator==(vec4<T> v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
		bool operator!=(vec4<T> v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }
		bool isNear(vec4<T> v, T eps) const
		{
			return
				isNear(x, v.x, eps) &&
				isNear(y, v.y, eps) &&
				isNear(z, v.z, eps) &&
				isNear(w, v.w, eps);
		}
		T operator()(int i) const { return (&x)[i]; }
		T& operator()(int i) { return (&x)[i]; }
		explicit operator vec2<T>() const { return vec2<T>(x, y); }
		explicit operator vec3<T>() const { return vec3<T>(x, y, z); }
		explicit operator T* () const { return &x; }
		template <typename S>
		explicit operator vec4<S>() const { return vec4<S>(x, y, z, w); }
		template <typename S>
		vec4<S> WithType() const { return (vec4<S>) * this; }
	};

	template <typename T>
	vec4<T> operator+(T t, vec4<T> v) { return v + t; }
	template <typename T>
	vec4<T> operator-(T t, vec4<T> v) { return vec4<T>(t) - v; }
	template <typename T>
	vec4<T> operator*(T t, vec4<T> v) { return v * t; }
	template <typename T>
	std::ostream& operator<<(std::ostream& os, vec4<T> v)
	{
		os << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
		return os;
	}
	template <typename T>
	std::istream& operator>>(std::istream& is, vec4<T>& v)
	{
		is >> v.x >> v.y >> v.z >> v.w;
		return is;
	}
	template <typename T>
	std::wostream& operator<<(std::wostream& os, vec4<T> v)
	{
		os << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
		return os;
	}
	template <typename T>
	std::wistream& operator>>(std::wistream& is, vec4<T>& v)
	{
		is >> v.x >> v.y >> v.z >> v.w;
		return is;
	}
}