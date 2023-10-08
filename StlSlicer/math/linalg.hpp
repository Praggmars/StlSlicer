#pragma once

#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix2x2.hpp"
#include "matrix3x3.hpp"
#include "matrix4x4.hpp"

namespace mth
{
	using float2 = vec2<float>;
	using float3 = vec3<float>;
	using float4 = vec4<float>;
	using float2x2 = mat2x2<float>;
	using float3x3 = mat3x3<float>;
	using float4x4 = mat4x4<float>;

	using double2 = vec2<double>;
	using double3 = vec3<double>;
	using double4 = vec4<double>;
	using double2x2 = mat2x2<double>;
	using double3x3 = mat3x3<double>;
	using double4x4 = mat4x4<double>;

	template <typename T>
	vec3<T> Transform(const mat4x4<T>& m, vec3<T> v)
	{
		vec4<T> v4(v, 1.0f);
		return vec3<T>(m * v4);
	}
	template <typename T>
	mat3x3<T> NormalToRotationMatrix(vec3<T> n)
	{
		if (n.z == 1.0f)
			return mat3x3<T>::Identity();
		vec3<T> u1, u2, u3;
		u3 = n;
		u1 = u3.Cross(vec3<T>(0.0f, 0.0f, 1.0f));
		u2 = u1.Cross(u3);
		return mat3x3<T>(
			u1.x, u1.y, u1.z,
			u2.x, u2.y, u2.z,
			u3.x, u3.y, u3.z);
	}
}