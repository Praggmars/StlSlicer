#pragma once

#include "position.hpp"

namespace mth
{
	template <typename T>
	bool IsPointOverTriangle(const vec3<T> tri[3], vec3<T> point)
	{
		vec3<T> vecs[3] = { tri[1] - tri[0],
			tri[2] - tri[0],
			point - tri[0] };
		T dot00 = vecs[0].Dot(vecs[0]);
		T dot01 = vecs[0].Dot(vecs[1]);
		T dot02 = vecs[0].Dot(vecs[2]);
		T dot11 = vecs[1].Dot(vecs[1]);
		T dot12 = vecs[1].Dot(vecs[2]);
		T denom = dot00 * dot11 - dot01 * dot01;
		T u = (dot11 * dot02 - dot01 * dot12) / denom;
		T v = (dot00 * dot12 - dot01 * dot02) / denom;
		return u >= 0 && v >= 0.0f && u + v <= 1;
	}

	template <typename T>
	class Plain3D
	{
		vec3<T> m_normal;
		T m_distance;

	public:
		Plain3D() {}
		Plain3D(vec3<T> unitNormal, T distance) :
			m_normal(unitNormal),
			m_distance(distance) {}
		Plain3D(const vec3<T> p[3]) :Plain3D(p[0], p[1], p[2]) {}
		Plain3D(vec3<T> p1, vec3<T> p2, vec3<T> p3) :
			m_normal((p1 - p2).Cross(p1 - p3).Normalized()),
			m_distance(m_normal.Dot(p1)) {}

		inline vec3<T> Normal() const { return m_normal; }
		inline void Normal(vec3<T> unitNormal) { m_normal = unitNormal; }
		inline T Distance() const { return m_distance; }
		inline void Distance(T distance) { m_distance = distance; }

		bool IsPointOn(vec3<T> point, T eps = EPS) const
		{
			return std::abs(point.Dot(m_normal) - m_distance) < eps;
		}
		bool IsPointBelow(vec3<T> point) const
		{
			return point.Dot(m_normal) < m_distance;
		}
		bool IsPointOver(vec3<T> point) const
		{
			return point.Dot(m_normal) > m_distance;
		}
		T Distance(vec3<T> point) const
		{
			return m_normal.Dot(point) - m_distance;
		}
		T DirectionalDistance(Position<T>& ray) const
		{
			return DirectionalDistance(ray.position, ray.GetLookDirection());
		}
		T DirectionalDistance(vec3<T> raypos, vec3<T> raydir) const
		{
			T distTowardPlain = -m_normal.Dot(raydir);
			T distFromPlain = m_normal.Dot(raypos) - m_distance;
			return distFromPlain / distTowardPlain;
		}
		T TimeToGetClose(vec3<T> position, vec3<T> direction, T distance) const
		{
			T distTowardPlain = -m_normal.Dot(direction);
			T distFromPlain = m_normal.Dot(position) - m_distance;
			if (distFromPlain < 0)
				distFromPlain += distance;
			else
				distFromPlain -= distance;
			return distFromPlain / distTowardPlain;
		}
	};

	template <typename T>
	class Triangle3D
	{
		Plain3D<T> m_plain;
		vec3<T> m_vertices[3];

	public:
		Triangle3D() {}
		Triangle3D(const vec3<T> tri[3]) : Triangle3D(tri[0], tri[1], tri[2]) {}
		Triangle3D(vec3<T> v1, vec3<T> v2, vec3<T> v3) :
			m_plain(v1, v2, v3),
			m_vertices{ v1, v2, v3 }{}
		Triangle3D(vec3<T> tri[3], vec3<T> plainNormal, T plainDistance) :
			m_plain(tri[0], tri[1], tri[2]),
			m_vertices{ tri[0], tri[1], tri[2] }{}

		bool IsPointOver(vec3<T> point) const
		{
			return IsPointOverTriangle(m_vertices, point);
		}
		bool IsPointOn(vec3<T> point, T eps = EPS) const
		{
			return m_plain.IsPointOn(point, eps) && IsPointOverTriangle(m_vertices, point);
		}

		inline Plain3D<T>& Plain() { return m_plain; }
		inline vec3<T> Vertex(unsigned index) const { return m_vertices[index]; }
	};

	using Plain3Df = Plain3D<float>;
	using Plain3Dd = Plain3D<double>;
	using Triangle3Df = Triangle3D<float>;
	using Triangle3Dd = Triangle3D<double>;
}