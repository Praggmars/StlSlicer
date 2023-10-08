#pragma once

#include "position.hpp"

namespace mth
{
	template <typename T>
	class Line2D
	{
		vec2<T> m_point;
		vec2<T> m_direction;

	public:
		Line2D() : m_point(), m_direction() {}
		Line2D(vec2<T> point, vec2<T> direction) : m_point(point), m_direction(direction) {}
		static Line2D From2Points(vec2<T> p1, vec2<T> p2) { return Line2D(p1, (p2 - p1).Normalized()); }

		T Distance(vec2<T> point) const
		{
			vec2<T> p = m_point + m_direction;
			float num = std::abs((p.y - m_point.y) * point.x - (p.x - m_point.x) * point.y + p.x * m_point.y - p.y * m_point.x);
			float den = std::sqrt((p.y - m_point.y) * (p.y - m_point.y) + (p.x - m_point.x) * (p.x - m_point.x));
			return num / den;
		}
		T DistanceSquare(vec2<T> point) const
		{
			point -= m_point;
			point -= point * point.Dot(m_direction);
			return point.LengthSquare();
		}
		vec2<T> Intersection(const Line2D& line) const
		{
			vec2<T> p1 = m_point;
			vec2<T> p2 = m_point + m_direction;
			vec2<T> q1 = line.m_point;
			vec2<T> q2 = line.m_point + line.m_direction;

			return vec2<T>(
				(p1.x * p2.y - p1.y * p2.x) * (q1.x - q2.x) - (p1.x - p2.x) * (q1.x * q2.y - q1.y * q2.x),
				(p1.x * p2.y - p1.y * p2.x) * (q1.y - q2.y) - (p1.y - p2.y) * (q1.x * q2.y - q1.y * q2.x)
				) * (static_cast<T>(1) / ((p1.x - p2.x) * (q1.y - q2.y) - (p1.y - p2.y) * (q1.x - q2.x)));
		}

		inline vec2<T> Point() const { return m_point; }
		inline vec2<T> Direction() const { return m_direction; }
		inline vec2<T> Normal() const { return vec2<T>(-m_direction.y, m_direction.x); }
	};

	template <typename T>
	class LineSection2D
	{
	public:
		vec2<T> point1;
		vec2<T> point2;

		LineSection2D() : point1(), point2() {}
		LineSection2D(vec2<T> point1, vec2<T> point2) : point1(point1), point2(point2) {}

		bool Intersects(LineSection2D& ls, vec2<T>* intersection = nullptr) const
		{
			vec2<T> s1 = point2 - point1;
			vec2<T> s2 = ls.point2 - ls.point1;

			T den = s1.x * s2.y - s2.x * s1.y;
			T s = (-s1.y * (point1.x - ls.point1.x) + s1.x * (point1.y - ls.point1.y)) / den;
			T t = (+s2.x * (point1.y - ls.point1.y) - s2.y * (point1.x - ls.point1.x)) / den;

			if (s >= 0.0f && s <= 1.0f && t >= 0.0f && t <= 1.0f)
			{
				if (intersection)
					*intersection = point1 + t * s1;
				return true;
			}
			return false;
		}
	};

	using Line2Df = Line2D<float>;
	using Line2Dd = Line2D<double>;
	using LineSection2Df = LineSection2D<float>;
	using LineSection2Dd = LineSection2D<double>;
}