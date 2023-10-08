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
	class mat2x2
	{
		T m_mat[2][2];

	public:
		explicit mat2x2()
		{
			m_mat[0][0] = 0; m_mat[0][1] = 0;
			m_mat[1][0] = 0; m_mat[1][1] = 0;
		}
		explicit mat2x2(T t)
		{
			m_mat[0][0] = t; m_mat[0][1] = t;
			m_mat[1][0] = t; m_mat[1][1] = t;
		}
		explicit mat2x2(const T* const m)
		{
			m_mat[0][0] = m[0]; m_mat[0][1] = m[1];
			m_mat[1][0] = m[2]; m_mat[1][1] = m[3];
		}
		explicit mat2x2(T _00, T _01, T _10, T _11)
		{
			m_mat[0][0] = _00; m_mat[0][1] = _01;
			m_mat[1][0] = _10; m_mat[1][1] = _11;
		}
		mat2x2(const mat2x2<T>& m)
		{
			m_mat[0][0] = m.m_mat[0][0]; m_mat[0][1] = m.m_mat[0][1];
			m_mat[1][0] = m.m_mat[1][0]; m_mat[1][1] = m.m_mat[1][1];
		}
		mat2x2(mat2x2<T>&& m)
		{
			m_mat[0][0] = m.m_mat[0][0]; m_mat[0][1] = m.m_mat[0][1];
			m_mat[1][0] = m.m_mat[1][0]; m_mat[1][1] = m.m_mat[1][1];
		}
		explicit mat2x2(const mat3x3<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1);
		}
		explicit mat2x2(const mat4x4<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1);
		}
		static mat2x2<T> Identity() { return mat2x2<T>(1, 0, 0, 1); }
		static mat2x2<T> Rotation(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat2x2<T>(ca, -sa, sa, ca);
		}
		static mat2x2<T> Scaling(T x, T y)
		{
			return  mat2x2<T>(x, 0, 0, y);
		}
		static mat2x2<T> Scaling(vec2<T> s)
		{
			return  mat2x2<T>(s.x, 0, 0, s.y);
		}
		static mat2x2<T> RotationScaling(T a, T x, T y)
		{
			T ca = cos(a), sa = sin(a);
			return  mat2x2<T>(ca * x, -sa * x, sa * y, ca * y);
		}
		static mat2x2<T> RotationScaling(vec2<T> a, vec2<T> s)
		{
			T ca = cos(a), sa = sin(a);
			return mat2x2<T>(ca * s.x, -sa * s.x, sa * s.y, ca * s.y);
		}

		T operator()(int row, int column) const { return m_mat[row][column]; }
		T& operator()(int row, int column) { return m_mat[row][column]; }
		vec2<T> operator*(vec2<T> v) const
		{
			return vec2<T>(
				m_mat[0][0] * v.x + m_mat[0][1] * v.y,
				m_mat[1][0] * v.x + m_mat[1][1] * v.y);
		}
		explicit operator T* () { return &m_mat[0][0]; }
		explicit operator mat3x3<T>() const
		{
			return mat3x3<T>(
				m_mat[0][0], m_mat[0][1], 0,
				m_mat[1][0], m_mat[1][1], 0,
				0, 0, 1);
		}
		explicit operator mat4x4<T>() const
		{
			return  mat4x4<T>(
				m_mat[0][0], m_mat[0][1], 0, 0,
				m_mat[1][0], m_mat[1][1], 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}
		T Determinant() const { return m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0]; }
		void Invert() { *this = Inverse(); }
		mat2x2<T> Inverse() const
		{
			T det = Determinant();
			return mat2x2<T>(
				m_mat[1][1] / det, m_mat[0][1] / -det,
				m_mat[1][0] / -det, m_mat[0][0] / det);
		}
		void Transpose()
		{
			T tmp = m_mat[0][1];
			m_mat[0][1] = m_mat[1][0];
			m_mat[1][0] = tmp;
		}
		mat2x2<T> Trasposed() const
		{
			return mat2x2<T>(
				m_mat[0][0], m_mat[1][0],
				m_mat[0][1], m_mat[1][1]);
		}
		mat2x2<T> operator*(const mat2x2<T>& m) const
		{
			return mat2x2<T>(
				m_mat[0][0] * m(0, 0) + m_mat[0][1] * m(1, 0), m_mat[0][0] * m(0, 1) + m_mat[0][1] * m(1, 1),
				m_mat[1][0] * m(0, 0) + m_mat[1][1] * m(1, 0), m_mat[1][0] * m(0, 1) + m_mat[1][1] * m(1, 1));
		}
		mat2x2<T> operator+(const mat2x2<T>& m) const
		{
			return mat2x2<T>(
				m_mat[0][0] + m(0, 0), m_mat[0][1] + m(0, 1),
				m_mat[1][0] + m(1, 0), m_mat[1][1] + m(1, 1));
		}
		mat2x2<T> operator-(const mat2x2<T>& m) const
		{
			return mat2x2<T>(
				m_mat[0][0] - m(0, 0), m_mat[0][1] - m(0, 1),
				m_mat[1][0] - m(1, 0), m_mat[1][1] - m(1, 1));
		}
		mat2x2<T>& operator=(const mat2x2<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1);
			return *this;
		}
		mat2x2<T> operator+(T t) const
		{
			return mat2x2<T>(
				m_mat[0][0] + t, m_mat[0][1] + t,
				m_mat[1][0] + t, m_mat[1][1] + t);
		}
		mat2x2<T>& operator+=(T t)
		{
			m_mat[0][0] += t; m_mat[0][1] += t;
			m_mat[1][0] += t; m_mat[1][1] += t;
			return *this;
		}
		mat2x2<T> operator-(T t) const
		{
			return mat2x2<T>(
				m_mat[0][0] - t, m_mat[0][1] - t,
				m_mat[1][0] - t, m_mat[1][1] - t);
		}
		mat2x2<T>& operator-=(T t)
		{
			m_mat[0][0] -= t; m_mat[0][1] -= t;
			m_mat[1][0] -= t; m_mat[1][1] -= t;
			return *this;
		}
		mat2x2<T> operator*(T t) const
		{
			return mat2x2<T>(
				m_mat[0][0] * t, m_mat[0][1] * t,
				m_mat[1][0] * t, m_mat[1][1] * t);
		}
		mat2x2<T>& operator*=(T t)
		{
			m_mat[0][0] *= t; m_mat[0][1] *= t;
			m_mat[1][0] *= t; m_mat[1][1] *= t;
			return *this;
		};
		mat2x2<T> operator/(T t) const
		{
			return mat2x2<T>(
				m_mat[0][0] / t, m_mat[0][1] / t,
				m_mat[1][0] / t, m_mat[1][1] / t);
		}
		mat2x2<T>& operator/=(T t)
		{
			m_mat[0][0] /= t; m_mat[0][1] /= t;
			m_mat[1][0] /= t; m_mat[1][1] /= t;
			return *this;
		}
		mat2x2<T>& operator=(T t)
		{
			m_mat[0][0] = t; m_mat[0][1] = t;
			m_mat[1][0] = t; m_mat[1][1] = t;
			return *this;
		}
		mat2x2<T> operator-() const
		{
			return mat2x2<T>(
				-m_mat[0][0], -m_mat[0][1],
				-m_mat[1][0], -m_mat[1][1]);
		}
		bool operator==(mat2x2<T> m) const
		{
			return
				m_mat[0][0] == m(0, 0) && m_mat[0][1] == m(0, 1) &&
				m_mat[1][0] == m(1, 0) && m_mat[1][1] == m(1, 1);
		}
		bool operator!=(mat2x2<T> m) const
		{
			return
				m_mat[0][0] != m(0, 0) ||
				m_mat[0][1] != m(0, 1) ||
				m_mat[1][0] != m(1, 0) ||
				m_mat[1][1] != m(1, 1);
		}
		bool isNear(mat2x2<T> m, T eps = EPS) const
		{
			return
				isNear(m_mat[0][0], m(0, 0), eps) && isNear(m_mat[0][1], m(0, 1), eps) &&
				isNear(m_mat[1][0], m(1, 0), eps) && isNear(m_mat[1][1], m(1, 1), eps);
		}
		template <typename S>
		explicit operator mat2x2<S>() const
		{
			return mat2x2<S>(
				m_mat[0][0], m_mat[0][1],
				m_mat[1][0], m_mat[1][1]);
		}
		template <typename S>
		mat2x2<S> WithType() const { return (mat2x2<S>) * this; }
	};

	template <typename T>
	mat2x2<T> operator+(T t, const mat2x2<T>& m) { return m + t; }
	template <typename T>
	mat2x2<T> operator-(T t, const mat2x2<T>& m) { return mat2x2<T>(t) - m; }
	template <typename T>
	mat2x2<T> operator*(T t, const mat2x2<T>& m) { return m * t; }
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const mat2x2<T>& m)
	{
		os <<
			m(0, 0) << ' ' << m(0, 1) << '\n' <<
			m(1, 0) << ' ' << m(1, 1) << '\n';
		return os;
	}
	template <typename T>
	std::istream& operator>>(std::istream& is, mat2x2<T>& m)
	{
		is >>
			m(0, 0) >> m(0, 1) >>
			m(1, 0) >> m(1, 1);
		return is;
	}
	template <typename T>
	std::wostream& operator<<(std::wostream& os, const mat2x2<T>& m)
	{
		os <<
			m(0, 0) << ' ' << m(0, 1) << '\n' <<
			m(1, 0) << ' ' << m(1, 1) << '\n';
		return os;
	}
	template <typename T>
	std::wistream& operator>>(std::wistream& is, mat2x2<T>& m)
	{
		is >>
			m(0, 0) >> m(0, 1) >>
			m(1, 0) >> m(1, 1);
		return is;
	}
}