#pragma once

#include "math/position.hpp"
#include <vector>
#include <fstream>

struct Vertex
{
	mth::float3 position;
	mth::float3 normal;
};

class Model
{
	std::vector<Vertex> m_vertices;

private:
	bool LoadText(const wchar_t* filename);
	bool LoadBin(const wchar_t* filename);

public:
	void Cube();
	bool Load(const wchar_t* filename);

	void OptimalPositioning(mth::float3& offset, float& scale) const;
	std::vector<mth::float2> CalcSlice(mth::float3 plainNormal, float plainDistFromOrigin) const;
	std::vector<mth::float2> CalcSlice(mth::float3 plainNormal, float plainDistFromOrigin, unsigned jobs) const;

	inline const std::vector<Vertex>& Vertices() const { return m_vertices; }
};