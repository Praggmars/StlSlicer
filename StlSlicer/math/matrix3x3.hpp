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
	class mat3x3
	{
		T m_mat[3][3];

	public:
		explicit mat3x3()
		{
			m_mat[0][0] = 0; m_mat[0][1] = 0; m_mat[0][2] = 0;
			m_mat[1][0] = 0; m_mat[1][1] = 0; m_mat[1][2] = 0;
			m_mat[2][0] = 0; m_mat[2][1] = 0; m_mat[2][2] = 0;
		}
		explicit mat3x3(T t)
		{
			m_mat[0][0] = t; m_mat[0][1] = t; m_mat[0][2] = t;
			m_mat[1][0] = t; m_mat[1][1] = t; m_mat[1][2] = t;
			m_mat[2][0] = t; m_mat[2][1] = t; m_mat[2][2] = t;
		}
		explicit mat3x3(const T* const m)
		{
			m_mat[0][0] = m[0]; m_mat[0][1] = m[1]; m_mat[0][2] = m[2];
			m_mat[1][0] = m[3]; m_mat[1][1] = m[4]; m_mat[1][2] = m[5];
			m_mat[2][0] = m[6]; m_mat[2][1] = m[7]; m_mat[2][2] = m[8];
		}
		explicit mat3x3(
			T _00, T _01, T _02,
			T _10, T _11, T _12,
			T _20, T _21, T _22)
		{
			m_mat[0][0] = _00; m_mat[0][1] = _01; m_mat[0][2] = _02;
			m_mat[1][0] = _10; m_mat[1][1] = _11; m_mat[1][2] = _12;
			m_mat[2][0] = _20; m_mat[2][1] = _21; m_mat[2][2] = _22;
		}
		explicit mat3x3(const mat2x2<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = 0;
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = 0;
			m_mat[2][0] = 0; m_mat[2][1] = 0; m_mat[2][2] = 1;
		}
		mat3x3(const mat3x3<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2);
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2);
		}
		mat3x3(mat3x3<T>&& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2);
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2);
		}
		explicit mat3x3(const mat4x4<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2);
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2);
		}
		static mat3x3<T> Identity()
		{
			return mat3x3<T>(
				1, 0, 0,
				0, 1, 0,
				0, 0, 1);
		}
		static mat3x3<T> Scaling2D(T x, T y)
		{
			return mat3x3<T>(
				x, 0, 0,
				0, y, 0,
				0, 0, 1);
		}
		static mat3x3<T> Scaling2D(vec2<T> s)
		{
			return mat3x3<T>(
				s.x, 0, 0,
				0, s.y, 0,
				0, 0, 1);
		}
		static mat3x3<T> Translation2D(T x, T y)
		{
			return mat3x3<T>(
				1, 0, x,
				0, 1, y,
				0, 0, 1);
		}
		static mat3x3<T> Translation2D(vec2<T> t)
		{
			return mat3x3<T>(
				1, 0, t.x,
				0, 1, t.y,
				0, 0, 1);
		}
		static mat3x3<T> Rotation2D(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat3x3<T>(
				ca, -sa, 0,
				sa, ca, 0,
				0, 0, 1);
		}
		static mat3x3<T> Scaling(T x, T y, T z)
		{
			return mat3x3<T>(
				x, 0, 0,
				0, y, 0,
				0, 0, z);
		}
		static mat3x3<T> Scaling(vec3<T> s)
		{
			return mat3x3<T>(
				s.x, 0, 0,
				0, s.y, 0,
				0, 0, s.z);
		}
		static mat3x3<T> RotationX(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat3x3<T>(
				1, 0, 0,
				0, ca, -sa,
				0, sa, ca);
		}
		static mat3x3<T> RotationY(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat3x3<T>(
				ca, 0, sa,
				0, 1, 0,
				-sa, 0, ca);
		}
		static mat3x3<T> RotationZ(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat3x3<T>(
				ca, -sa, 0,
				sa, ca, 0,
				0, 0, 1);
		}
		static mat3x3<T> Rotation(T pitch, T yaw, T roll)
		{
			T cp = cos(pitch), sp = sin(pitch), cy = cos(yaw), sy = sin(yaw), cr = cos(roll), sr = sin(roll);
			return mat3x3<T>(
				sy * sp * sr + cy * cr, sy * sp * cr - cy * sr, sy * cp,
				cp * sr, cp * cr, -sp,
				cy * sp * sr - sy * cr, cy * sp * cr + sy * sr, cy * cp);
		}
		static mat3x3<T> Rotation(vec3<T> r)
		{
			T cp = cos(r.x), sp = sin(r.x), cy = cos(r.y), sy = sin(r.y), cr = cos(r.z), sr = sin(r.z);
			return mat3x3<T>(
				sy * sp * sr + cy * cr, sy * sp * cr - cy * sr, sy * cp,
				cp * sr, cp * cr, -sp,
				cy * sp * sr - sy * cr, cy * sp * cr + sy * sr, cy * cp);
		}
		static mat3x3<T> RotationAxis(vec3<T> axis, T a)
		{
			return RotationNormal(axis.Normalized(), a);
		}
		static mat3x3<T> RotationNormal(vec3<T> n, T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat3x3<T>(
				ca + n.x * n.x * (1 - ca), n.x * n.y * (1 - ca) - n.z * sa, n.x * n.z * (1 - ca) + n.y * sa,
				n.y * n.x * (1 - ca) + n.z * sa, ca + n.y * n.y * (1 - ca), n.y * n.z * (1 - ca) - n.x * sa,
				n.z * n.x * (1 - ca) - n.y * sa, n.z * n.y * (1 - ca) + n.x * sa, ca + n.z * n.z * (1 - ca));
		}
		static mat3x3<T> RotationCamera(T pitch, T yaw, T roll)
		{
			T sx = sin(-pitch), cx = cos(-pitch), sy = sin(-yaw), cy = cos(-yaw), sz = sin(-roll), cz = cos(-roll);
			return mat3x3<T>(
				cy * cz - sx * sy * sz, -cx * sz, sy * cz + sx * cy * sz,
				cy * sz + sx * sy * cz, cx * cz, sy * sz - sx * cy * cz,
				-cx * sy, sx, cx * cy);
		}
		static mat3x3<T> RotationCamera(vec3<T> r)
		{
			T sx = sin(-r.x), cx = cos(-r.x), sy = sin(-r.y), cy = cos(-r.y), sz = sin(-r.z), cz = cos(-r.z);
			return mat3x3<T>(
				cy * cz - sx * sy * sz, -cx * sz, sy * cz + sx * cy * sz,
				cy * sz + sx * sy * cz, cx * cz, sy * sz - sx * cy * cz,
				-cx * sy, sx, cx * cy);
		}

		static mat3x3<T> RotateUnitVector(vec3<T> from, vec3<T> to)
		{
			vec3<T> v = from.Cross(to);
			T t = 1 / (1 + from.Dot(to));
			return mat3x3<T>(
				1 - v.y * v.y * t - v.z * v.z * t, v.x * v.y * t - v.z, v.x * v.z * t + v.y,
				v.x * v.y * t + v.z, 1 - v.x * v.x * t - v.z * v.z * t, v.y * v.z * t - v.x,
				v.x * v.z * t - v.y, v.y * v.z * t + v.x, 1 - v.x * v.x * t - v.y * v.y * t
				);
		}
		vec3<T> ToRotationAngles() const
		{
			vec3<T> a;
			a.y = atan2(m_mat[0][2], m_mat[2][2]);
			a.x = atan2(-m_mat[1][2], fabs(a.y) < 0.25 ? m_mat[2][2] / cos(a.y) : m_mat[0][2] / sin(a.y));
			a.z = atan2(m_mat[1][0], m_mat[1][1]);
			return a;
		}
		vec3<T> ToCameraRotation() const
		{
			vec3<T> a;
			a.z = -atan2(-m_mat[0][1], m_mat[1][1]);
			a.y = -atan2(-m_mat[2][0], m_mat[2][1]);
			a.x = -asin(m_mat[2][1]);
			return a;
		}

		T operator()(int row, int column) const
		{
			return m_mat[row][column];
		}
		T& operator()(int row, int column)
		{
			return m_mat[row][column];
		}
		vec3<T> operator*(vec3<T> v) const
		{
			return vec3<T>(
				m_mat[0][0] * v.x + m_mat[0][1] * v.y + m_mat[0][2] * v.z,
				m_mat[1][0] * v.x + m_mat[1][1] * v.y + m_mat[1][2] * v.z,
				m_mat[2][0] * v.x + m_mat[2][1] * v.y + m_mat[2][2] * v.z);
		}
		explicit operator mat2x2<T>() const
		{
			return mat2x2<T>(
				m_mat[0][0], m_mat[0][1],
				m_mat[1][0], m_mat[1][1]);
		}
		explicit operator mat4x4<T>() const
		{
			return mat4x4<T>(
				m_mat[0][0], m_mat[0][1], m_mat[0][2], 0,
				m_mat[1][0], m_mat[1][1], m_mat[1][2], 0,
				m_mat[2][0], m_mat[2][1], m_mat[2][2], 0,
				0, 0, 0, 1);
		}
		T Determinant() const
		{
			return
				m_mat[0][0] * m_mat[1][1] * m_mat[2][2] +
				m_mat[0][1] * m_mat[1][2] * m_mat[2][0] +
				m_mat[0][2] * m_mat[1][0] * m_mat[2][1] -
				m_mat[0][2] * m_mat[1][1] * m_mat[2][0] -
				m_mat[0][0] * m_mat[1][2] * m_mat[2][1] -
				m_mat[0][1] * m_mat[1][0] * m_mat[2][2];
		}
		void Invert()
		{
			*this = Inverse();
		}
		mat3x3<T> Inverse() const
		{
			float det = Determinant();
			return mat3x3<T>(
				mat2x2<T>(m_mat[1][1], m_mat[1][2], m_mat[2][1], m_mat[2][2]).Determinant() / det,
				mat2x2<T>(m_mat[0][1], m_mat[0][2], m_mat[2][1], m_mat[2][2]).Determinant() / -det,
				mat2x2<T>(m_mat[0][1], m_mat[0][2], m_mat[1][1], m_mat[1][2]).Determinant() / det,

				mat2x2<T>(m_mat[1][0], m_mat[1][2], m_mat[2][0], m_mat[2][2]).Determinant() / -det,
				mat2x2<T>(m_mat[0][0], m_mat[0][2], m_mat[2][0], m_mat[2][2]).Determinant() / det,
				mat2x2<T>(m_mat[0][0], m_mat[0][2], m_mat[1][0], m_mat[1][2]).Determinant() / -det,

				mat2x2<T>(m_mat[1][0], m_mat[1][1], m_mat[2][0], m_mat[2][1]).Determinant() / det,
				mat2x2<T>(m_mat[0][0], m_mat[0][1], m_mat[2][0], m_mat[2][1]).Determinant() / -det,
				mat2x2<T>(m_mat[0][0], m_mat[0][1], m_mat[1][0], m_mat[1][1]).Determinant() / det);
		}
		void Transpose()
		{
			T tmp;
			tmp = m_mat[0][1]; m_mat[0][1] = m_mat[1][0]; m_mat[1][0] = tmp;
			tmp = m_mat[0][2]; m_mat[0][2] = m_mat[2][0]; m_mat[2][0] = tmp;
			tmp = m_mat[1][2]; m_mat[1][2] = m_mat[2][1]; m_mat[2][1] = tmp;
		}
		mat3x3<T> Transposed() const
		{
			return mat3x3<T>(
				m_mat[0][0], m_mat[1][0], m_mat[2][0],
				m_mat[0][1], m_mat[1][1], m_mat[2][1],
				m_mat[0][2], m_mat[1][2], m_mat[2][2]);
		}
		mat3x3<T> operator*(const mat3x3<T>& m) const
		{
			return mat3x3<T>(
				m_mat[0][0] * m(0, 0) + m_mat[0][1] * m(1, 0) + m_mat[0][2] * m(2, 0),
				m_mat[0][0] * m(0, 1) + m_mat[0][1] * m(1, 1) + m_mat[0][2] * m(2, 1),
				m_mat[0][0] * m(0, 2) + m_mat[0][1] * m(1, 2) + m_mat[0][2] * m(2, 2),
				m_mat[1][0] * m(0, 0) + m_mat[1][1] * m(1, 0) + m_mat[1][2] * m(2, 0),
				m_mat[1][0] * m(0, 1) + m_mat[1][1] * m(1, 1) + m_mat[1][2] * m(2, 1),
				m_mat[1][0] * m(0, 2) + m_mat[1][1] * m(1, 2) + m_mat[1][2] * m(2, 2),
				m_mat[2][0] * m(0, 0) + m_mat[2][1] * m(1, 0) + m_mat[2][2] * m(2, 0),
				m_mat[2][0] * m(0, 1) + m_mat[2][1] * m(1, 1) + m_mat[2][2] * m(2, 1),
				m_mat[2][0] * m(0, 2) + m_mat[2][1] * m(1, 2) + m_mat[2][2] * m(2, 2));
		}
		mat3x3<T> operator+(const mat3x3<T>& m) const
		{
			return mat3x3<T>(
				m_mat[0][0] + m(0, 0), m_mat[0][1] + m(0, 1), m_mat[0][2] + m(0, 2),
				m_mat[1][0] + m(1, 0), m_mat[1][1] + m(1, 1), m_mat[1][2] + m(1, 2),
				m_mat[2][0] + m(2, 0), m_mat[2][1] + m(2, 1), m_mat[2][2] + m(2, 2));
		}
		mat3x3<T>& operator+=(const mat3x3<T>& m)
		{
			m_mat[0][0] += m(0, 0); m_mat[0][1] += m(0, 1); m_mat[0][2] += m(0, 2);
			m_mat[1][0] += m(1, 0); m_mat[1][1] += m(1, 1); m_mat[1][2] += m(1, 2);
			m_mat[2][0] += m(2, 0); m_mat[2][1] += m(2, 1); m_mat[2][2] += m(2, 2);
			return *this;
		}
		mat3x3<T> operator-(const mat3x3<T>& m) const
		{
			return mat3x3<T>(
				m_mat[0][0] - m(0, 0), m_mat[0][1] - m(0, 1), m_mat[0][2] - m(0, 2),
				m_mat[1][0] - m(1, 0), m_mat[1][1] - m(1, 1), m_mat[1][2] - m(1, 2),
				m_mat[2][0] - m(2, 0), m_mat[2][1] - m(2, 1), m_mat[2][2] - m(2, 2));
		}
		mat3x3<T>& operator-=(const mat3x3<T>& m)
		{
			m_mat[0][0] -= m(0, 0); m_mat[0][1] -= m(0, 1); m_mat[0][2] -= m(0, 2);
			m_mat[1][0] -= m(1, 0); m_mat[1][1] -= m(1, 1); m_mat[1][2] -= m(1, 2);
			m_mat[2][0] -= m(2, 0); m_mat[2][1] -= m(2, 1); m_mat[2][2] -= m(2, 2);
			return *this;
		}
		mat3x3<T>& operator=(const mat3x3<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2);
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2);
			return *this;
		}
		mat3x3<T> operator+(T t) const
		{
			return mat3x3<T>(
				m_mat[0][0] + t, m_mat[0][1] + t, m_mat[0][2] + t,
				m_mat[1][0] + t, m_mat[1][1] + t, m_mat[1][2] + t,
				m_mat[2][0] + t, m_mat[2][1] + t, m_mat[2][2] + t);
		}
		mat3x3<T>& operator+=(T t)
		{
			m_mat[0][0] += t; m_mat[0][1] += t; m_mat[0][2] += t;
			m_mat[1][0] += t; m_mat[1][1] += t; m_mat[1][2] += t;
			m_mat[2][0] += t; m_mat[2][1] += t; m_mat[2][2] += t;
			return *this;
		}
		mat3x3<T> operator-(T t) const
		{
			return mat3x3<T>(
				m_mat[0][0] - t, m_mat[0][1] - t, m_mat[0][2] - t,
				m_mat[1][0] - t, m_mat[1][1] - t, m_mat[1][2] - t,
				m_mat[2][0] - t, m_mat[2][1] - t, m_mat[2][2] - t);
		}
		mat3x3<T>& operator-=(T t)
		{
			m_mat[0][0] -= t; m_mat[0][1] -= t; m_mat[0][2] -= t;
			m_mat[1][0] -= t; m_mat[1][1] -= t; m_mat[1][2] -= t;
			m_mat[2][0] -= t; m_mat[2][1] -= t; m_mat[2][2] -= t;
			return *this;
		}
		mat3x3<T> operator*(T t) const
		{
			return mat3x3<T>(
				m_mat[0][0] * t, m_mat[0][1] * t, m_mat[0][2] * t,
				m_mat[1][0] * t, m_mat[1][1] * t, m_mat[1][2] * t,
				m_mat[2][0] * t, m_mat[2][1] * t, m_mat[2][2] * t);
		}
		mat3x3<T>& operator*=(T t)
		{
			m_mat[0][0] *= t; m_mat[0][1] *= t; m_mat[0][2] *= t;
			m_mat[1][0] *= t; m_mat[1][1] *= t; m_mat[1][2] *= t;
			m_mat[2][0] *= t; m_mat[2][1] *= t; m_mat[2][2] *= t;
			return *this;
		}
		mat3x3<T> operator/(T t) const
		{
			return mat3x3<T>(
				m_mat[0][0] / t, m_mat[0][1] / t, m_mat[0][2] / t,
				m_mat[1][0] / t, m_mat[1][1] / t, m_mat[1][2] / t,
				m_mat[2][0] / t, m_mat[2][1] / t, m_mat[2][2] / t);
		}
		mat3x3<T>& operator/=(T t)
		{
			m_mat[0][0] /= t; m_mat[0][1] /= t; m_mat[0][2] /= t;
			m_mat[1][0] /= t; m_mat[1][1] /= t; m_mat[1][2] /= t;
			m_mat[2][0] /= t; m_mat[2][1] /= t; m_mat[2][2] /= t;
			return *this;
		}
		mat3x3<T>& operator=(T t)
		{
			m_mat[0][0] = t; m_mat[0][1] = t; m_mat[0][2] = t;
			m_mat[1][0] = t; m_mat[1][1] = t; m_mat[1][2] = t;
			m_mat[2][0] = t; m_mat[2][1] = t; m_mat[2][2] = t;
			return *this;
		}
		mat3x3<T> operator-() const
		{
			return mat3x3<T>(
				-m_mat[0][0], -m_mat[0][1], -m_mat[0][2],
				-m_mat[1][0], -m_mat[1][1], -m_mat[1][2],
				-m_mat[2][0], -m_mat[2][1], -m_mat[2][2]);
		}
		bool operator==(mat3x3<T> m) const
		{
			return
				m_mat[0][0] == m(0, 0) && m_mat[0][1] == m(0, 1) && m_mat[0][2] == m(0, 2) &&
				m_mat[1][0] == m(1, 0) && m_mat[1][1] == m(1, 1) && m_mat[1][2] == m(1, 2) &&
				m_mat[2][0] == m(2, 0) && m_mat[2][1] == m(2, 1) && m_mat[2][2] == m(2, 2);
		}
		bool operator!=(mat3x3<T> m) const
		{
			return
				m_mat[0][0] != m(0, 0) || m_mat[0][1] != m(0, 1) || m_mat[0][2] != m(0, 2) ||
				m_mat[1][0] != m(1, 0) || m_mat[1][1] != m(1, 1) || m_mat[1][2] != m(1, 2) ||
				m_mat[2][0] != m(2, 0) || m_mat[2][1] != m(2, 1) || m_mat[2][2] != m(2, 2);
		}
		bool isNear(mat3x3<T> m, T eps = EPS) const
		{
			return
				isNear(m_mat[0][0], m(0, 0), eps) && isNear(m_mat[0][1], m(0, 1), eps) && isNear(m_mat[0][2], m(0, 2), eps) &&
				isNear(m_mat[1][0], m(1, 0), eps) && isNear(m_mat[1][1], m(1, 1), eps) && isNear(m_mat[1][2], m(1, 2), eps) &&
				isNear(m_mat[2][0], m(2, 0), eps) && isNear(m_mat[2][1], m(2, 1), eps) && isNear(m_mat[2][2], m(2, 2), eps);
		}
		template <typename S>
		explicit operator mat3x3<S>() const
		{
			return mat3x3<S>(
				m_mat[0][0], m_mat[0][1], m_mat[0][2],
				m_mat[1][0], m_mat[1][1], m_mat[1][2],
				m_mat[2][0], m_mat[2][1], m_mat[2][2]);
		}
		template <typename S>
		mat3x3<S> WithType() const { return (mat3x3<S>) * this; }
	};

	template <typename T>
	mat3x3<T> operator+(const T t, const mat3x3<T>& m) { return m + t; }
	template <typename T>
	mat3x3<T> operator-(const T t, const mat3x3<T>& m) { return mat3x3<T>(t) - m; }
	template <typename T>
	mat3x3<T> operator*(const T t, const mat3x3<T>& m) { return m * t; }
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const mat3x3<T>& m)
	{
		os <<
			m(0, 0) << ' ' << m(0, 1) << ' ' << m(0, 2) << '\n' <<
			m(1, 0) << ' ' << m(1, 1) << ' ' << m(1, 2) << '\n' <<
			m(2, 0) << ' ' << m(2, 1) << ' ' << m(2, 2) << '\n';
		return os;
	}
	template <typename T>
	std::istream& operator>>(std::istream& is, mat3x3<T>& m)
	{
		is >>
			m(0, 0) >> m(0, 1) >> m(0, 2) >>
			m(1, 0) >> m(1, 1) >> m(1, 2) >>
			m(2, 0) >> m(2, 1) >> m(2, 2);
		return is;
	}
	template <typename T>
	std::wostream& operator<<(std::wostream& os, const mat3x3<T>& m)
	{
		os <<
			m(0, 0) << ' ' << m(0, 1) << ' ' << m(0, 2) << '\n' <<
			m(1, 0) << ' ' << m(1, 1) << ' ' << m(1, 2) << '\n' <<
			m(2, 0) << ' ' << m(2, 1) << ' ' << m(2, 2) << '\n';
		return os;
	}
	template <typename T>
	std::wistream& operator>>(std::wistream& is, mat3x3<T>& m)
	{
		is >>
			m(0, 0) >> m(0, 1) >> m(0, 2) >>
			m(1, 0) >> m(1, 1) >> m(1, 2) >>
			m(2, 0) >> m(2, 1) >> m(2, 2);
		return is;
	}
}