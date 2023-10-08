#pragma once

#include <cmath>

namespace mth
{
	constexpr double PI = 3.1415926535897932;
	constexpr double EPS = 1e-6;
	constexpr float pi = 3.1415926535897932f;
	constexpr float eps = 1e-6f;

	template <typename T>
	bool isNear(T a, T b, T eps = EPS)
	{
		return fabs(a - b) < eps;
	}

	template <typename T>
	int Quadratic(T a, T b, T c, T& s1, T& s2)
	{
		T dis = b * b - 4 * a * c;
		if (dis < 0)
			return 0;
		if (dis == 0)
		{
			s1 = s2 = -b / (2 * a);
			return 1;
		}
		a = 0.5 / a;
		b *= a;
		dis = sqrt(dis) * a;
		s1 = -b - dis;
		s2 = -b + dis;
		return 2;
	}

	template <typename T>
	T Random(T minimum, T maximum)
	{
		return (static_cast<T>(rand()) / static_cast<T>(RAND_MAX))* (maximum - minimum) + minimum;
	}
	template <typename T>
	T Random()
	{
		return Random(0, 1);
	}
}