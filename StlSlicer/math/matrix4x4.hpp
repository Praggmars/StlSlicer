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
	class mat4x4
	{
		T m_mat[4][4];

	public:
		explicit mat4x4()
		{
			m_mat[0][0] = 0; m_mat[0][1] = 0; m_mat[0][2] = 0; m_mat[0][3] = 0;
			m_mat[1][0] = 0; m_mat[1][1] = 0; m_mat[1][2] = 0; m_mat[1][3] = 0;
			m_mat[2][0] = 0; m_mat[2][1] = 0; m_mat[2][2] = 0; m_mat[2][3] = 0;
			m_mat[3][0] = 0; m_mat[3][1] = 0; m_mat[3][2] = 0; m_mat[3][3] = 0;
		}
		explicit mat4x4(T t)
		{
			m_mat[0][0] = t; m_mat[0][1] = t; m_mat[0][2] = t; m_mat[0][3] = t;
			m_mat[1][0] = t; m_mat[1][1] = t; m_mat[1][2] = t; m_mat[1][3] = t;
			m_mat[2][0] = t; m_mat[2][1] = t; m_mat[2][2] = t; m_mat[2][3] = t;
			m_mat[3][0] = t; m_mat[3][1] = t; m_mat[3][2] = t; m_mat[3][3] = t;
		}
		explicit mat4x4(const T* const m)
		{
			m_mat[0][0] = m[0]; m_mat[0][1] = m[1]; m_mat[0][2] = m[2]; m_mat[0][3] = m[3];
			m_mat[1][0] = m[4]; m_mat[1][1] = m[5]; m_mat[1][2] = m[6]; m_mat[1][3] = m[7];
			m_mat[2][0] = m[8]; m_mat[2][1] = m[9]; m_mat[2][2] = m[10]; m_mat[2][3] = m[11];
			m_mat[3][0] = m[12]; m_mat[3][1] = m[13]; m_mat[3][2] = m[14]; m_mat[3][3] = m[15];
		}
		explicit mat4x4(
			T _00, T _01, T _02, T _03,
			T _10, T _11, T _12, T _13,
			T _20, T _21, T _22, T _23,
			T _30, T _31, T _32, T _33)
		{
			m_mat[0][0] = _00; m_mat[0][1] = _01; m_mat[0][2] = _02; m_mat[0][3] = _03;
			m_mat[1][0] = _10; m_mat[1][1] = _11; m_mat[1][2] = _12; m_mat[1][3] = _13;
			m_mat[2][0] = _20; m_mat[2][1] = _21; m_mat[2][2] = _22; m_mat[2][3] = _23;
			m_mat[3][0] = _30; m_mat[3][1] = _31; m_mat[3][2] = _32; m_mat[3][3] = _33;
		}
		explicit mat4x4(const mat2x2<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = 0; m_mat[0][3] = 0;
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = 0; m_mat[1][3] = 0;
			m_mat[2][0] = 0; m_mat[2][1] = 0; m_mat[2][2] = 1; m_mat[2][3] = 0;
			m_mat[3][0] = 0; m_mat[3][1] = 0; m_mat[3][2] = 0; m_mat[3][3] = 1;
		}
		explicit mat4x4(const mat3x3<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2); m_mat[0][3] = 0;
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2); m_mat[1][3] = 0;
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2); m_mat[2][3] = 0;
			m_mat[3][0] = 0; m_mat[3][1] = 0; m_mat[3][2] = 0; m_mat[3][3] = 1;
		}
		mat4x4(const mat4x4<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2); m_mat[0][3] = m(0, 3);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2); m_mat[1][3] = m(1, 3);
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2); m_mat[2][3] = m(2, 3);
			m_mat[3][0] = m(3, 0); m_mat[3][1] = m(3, 1); m_mat[3][2] = m(3, 2); m_mat[3][3] = m(3, 3);
		}
		mat4x4(mat4x4<T>&& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2); m_mat[0][3] = m(0, 3);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2); m_mat[1][3] = m(1, 3);
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2); m_mat[2][3] = m(2, 3);
			m_mat[3][0] = m(3, 0); m_mat[3][1] = m(3, 1); m_mat[3][2] = m(3, 2); m_mat[3][3] = m(3, 3);
		}
		static mat4x4<T> Identity()
		{
			return mat4x4<T>(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> Scaling(T x, T y, T z)
		{
			return mat4x4<T>(
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> Scaling(vec3<T> s)
		{
			return mat4x4<T>(
				s.x, 0, 0, 0,
				0, s.y, 0, 0,
				0, 0, s.z, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> Translation(T x, T y, T z)
		{
			return mat4x4<T>(
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1);
		}
		static mat4x4<T> Translation(vec3<T> t)
		{
			return mat4x4<T>(
				1, 0, 0, t.x,
				0, 1, 0, t.y,
				0, 0, 1, t.z,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationX(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat4x4<T>(
				1, 0, 0, 0,
				0, ca, -sa, 0,
				0, sa, ca, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationY(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat4x4<T>(
				ca, 0, sa, 0,
				0, 1, 0, 0,
				-sa, 0, ca, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationZ(T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat4x4<T>(
				ca, -sa, 0, 0,
				sa, ca, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> Rotation(T pitch, T yaw, T roll)
		{
			T cp = cos(pitch), sp = sin(pitch), cy = cos(yaw), sy = sin(yaw), cr = cos(roll), sr = sin(roll);
			return mat4x4<T>(
				sy * sp * sr + cy * cr, sy * sp * cr - cy * sr, sy * cp, 0,
				cp * sr, cp * cr, -sp, 0,
				cy * sp * sr - sy * cr, cy * sp * cr + sy * sr, cy * cp, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> Rotation(vec3<T> r)
		{
			T cp = cos(r.x), sp = sin(r.x), cy = cos(r.y), sy = sin(r.y), cr = cos(r.z), sr = sin(r.z);
			return mat4x4<T>(
				sy * sp * sr + cy * cr, sy * sp * cr - cy * sr, sy * cp, 0,
				cp * sr, cp * cr, -sp, 0,
				cy * sp * sr - sy * cr, cy * sp * cr + sy * sr, cy * cp, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationAxis(vec3<T> axis, T a)
		{
			return RotationNormal(axis.Normalized(), a);
		}
		static mat4x4<T> RotationNormal(vec3<T> n, T a)
		{
			T ca = cos(a), sa = sin(a);
			return mat4x4<T>(
				ca + n.x * n.x * (1 - ca), n.x * n.y * (1 - ca) - n.z * sa, n.x * n.z * (1 - ca) + n.y * sa, 0,
				n.y * n.x * (1 - ca) + n.z * sa, ca + n.y * n.y * (1 - ca), n.y * n.z * (1 - ca) - n.x * sa, 0,
				n.z * n.x * (1 - ca) - n.y * sa, n.z * n.y * (1 - ca) + n.x * sa, ca + n.z * n.z * (1 - ca), 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationCamera(T px, T py, T pz, T rx, T ry, T rz)
		{
			mat3x3<T> m = mat3x3<T>::RotationCamera(rx, ry, rz);
			vec3<T> v = m * vec3<T>(px, py, pz);
			return mat4x4<T>(
				m(0, 0), m(0, 1), m(0, 2), -v.x,
				m(1, 0), m(1, 1), m(1, 2), -v.y,
				m(2, 0), m(2, 1), m(2, 2), -v.z,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationCamera(vec3<T> p, vec3<T> r)
		{
			mat3x3<T> m = mat3x3<T>::RotationCamera(r);
			vec3<T> v = m * p;
			return mat4x4<T>(
				m(0, 0), m(0, 1), m(0, 2), -v.x,
				m(1, 0), m(1, 1), m(1, 2), -v.y,
				m(2, 0), m(2, 1), m(2, 2), -v.z,
				0, 0, 0, 1);
		}
		static mat4x4<T> ScalingRotationTranslation(
			T sx, T sy, T sz,
			T pitch, T yaw, T roll,
			T tx, T ty, T tz)
		{
			T cpitch = cos(pitch), spitch = sin(pitch), cyaw = cos(yaw), syaw = sin(yaw), croll = cos(roll), sroll = sin(roll);
			return mat4x4<T>(
				(syaw * spitch * sroll + cyaw * croll) * sx, (syaw * spitch * croll - cyaw * sroll) * sy, (syaw * cpitch) * sz, tx,
				(cpitch * sroll) * sx, (cpitch * croll) * sy, (-spitch) * sz, ty,
				(cyaw * spitch * sroll - syaw * croll) * sx, (cyaw * spitch * croll + syaw * sroll) * sy, (cyaw * cpitch) * sz, tz,
				0, 0, 0, 1);
		}
		static mat4x4<T> ScalingRotationTranslation(vec3<T> s, vec3<T> r, vec3<T> t)
		{
			T cpitch = cos(r.x), spitch = sin(r.x), cyaw = cos(r.y), syaw = sin(r.y), croll = cos(r.z), sroll = sin(r.z);
			return mat4x4<T>(
				(syaw * spitch * sroll + cyaw * croll) * s.x, (syaw * spitch * croll - cyaw * sroll) * s.y, (syaw * cpitch) * s.z, t.x,
				(cpitch * sroll) * s.x, (cpitch * croll) * s.y, (-spitch) * s.z, t.y,
				(cyaw * spitch * sroll - syaw * croll) * s.x, (cyaw * spitch * croll + syaw * sroll) * s.y, (cyaw * cpitch) * s.z, t.z,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationTranslation(
			T pitch, T yaw, T roll,
			T tx, T ty, T tz)
		{
			T cpitch = cos(pitch), spitch = sin(pitch), cyaw = cos(yaw), syaw = sin(yaw), croll = cos(roll), sroll = sin(roll);
			return mat4x4<T>(
				(syaw * spitch * sroll + cyaw * croll), (syaw * spitch * croll - cyaw * sroll), (syaw * cpitch), tx,
				(cpitch * sroll), (cpitch * croll), (-spitch), ty,
				(cyaw * spitch * sroll - syaw * croll), (cyaw * spitch * croll + syaw * sroll), (cyaw * cpitch), tz,
				0, 0, 0, 1);
		}
		static mat4x4<T> RotationTranslation(vec3<T> r, vec3<T> t)
		{
			T cpitch = cos(r.x), spitch = sin(r.x), cyaw = cos(r.y), syaw = sin(r.y), croll = cos(r.z), sroll = sin(r.z);
			return mat4x4<T>(
				(syaw * spitch * sroll + cyaw * croll), (syaw * spitch * croll - cyaw * sroll), (syaw * cpitch), t.x,
				(cpitch * sroll), (cpitch * croll), (-spitch), t.y,
				(cyaw * spitch * sroll - syaw * croll), (cyaw * spitch * croll + syaw * sroll), (cyaw * cpitch), t.z,
				0, 0, 0, 1);
		}
		static mat4x4<T> ScalingTranslation(
			T sx, T sy, T sz,
			T tx, T ty, T tz)
		{
			return mat4x4<T>(
				sx, 0, 0, tx,
				0, sy, 0, ty,
				0, 0, sz, tz,
				0, 0, 0, 1);
		}
		static mat4x4<T> ScalingTranslation(vec3<T> s, vec3<T> t)
		{
			return mat4x4<T>(
				s.x, 0, 0, t.x,
				0, s.y, 0, t.y,
				0, 0, s.z, t.z,
				0, 0, 0, 1);
		}
		static mat4x4<T> ScalingRotation(
			T sx, T sy, T sz,
			T pitch, T yaw, T roll)
		{
			T cpitch = cos(pitch), spitch = sin(pitch), cyaw = cos(yaw), syaw = sin(yaw), croll = cos(roll), sroll = sin(roll);
			return mat4x4<T>(
				(syaw * spitch * sroll + cyaw * croll) * sx, (syaw * spitch * croll - cyaw * sroll) * sy, (syaw * cpitch) * sz, 0,
				(cpitch * sroll) * sx, (cpitch * croll) * sy, (-spitch) * sz, 0,
				(cyaw * spitch * sroll - syaw * croll) * sx, (cyaw * spitch * croll + syaw * sroll) * sy, (cyaw * cpitch) * sz, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> ScalingRotation(vec3<T> s, vec3<T> r)
		{
			T cpitch = cos(r.x), spitch = sin(r.x), cyaw = cos(r.y), syaw = sin(r.y), croll = cos(r.z), sroll = sin(r.z);
			return mat4x4<T>(
				(syaw * spitch * sroll + cyaw * croll) * s.x, (syaw * spitch * croll - cyaw * sroll) * s.y, (syaw * cpitch) * s.z, 0,
				(cpitch * sroll) * s.x, (cpitch * croll) * s.y, (-spitch) * s.z, 0,
				(cyaw * spitch * sroll - syaw * croll) * s.x, (cyaw * spitch * croll + syaw * sroll) * s.y, (cyaw * cpitch) * s.z, 0,
				0, 0, 0, 1);
		}
		static mat4x4<T> PerspectiveFOV(T fov, T screenAspect, T screenNear, T screenDepth)
		{
			T yScale = 1 / tan(fov / 2);
			T xScale = yScale / screenAspect;
			return mat4x4<T>(
				xScale, 0, 0, 0,
				0, yScale, 0, 0,
				0, 0, screenDepth / (screenDepth - screenNear), -screenDepth * screenNear / (screenDepth - screenNear),
				0, 0, 1, 0);
		}
		static mat4x4<T> Orthographic(T viewWidth, T viewHeight, T screenNear, T screenDepth)
		{
			return mat4x4<T>(
				2 / viewWidth, 0, 0, 0,
				0, 2 / viewHeight, 0, 0,
				0, 0, 1 / (screenDepth - screenNear), -screenNear / (screenDepth - screenNear),
				0, 0, 0, 1);
		}
		static mat4x4<T> LookTo(vec3<T> eye, vec3<T> direction, vec3<T> up)
		{
			vec3<T> zaxis = direction.Normalized();
			vec3<T> xaxis = up.Cross(zaxis).Normalized();
			vec3<T> yaxis = zaxis.Cross(xaxis);
			return mat4x4<T>(
				xaxis.x, xaxis.y, xaxis.z, -xaxis.Dot(eye),
				yaxis.x, yaxis.y, yaxis.z, -yaxis.Dot(eye),
				zaxis.x, zaxis.y, zaxis.z, -zaxis.Dot(eye),
				0, 0, 0, 1);
		}
		static mat4x4<T> LookAt(vec3<T> eye, vec3<T> focus, vec3<T> up)
		{
			return LookTo(eye, focus - eye, up);
		}

		T operator()(int row, int column) const { return m_mat[row][column]; }
		T& operator()(int row, int column) { return m_mat[row][column]; }
		vec4<T> operator*(vec4<T> v) const
		{
			return vec4<T>(
				m_mat[0][0] * v.x + m_mat[0][1] * v.y + m_mat[0][2] * v.z + m_mat[0][3] * v.w,
				m_mat[1][0] * v.x + m_mat[1][1] * v.y + m_mat[1][2] * v.z + m_mat[1][3] * v.w,
				m_mat[2][0] * v.x + m_mat[2][1] * v.y + m_mat[2][2] * v.z + m_mat[2][3] * v.w,
				m_mat[3][0] * v.x + m_mat[3][1] * v.y + m_mat[3][2] * v.z + m_mat[3][3] * v.w);
		}
		explicit operator mat2x2<T>() const
		{
			return mat2x2<T>(
				m_mat[0][0], m_mat[0][1],
				m_mat[1][0], m_mat[1][1]);
		}
		explicit operator mat3x3<T>() const
		{
			return mat3x3<T>(
				m_mat[0][0], m_mat[0][1], m_mat[0][2],
				m_mat[1][0], m_mat[1][1], m_mat[1][2],
				m_mat[2][0], m_mat[2][1], m_mat[2][2]);
		}
		T Determinant() const
		{
			return
				mat3x3<T>(m_mat[1][1], m_mat[1][2], m_mat[1][3], m_mat[2][1], m_mat[2][2], m_mat[2][3], m_mat[3][1], m_mat[3][2], m_mat[3][3]).Determinant() * m_mat[0][0] -
				mat3x3<T>(m_mat[0][1], m_mat[0][2], m_mat[0][3], m_mat[2][1], m_mat[2][2], m_mat[2][3], m_mat[3][1], m_mat[3][2], m_mat[3][3]).Determinant() * m_mat[1][0] +
				mat3x3<T>(m_mat[0][1], m_mat[0][2], m_mat[0][3], m_mat[1][1], m_mat[1][2], m_mat[1][3], m_mat[3][1], m_mat[3][2], m_mat[3][3]).Determinant() * m_mat[2][0] -
				mat3x3<T>(m_mat[0][1], m_mat[0][2], m_mat[0][3], m_mat[1][1], m_mat[1][2], m_mat[1][3], m_mat[2][1], m_mat[2][2], m_mat[2][3]).Determinant() * m_mat[3][0];
		}
		void Invert() { *this = Inverse(); }
		mat4x4<T> Inverse() const
		{
			T det = Determinant();
			return mat4x4(
				mat3x3<T>(m_mat[1][1], m_mat[1][2], m_mat[1][3], m_mat[2][1], m_mat[2][2], m_mat[2][3], m_mat[3][1], m_mat[3][2], m_mat[3][3]).Determinant() / det,
				mat3x3<T>(m_mat[0][1], m_mat[0][2], m_mat[0][3], m_mat[2][1], m_mat[2][2], m_mat[2][3], m_mat[3][1], m_mat[3][2], m_mat[3][3]).Determinant() / -det,
				mat3x3<T>(m_mat[0][1], m_mat[0][2], m_mat[0][3], m_mat[1][1], m_mat[1][2], m_mat[1][3], m_mat[3][1], m_mat[3][2], m_mat[3][3]).Determinant() / det,
				mat3x3<T>(m_mat[0][1], m_mat[0][2], m_mat[0][3], m_mat[1][1], m_mat[1][2], m_mat[1][3], m_mat[2][1], m_mat[2][2], m_mat[2][3]).Determinant() / -det,

				mat3x3<T>(m_mat[1][0], m_mat[1][2], m_mat[1][3], m_mat[2][0], m_mat[2][2], m_mat[2][3], m_mat[3][0], m_mat[3][2], m_mat[3][3]).Determinant() / -det,
				mat3x3<T>(m_mat[0][0], m_mat[0][2], m_mat[0][3], m_mat[2][0], m_mat[2][2], m_mat[2][3], m_mat[3][0], m_mat[3][2], m_mat[3][3]).Determinant() / det,
				mat3x3<T>(m_mat[0][0], m_mat[0][2], m_mat[0][3], m_mat[1][0], m_mat[1][2], m_mat[1][3], m_mat[3][0], m_mat[3][2], m_mat[3][3]).Determinant() / -det,
				mat3x3<T>(m_mat[0][0], m_mat[0][2], m_mat[0][3], m_mat[1][0], m_mat[1][2], m_mat[1][3], m_mat[2][0], m_mat[2][2], m_mat[2][3]).Determinant() / det,

				mat3x3<T>(m_mat[1][0], m_mat[1][1], m_mat[1][3], m_mat[2][0], m_mat[2][1], m_mat[2][3], m_mat[3][0], m_mat[3][1], m_mat[3][3]).Determinant() / det,
				mat3x3<T>(m_mat[0][0], m_mat[0][1], m_mat[0][3], m_mat[2][0], m_mat[2][1], m_mat[2][3], m_mat[3][0], m_mat[3][1], m_mat[3][3]).Determinant() / -det,
				mat3x3<T>(m_mat[0][0], m_mat[0][1], m_mat[0][3], m_mat[1][0], m_mat[1][1], m_mat[1][3], m_mat[3][0], m_mat[3][1], m_mat[3][3]).Determinant() / det,
				mat3x3<T>(m_mat[0][0], m_mat[0][1], m_mat[0][3], m_mat[1][0], m_mat[1][1], m_mat[1][3], m_mat[2][0], m_mat[2][1], m_mat[2][3]).Determinant() / -det,

				mat3x3<T>(m_mat[1][0], m_mat[1][1], m_mat[1][2], m_mat[2][0], m_mat[2][1], m_mat[2][2], m_mat[3][0], m_mat[3][1], m_mat[3][2]).Determinant() / -det,
				mat3x3<T>(m_mat[0][0], m_mat[0][1], m_mat[0][2], m_mat[2][0], m_mat[2][1], m_mat[2][2], m_mat[3][0], m_mat[3][1], m_mat[3][2]).Determinant() / det,
				mat3x3<T>(m_mat[0][0], m_mat[0][1], m_mat[0][2], m_mat[1][0], m_mat[1][1], m_mat[1][2], m_mat[3][0], m_mat[3][1], m_mat[3][2]).Determinant() / -det,
				mat3x3<T>(m_mat[0][0], m_mat[0][1], m_mat[0][2], m_mat[1][0], m_mat[1][1], m_mat[1][2], m_mat[2][0], m_mat[2][1], m_mat[2][2]).Determinant() / det);
		}
		void Transpose()
		{
			T tmp;
			tmp = m_mat[0][1]; m_mat[0][1] = m_mat[1][0]; m_mat[1][0] = tmp;
			tmp = m_mat[0][2]; m_mat[0][2] = m_mat[2][0]; m_mat[2][0] = tmp;
			tmp = m_mat[0][3]; m_mat[0][3] = m_mat[3][0]; m_mat[3][0] = tmp;
			tmp = m_mat[1][2]; m_mat[1][2] = m_mat[2][1]; m_mat[2][1] = tmp;
			tmp = m_mat[1][3]; m_mat[1][3] = m_mat[3][1]; m_mat[3][1] = tmp;
			tmp = m_mat[2][3]; m_mat[2][3] = m_mat[3][2]; m_mat[3][2] = tmp;
		}
		mat4x4<T> Transposed() const
		{
			return mat4x4<T>(
				m_mat[0][0], m_mat[1][0], m_mat[2][0], m_mat[3][0],
				m_mat[0][1], m_mat[1][1], m_mat[2][1], m_mat[3][1],
				m_mat[0][2], m_mat[1][2], m_mat[2][2], m_mat[3][2],
				m_mat[0][3], m_mat[1][3], m_mat[2][3], m_mat[3][3]);
		}
		mat4x4<T> operator*(const mat4x4<T>& m) const
		{
			return mat4x4<T>(
				m_mat[0][0] * m(0, 0) + m_mat[0][1] * m(1, 0) + m_mat[0][2] * m(2, 0) + m_mat[0][3] * m(3, 0),
				m_mat[0][0] * m(0, 1) + m_mat[0][1] * m(1, 1) + m_mat[0][2] * m(2, 1) + m_mat[0][3] * m(3, 1),
				m_mat[0][0] * m(0, 2) + m_mat[0][1] * m(1, 2) + m_mat[0][2] * m(2, 2) + m_mat[0][3] * m(3, 2),
				m_mat[0][0] * m(0, 3) + m_mat[0][1] * m(1, 3) + m_mat[0][2] * m(2, 3) + m_mat[0][3] * m(3, 3),
				m_mat[1][0] * m(0, 0) + m_mat[1][1] * m(1, 0) + m_mat[1][2] * m(2, 0) + m_mat[1][3] * m(3, 0),
				m_mat[1][0] * m(0, 1) + m_mat[1][1] * m(1, 1) + m_mat[1][2] * m(2, 1) + m_mat[1][3] * m(3, 1),
				m_mat[1][0] * m(0, 2) + m_mat[1][1] * m(1, 2) + m_mat[1][2] * m(2, 2) + m_mat[1][3] * m(3, 2),
				m_mat[1][0] * m(0, 3) + m_mat[1][1] * m(1, 3) + m_mat[1][2] * m(2, 3) + m_mat[1][3] * m(3, 3),
				m_mat[2][0] * m(0, 0) + m_mat[2][1] * m(1, 0) + m_mat[2][2] * m(2, 0) + m_mat[2][3] * m(3, 0),
				m_mat[2][0] * m(0, 1) + m_mat[2][1] * m(1, 1) + m_mat[2][2] * m(2, 1) + m_mat[2][3] * m(3, 1),
				m_mat[2][0] * m(0, 2) + m_mat[2][1] * m(1, 2) + m_mat[2][2] * m(2, 2) + m_mat[2][3] * m(3, 2),
				m_mat[2][0] * m(0, 3) + m_mat[2][1] * m(1, 3) + m_mat[2][2] * m(2, 3) + m_mat[2][3] * m(3, 3),
				m_mat[3][0] * m(0, 0) + m_mat[3][1] * m(1, 0) + m_mat[3][2] * m(2, 0) + m_mat[3][3] * m(3, 0),
				m_mat[3][0] * m(0, 1) + m_mat[3][1] * m(1, 1) + m_mat[3][2] * m(2, 1) + m_mat[3][3] * m(3, 1),
				m_mat[3][0] * m(0, 2) + m_mat[3][1] * m(1, 2) + m_mat[3][2] * m(2, 2) + m_mat[3][3] * m(3, 2),
				m_mat[3][0] * m(0, 3) + m_mat[3][1] * m(1, 3) + m_mat[3][2] * m(2, 3) + m_mat[3][3] * m(3, 3));
		}
		mat4x4<T> operator+(const mat4x4<T>& m) const
		{
			return mat4x4<T>(
				m_mat[0][0] + m(0, 0), m_mat[0][1] + m(0, 1), m_mat[0][2] + m(0, 2), m_mat[0][3] + m(0, 3),
				m_mat[1][0] + m(1, 0), m_mat[1][1] + m(1, 1), m_mat[1][2] + m(1, 2), m_mat[1][3] + m(1, 3),
				m_mat[2][0] + m(2, 0), m_mat[2][1] + m(2, 1), m_mat[2][2] + m(2, 2), m_mat[2][3] + m(2, 3),
				m_mat[3][0] + m(3, 0), m_mat[3][1] + m(3, 1), m_mat[3][2] + m(3, 2), m_mat[3][3] + m(3, 3));
		}
		mat4x4<T>& operator+=(const mat4x4<T>& m)
		{
			m_mat[0][0] += m(0, 0); m_mat[0][1] += m(0, 1); m_mat[0][2] += m(0, 2);	   m_mat[0][3] += m(0, 3);
			m_mat[1][0] += m(1, 0); m_mat[1][1] += m(1, 1); m_mat[1][2] += m(1, 2);	   m_mat[1][3] += m(1, 3);
			m_mat[2][0] += m(2, 0); m_mat[2][1] += m(2, 1); m_mat[2][2] += m(2, 2);	   m_mat[2][3] += m(2, 3);
			m_mat[3][0] += m(3, 0); m_mat[3][1] += m(3, 1); m_mat[3][2] += m(3, 2);	   m_mat[3][3] += m(3, 3);
			return *this;
		}
		mat4x4<T> operator-(const mat4x4<T>& m) const
		{
			return mat4x4<T>(
				m_mat[0][0] - m(0, 0), m_mat[0][1] - m(0, 1), m_mat[0][2] - m(0, 2), m_mat[0][3] - m(0, 3),
				m_mat[1][0] - m(1, 0), m_mat[1][1] - m(1, 1), m_mat[1][2] - m(1, 2), m_mat[1][3] - m(1, 3),
				m_mat[2][0] - m(2, 0), m_mat[2][1] - m(2, 1), m_mat[2][2] - m(2, 2), m_mat[2][3] - m(2, 3),
				m_mat[3][0] - m(3, 0), m_mat[3][1] - m(3, 1), m_mat[3][2] - m(3, 2), m_mat[3][3] - m(3, 3));
		}
		mat4x4<T>& operator-=(const mat4x4<T>& m)
		{
			m_mat[0][0] -= m(0, 0); m_mat[0][1] -= m(0, 1); m_mat[0][2] -= m(0, 2); m_mat[0][3] -= m(0, 3);
			m_mat[1][0] -= m(1, 0); m_mat[1][1] -= m(1, 1); m_mat[1][2] -= m(1, 2); m_mat[1][3] -= m(1, 3);
			m_mat[2][0] -= m(2, 0); m_mat[2][1] -= m(2, 1); m_mat[2][2] -= m(2, 2); m_mat[2][3] -= m(2, 3);
			m_mat[3][0] -= m(3, 0); m_mat[3][1] -= m(3, 1); m_mat[3][2] -= m(3, 2); m_mat[3][3] -= m(3, 3);
			return *this;
		}
		mat4x4<T>& operator=(const mat4x4<T>& m)
		{
			m_mat[0][0] = m(0, 0); m_mat[0][1] = m(0, 1); m_mat[0][2] = m(0, 2); m_mat[0][3] = m(0, 3);
			m_mat[1][0] = m(1, 0); m_mat[1][1] = m(1, 1); m_mat[1][2] = m(1, 2); m_mat[1][3] = m(1, 3);
			m_mat[2][0] = m(2, 0); m_mat[2][1] = m(2, 1); m_mat[2][2] = m(2, 2); m_mat[2][3] = m(2, 3);
			m_mat[3][0] = m(3, 0); m_mat[3][1] = m(3, 1); m_mat[3][2] = m(3, 2); m_mat[3][3] = m(3, 3);
			return *this;
		}
		mat4x4<T> operator+(T t) const
		{
			return mat4x4<T>(
				m_mat[0][0] + t, m_mat[0][1] + t, m_mat[0][2] + t, m_mat[0][3] + t,
				m_mat[1][0] + t, m_mat[1][1] + t, m_mat[1][2] + t, m_mat[1][3] + t,
				m_mat[2][0] + t, m_mat[2][1] + t, m_mat[2][2] + t, m_mat[2][3] + t,
				m_mat[3][0] + t, m_mat[3][1] + t, m_mat[3][2] + t, m_mat[3][3] + t);
		}
		mat4x4<T>& operator+=(const T t)
		{
			m_mat[0][0] += t; m_mat[0][1] += t; m_mat[0][2] += t; m_mat[0][3] += t;
			m_mat[1][0] += t; m_mat[1][1] += t; m_mat[1][2] += t; m_mat[1][3] += t;
			m_mat[2][0] += t; m_mat[2][1] += t; m_mat[2][2] += t; m_mat[2][3] += t;
			m_mat[3][0] += t; m_mat[3][1] += t; m_mat[3][2] += t; m_mat[3][3] += t;
			return *this;
		}
		mat4x4<T> operator-(T t) const
		{
			return mat4x4<T>(
				m_mat[0][0] - t, m_mat[0][1] - t, m_mat[0][2] - t, m_mat[0][3] - t,
				m_mat[1][0] - t, m_mat[1][1] - t, m_mat[1][2] - t, m_mat[1][3] - t,
				m_mat[2][0] - t, m_mat[2][1] - t, m_mat[2][2] - t, m_mat[2][3] - t,
				m_mat[3][0] - t, m_mat[3][1] - t, m_mat[3][2] - t, m_mat[3][3] - t);
		}
		mat4x4<T>& operator-=(T t)
		{
			m_mat[0][0] -= t; m_mat[0][1] -= t; m_mat[0][2] -= t; m_mat[0][3] -= t;
			m_mat[1][0] -= t; m_mat[1][1] -= t; m_mat[1][2] -= t; m_mat[1][3] -= t;
			m_mat[2][0] -= t; m_mat[2][1] -= t; m_mat[2][2] -= t; m_mat[2][3] -= t;
			m_mat[3][0] -= t; m_mat[3][1] -= t; m_mat[3][2] -= t; m_mat[3][3] -= t;
			return *this;
		}
		mat4x4<T> operator*(T t) const
		{
			return mat3x3<T>(
				m_mat[0][0] * t, m_mat[0][1] * t, m_mat[0][2] * t, m_mat[0][3] * t,
				m_mat[1][0] * t, m_mat[1][1] * t, m_mat[1][2] * t, m_mat[1][3] * t,
				m_mat[2][0] * t, m_mat[2][1] * t, m_mat[2][2] * t, m_mat[2][3] * t,
				m_mat[3][0] * t, m_mat[3][1] * t, m_mat[3][2] * t, m_mat[3][3] * t);
		}
		mat4x4<T>& operator*=(T t)
		{
			m_mat[0][0] *= t; m_mat[0][1] *= t; m_mat[0][2] *= t; m_mat[0][3] *= t;
			m_mat[1][0] *= t; m_mat[1][1] *= t; m_mat[1][2] *= t; m_mat[1][3] *= t;
			m_mat[2][0] *= t; m_mat[2][1] *= t; m_mat[2][2] *= t; m_mat[2][3] *= t;
			m_mat[3][0] *= t; m_mat[3][1] *= t; m_mat[3][2] *= t; m_mat[3][3] *= t;
			return *this;
		}
		mat4x4<T> operator/(T t) const
		{
			return mat4x4<T>(
				m_mat[0][0] / t, m_mat[0][1] / t, m_mat[0][2] / t, m_mat[0][3] / t,
				m_mat[1][0] / t, m_mat[1][1] / t, m_mat[1][2] / t, m_mat[1][3] / t,
				m_mat[2][0] / t, m_mat[2][1] / t, m_mat[2][2] / t, m_mat[2][3] / t,
				m_mat[3][0] / t, m_mat[3][1] / t, m_mat[3][2] / t, m_mat[3][3] / t);
		}
		mat4x4<T>& operator/=(T t)
		{
			m_mat[0][0] /= t; m_mat[0][1] /= t; m_mat[0][2] /= t; m_mat[0][3] /= t;
			m_mat[1][0] /= t; m_mat[1][1] /= t; m_mat[1][2] /= t; m_mat[1][3] /= t;
			m_mat[2][0] /= t; m_mat[2][1] /= t; m_mat[2][2] /= t; m_mat[2][3] /= t;
			m_mat[3][0] /= t; m_mat[3][1] /= t; m_mat[3][2] /= t; m_mat[3][3] /= t;
			return *this;
		}
		mat4x4<T>& operator=(T t)
		{
			m_mat[0][0] = t; m_mat[0][1] = t; m_mat[0][2] = t; m_mat[0][3] = t;
			m_mat[1][0] = t; m_mat[1][1] = t; m_mat[1][2] = t; m_mat[1][3] = t;
			m_mat[2][0] = t; m_mat[2][1] = t; m_mat[2][2] = t; m_mat[2][3] = t;
			m_mat[3][0] = t; m_mat[3][1] = t; m_mat[3][2] = t; m_mat[3][3] = t;
			return *this;
		}
		mat4x4<T> operator-() const
		{
			return mat4x4<T>(
				-m_mat[0][0], -m_mat[0][1], -m_mat[0][2], -m_mat[0][3],
				-m_mat[1][0], -m_mat[1][1], -m_mat[1][2], -m_mat[1][3],
				-m_mat[2][0], -m_mat[2][1], -m_mat[2][2], -m_mat[2][3],
				-m_mat[3][0], -m_mat[3][1], -m_mat[3][2], -m_mat[3][3]);
		}
		bool operator==(const mat4x4<T>& m) const
		{
			return
				m_mat[0][0] == m(0, 0) && m_mat[0][1] == m(0, 1) && m_mat[0][2] == m(0, 2) && m_mat[0][3] == m(0, 3) &&
				m_mat[1][0] == m(1, 0) && m_mat[1][1] == m(1, 1) && m_mat[1][2] == m(1, 2) && m_mat[1][3] == m(1, 3) &&
				m_mat[2][0] == m(2, 0) && m_mat[2][1] == m(2, 1) && m_mat[2][2] == m(2, 2) && m_mat[2][3] == m(2, 3) &&
				m_mat[3][0] == m(3, 0) && m_mat[3][1] == m(3, 1) && m_mat[3][2] == m(3, 2) && m_mat[3][3] == m(3, 3);
		}
		bool operator!=(const mat4x4<T>& m) const
		{
			return
				m_mat[0][0] != m(0, 0) || m_mat[0][1] != m(0, 1) || m_mat[0][2] != m(0, 2) || m_mat[0][3] != m(0, 3) ||
				m_mat[1][0] != m(1, 0) || m_mat[1][1] != m(1, 1) || m_mat[1][2] != m(1, 2) || m_mat[1][3] != m(1, 3) ||
				m_mat[2][0] != m(2, 0) || m_mat[2][1] != m(2, 1) || m_mat[2][2] != m(2, 2) || m_mat[2][3] != m(2, 3) ||
				m_mat[3][0] != m(3, 0) || m_mat[3][1] != m(3, 1) || m_mat[3][2] != m(3, 2) || m_mat[3][3] != m(3, 3);
		}
		bool isNear(const mat4x4<T>& m, T eps = EPS) const
		{
			return
				mth::isNear(m_mat[0][0], m(0, 0), eps) && mth::isNear(m_mat[0][1], m(0, 1), eps) && mth::isNear(m_mat[0][2], m(0, 2), eps) && mth::isNear(m_mat[0][3], m(0, 3), eps) &&
				mth::isNear(m_mat[1][0], m(1, 0), eps) && mth::isNear(m_mat[1][1], m(1, 1), eps) && mth::isNear(m_mat[1][2], m(1, 2), eps) && mth::isNear(m_mat[1][3], m(1, 3), eps) &&
				mth::isNear(m_mat[2][0], m(2, 0), eps) && mth::isNear(m_mat[2][1], m(2, 1), eps) && mth::isNear(m_mat[2][2], m(2, 2), eps) && mth::isNear(m_mat[2][3], m(2, 3), eps) &&
				mth::isNear(m_mat[3][0], m(3, 0), eps) && mth::isNear(m_mat[3][1], m(3, 1), eps) && mth::isNear(m_mat[3][2], m(3, 2), eps) && mth::isNear(m_mat[3][3], m(3, 3), eps);
		}
		template <typename S>
		explicit operator mat4x4<S>() const
		{
			return mat4x4<S>(
				m_mat[0][0], m_mat[0][1], m_mat[0][2], m_mat[0][3],
				m_mat[1][0], m_mat[1][1], m_mat[1][2], m_mat[1][3],
				m_mat[2][0], m_mat[2][1], m_mat[2][2], m_mat[2][3],
				m_mat[3][0], m_mat[3][1], m_mat[3][2], m_mat[3][3]);
		}
		template <typename S>
		mat4x4<S> WithType() const { return (mat4x4<S>) * this; }
	};

	template <typename T>
	mat4x4<T> operator+(T t, const mat4x4<T>& m) { return m + t; }
	template <typename T>
	mat4x4<T> operator-(T t, const mat4x4<T>& m) { return mat4x4<T>(t) - m; }
	template <typename T>
	mat4x4<T> operator*(T t, const mat4x4<T>& m) { return m * t; }
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const mat4x4<T>& m)
	{
		os <<
			m(0, 0) << ' ' << m(0, 1) << ' ' << m(0, 2) << ' ' << m(0, 3) << '\n' <<
			m(1, 0) << ' ' << m(1, 1) << ' ' << m(1, 2) << ' ' << m(1, 3) << '\n' <<
			m(2, 0) << ' ' << m(2, 1) << ' ' << m(2, 2) << ' ' << m(2, 3) << '\n' <<
			m(3, 0) << ' ' << m(3, 1) << ' ' << m(3, 2) << ' ' << m(3, 3) << '\n';
		return os;
	}
	template <typename T>
	std::istream& operator>>(std::istream& is, mat4x4<T>& m)
	{
		is >>
			m(0, 0) >> m(0, 1) >> m(0, 2) >> m(0, 3) >>
			m(1, 0) >> m(1, 1) >> m(1, 2) >> m(1, 3) >>
			m(2, 0) >> m(2, 1) >> m(2, 2) >> m(2, 3) >>
			m(3, 0) >> m(3, 1) >> m(3, 2) >> m(3, 3);
		return is;
	}

	template <typename T>
	std::wostream& operator<<(std::wostream& os, const mat4x4<T>& m)
	{
		os <<
			m(0, 0) << ' ' << m(0, 1) << ' ' << m(0, 2) << ' ' << m(0, 3) << '\n' <<
			m(1, 0) << ' ' << m(1, 1) << ' ' << m(1, 2) << ' ' << m(1, 3) << '\n' <<
			m(2, 0) << ' ' << m(2, 1) << ' ' << m(2, 2) << ' ' << m(2, 3) << '\n' <<
			m(3, 0) << ' ' << m(3, 1) << ' ' << m(3, 2) << ' ' << m(3, 3) << '\n';
		return os;
	}
	template <typename T>
	std::wistream& operator>>(std::wistream& is, mat4x4<T>& m)
	{
		is >>
			m(0, 0) >> m(0, 1) >> m(0, 2) >> m(0, 3) >>
			m(1, 0) >> m(1, 1) >> m(1, 2) >> m(1, 3) >>
			m(2, 0) >> m(2, 1) >> m(2, 2) >> m(2, 3) >>
			m(3, 0) >> m(3, 1) >> m(3, 2) >> m(3, 3);
		return is;
	}
}