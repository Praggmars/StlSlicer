#pragma once

#include <vector>

namespace mth
{
	template <typename ElementType, typename WeightType>
	struct GraphEdge
	{
		ElementType* elements[2];
		WeightType weight;
	};

	template <typename ElementType, typename WeightType>
	struct Graph
	{
		std::vector<ElementType> vertices;
		std::vector<GraphEdge<ElementType, WeightType>> edges;
	};
}