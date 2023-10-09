#include "model.h"
#include <string>
#include <future>

static mth::float3 StlConvert(mth::float3 v)
{
	return mth::float3(v.y, v.z, v.x);
}

static mth::float3 ReadF3Ascii(std::ifstream& infile)
{
	mth::float3 v;
	infile >> v;
	return StlConvert(v);
}

static mth::float3 ReadF3Bin(std::ifstream& infile)
{
	mth::float3 v;
	infile.read(reinterpret_cast<char*>(&v), sizeof(v));
	return StlConvert(v);
}

bool Model::LoadText(const wchar_t* filename)
{
	std::ifstream infile(filename);
	std::vector<Vertex> vertices;
	std::string text;
	std::getline(infile, text);	// first line indicating file type

	while (!infile.eof())
	{
		infile >> text;
		if (text == "endsolid")
		{
			m_vertices = std::move(vertices);
			return true;
		}
		if (text != "facet")
			return false;
		infile >> text;
		if (text != "normal")
			return false;

		Vertex v;
		v.normal = ReadF3Ascii(infile);

		infile >> text;
		if (text != "outer")
			return false;
		infile >> text;
		if (text != "loop")
			return false;

		infile >> text;
		if (text != "vertex")
			return false;
		v.position = ReadF3Ascii(infile);
		vertices.push_back(v);

		infile >> text;
		if (text != "vertex")
			return false;
		v.position = ReadF3Ascii(infile);
		vertices.push_back(v);

		infile >> text;
		if (text != "vertex")
			return false;
		v.position = ReadF3Ascii(infile);
		vertices.push_back(v);

		infile >> text;
		if (text != "endloop")
			return false;
		infile >> text;
		if (text != "endfacet")
			return false;
	}

	return false;
}

bool Model::LoadBin(const wchar_t* filename)
{
	std::ifstream infile(filename, std::ios::binary);
	char header[80];
	infile.read(header, sizeof(header));
	unsigned faceCount = 0;
	infile.read(reinterpret_cast<char*>(&faceCount), sizeof(faceCount));

	std::vector<Vertex> vertices;
	vertices.reserve(3 * faceCount);
	for (unsigned i = 0; i < faceCount; ++i)
	{
		Vertex v;
		v.normal = ReadF3Bin(infile);
		v.position = ReadF3Bin(infile);
		vertices.push_back(v);
		v.position = ReadF3Bin(infile);
		vertices.push_back(v);
		v.position = ReadF3Bin(infile);
		vertices.push_back(v);

		if (infile.eof())
			return false;
		char attr[2];
		infile.read(attr, sizeof(attr));
	}

	m_vertices = std::move(vertices);
	return true;
}

void Model::Cube()
{
	m_vertices = std::vector<Vertex>({
		// bottom
		{ mth::float3(-1.0f, -1.0f, -1.0f), mth::float3( 0.0f, -1.0f,  0.0f) },
		{ mth::float3( 1.0f, -1.0f, -1.0f), mth::float3( 0.0f, -1.0f,  0.0f) },
		{ mth::float3( 1.0f, -1.0f,  1.0f), mth::float3( 0.0f, -1.0f,  0.0f) },
		{ mth::float3( 1.0f, -1.0f,  1.0f), mth::float3( 0.0f, -1.0f,  0.0f) },
		{ mth::float3(-1.0f, -1.0f,  1.0f), mth::float3( 0.0f, -1.0f,  0.0f) },
		{ mth::float3(-1.0f, -1.0f, -1.0f), mth::float3( 0.0f, -1.0f,  0.0f) },
		// top
		{ mth::float3( 1.0f,  1.0f, -1.0f), mth::float3( 0.0f,  1.0f,  0.0f) },
		{ mth::float3(-1.0f,  1.0f, -1.0f), mth::float3( 0.0f,  1.0f,  0.0f) },
		{ mth::float3( 1.0f,  1.0f,  1.0f), mth::float3( 0.0f,  1.0f,  0.0f) },
		{ mth::float3(-1.0f,  1.0f,  1.0f), mth::float3( 0.0f,  1.0f,  0.0f) },
		{ mth::float3( 1.0f,  1.0f,  1.0f), mth::float3( 0.0f,  1.0f,  0.0f) },
		{ mth::float3(-1.0f,  1.0f, -1.0f), mth::float3( 0.0f,  1.0f,  0.0f) },
		// left
		{ mth::float3(-1.0f,  1.0f, -1.0f), mth::float3(-1.0f,  0.0f,  0.0f) },
		{ mth::float3(-1.0f, -1.0f, -1.0f), mth::float3(-1.0f,  0.0f,  0.0f) },
		{ mth::float3(-1.0f,  1.0f,  1.0f), mth::float3(-1.0f,  0.0f,  0.0f) },
		{ mth::float3(-1.0f, -1.0f,  1.0f), mth::float3(-1.0f,  0.0f,  0.0f) },
		{ mth::float3(-1.0f,  1.0f,  1.0f), mth::float3(-1.0f,  0.0f,  0.0f) },
		{ mth::float3(-1.0f, -1.0f, -1.0f), mth::float3(-1.0f,  0.0f,  0.0f) },
		// right
		{ mth::float3( 1.0f, -1.0f, -1.0f), mth::float3( 1.0f,  0.0f,  0.0f) },
		{ mth::float3( 1.0f,  1.0f, -1.0f), mth::float3( 1.0f,  0.0f,  0.0f) },
		{ mth::float3( 1.0f,  1.0f,  1.0f), mth::float3( 1.0f,  0.0f,  0.0f) },
		{ mth::float3( 1.0f,  1.0f,  1.0f), mth::float3( 1.0f,  0.0f,  0.0f) },
		{ mth::float3( 1.0f, -1.0f,  1.0f), mth::float3( 1.0f,  0.0f,  0.0f) },
		{ mth::float3( 1.0f, -1.0f, -1.0f), mth::float3( 1.0f,  0.0f,  0.0f) },
		// front
		{ mth::float3(-1.0f, -1.0f, -1.0f), mth::float3( 0.0f,  0.0f, -1.0f) },
		{ mth::float3(-1.0f,  1.0f, -1.0f), mth::float3( 0.0f,  0.0f, -1.0f) },
		{ mth::float3( 1.0f,  1.0f, -1.0f), mth::float3( 0.0f,  0.0f, -1.0f) },
		{ mth::float3( 1.0f,  1.0f, -1.0f), mth::float3( 0.0f,  0.0f, -1.0f) },
		{ mth::float3( 1.0f, -1.0f, -1.0f), mth::float3( 0.0f,  0.0f, -1.0f) },
		{ mth::float3(-1.0f, -1.0f, -1.0f), mth::float3( 0.0f,  0.0f, -1.0f) },
		// back
		{ mth::float3(-1.0f,  1.0f,  1.0f), mth::float3( 0.0f,  0.0f,  1.0f) },
		{ mth::float3(-1.0f, -1.0f,  1.0f), mth::float3( 0.0f,  0.0f,  1.0f) },
		{ mth::float3( 1.0f,  1.0f,  1.0f), mth::float3( 0.0f,  0.0f,  1.0f) },
		{ mth::float3( 1.0f, -1.0f,  1.0f), mth::float3( 0.0f,  0.0f,  1.0f) },
		{ mth::float3( 1.0f,  1.0f,  1.0f), mth::float3( 0.0f,  0.0f,  1.0f) },
		{ mth::float3(-1.0f, -1.0f,  1.0f), mth::float3( 0.0f,  0.0f,  1.0f) }
		});

	//for (Vertex& v : m_vertices) v.position += mth::float3(10.0f, 100.0f, 300.0f);
}

bool Model::Load(const wchar_t* filename)
{
	std::ifstream infile(filename);
	if (!infile.is_open())
		return false;

	char solid[5];
	infile.read(solid, sizeof(solid));
	infile.close();
	if (0 == std::memcmp(solid, "solid", 5))
		return LoadText(filename);
	return LoadBin(filename);
}

void Model::OptimalViewing(mth::float3& center, float& distance) const
{
	if (m_vertices.empty())
	{
		center = 0.0f;
		distance = 1.0f;
	}
	else
	{
		mth::float3 minCoords = m_vertices[0].position;
		mth::float3 maxCoords = minCoords;
		for (const Vertex& v : m_vertices)
		{
			minCoords.x = std::min(minCoords.x, v.position.x);
			minCoords.y = std::min(minCoords.y, v.position.y);
			minCoords.z = std::min(minCoords.z, v.position.z);
			maxCoords.x = std::max(maxCoords.x, v.position.x);
			maxCoords.y = std::max(maxCoords.y, v.position.y);
			maxCoords.z = std::max(maxCoords.z, v.position.z);
		}
		center = (maxCoords - minCoords) * 0.5f + minCoords;
		distance = (maxCoords - minCoords).Length();
	}
}

static void CalculateTriangleSlice(std::vector<mth::float2>& outputContainer, const mth::float3x3& plainTransform, float plainDistFromOrigin, const Vertex vertices[3])
{
	mth::float3 v[] = {
		plainTransform * vertices[0].position - mth::float3(0.0f, plainDistFromOrigin, 0.0f),
		plainTransform * vertices[1].position - mth::float3(0.0f, plainDistFromOrigin, 0.0f),
		plainTransform * vertices[2].position - mth::float3(0.0f, plainDistFromOrigin, 0.0f)
	};
	for (int i = 0; i < 3; ++i)
		if (0.0f == v[i].y)
			v[i].y = std::numeric_limits<float>::min();

	if (v[0].y * v[1].y < 0.0f)
		outputContainer.push_back(mth::float2(v[0].x, v[0].z) + mth::float2(v[1].x - v[0].x, v[1].z - v[0].z) * std::abs(v[0].y / (v[1].y - v[0].y)));
	if (v[1].y * v[2].y < 0.0f)
		outputContainer.push_back(mth::float2(v[1].x, v[1].z) + mth::float2(v[2].x - v[1].x, v[2].z - v[1].z) * std::abs(v[1].y / (v[2].y - v[1].y)));
	if (v[2].y * v[0].y < 0.0f)
		outputContainer.push_back(mth::float2(v[2].x, v[2].z) + mth::float2(v[0].x - v[2].x, v[0].z - v[2].z) * std::abs(v[2].y / (v[0].y - v[2].y)));
}

std::vector<mth::float2> Model::CalcSlice(mth::float3 plainNormal, float plainDistFromOrigin) const
{
	std::vector<mth::float2> slice;
	slice.reserve(m_vertices.size() / 3 * 2);

	const mth::float3x3 plainTransform = mth::float3x3::RotateUnitVector(plainNormal, mth::float3(0.0f, 1.0f, 0.0f));

	for (std::size_t i = 0; i < m_vertices.size(); i += 3)
		CalculateTriangleSlice(slice, plainTransform, plainDistFromOrigin, m_vertices.data() + i);

	return slice;
}

std::vector<mth::float2> Model::CalcSlice(mth::float3 plainNormal, float plainDistFromOrigin, unsigned jobs) const
{
	if (jobs < 2)
		return CalcSlice(plainNormal, plainDistFromOrigin);

	class Worker
	{
		const mth::float3x3& m_plainTransform;
		const float m_plainDistFromOrigin;
		std::vector<mth::float2> m_slice;
		std::future<void> m_future;

	public:
		Worker(const mth::float3x3& plainTransform, const float plainDistFromOrigin)
			: m_plainTransform(plainTransform)
			, m_plainDistFromOrigin(plainDistFromOrigin) {}

		void Run(const Vertex* vertices, unsigned count)
		{
			m_slice.reserve(count * 2);
			m_future = std::async([this](const Vertex* vertices, unsigned count) {
				for (unsigned i = 0; i < count; ++i)
					CalculateTriangleSlice(m_slice, m_plainTransform, m_plainDistFromOrigin, &vertices[i * 3]);
				}, vertices, count);
		}

		void GetSlices(std::vector<mth::float2>& outputContainer)
		{
			m_future.wait();
			outputContainer.insert(outputContainer.end(), m_slice.begin(), m_slice.end());
		}
	};

	std::size_t jobWorkCount = (m_vertices.size() / 3 + jobs - 1) / jobs;
	const mth::float3x3 plainTransform = mth::float3x3::RotateUnitVector(plainNormal, mth::float3(0.0f, 1.0f, 0.0f));
	std::vector<Worker> workers;
	workers.reserve(jobs);

	for (unsigned i = 0; i < jobs; ++i)
	{
		const Vertex* vertices = &m_vertices[3 * i * jobWorkCount];
		unsigned count = std::min(jobWorkCount, m_vertices.size() - i * jobWorkCount);
		workers.emplace_back(plainTransform, plainDistFromOrigin).Run(vertices, count);
	}

	std::vector<mth::float2> allSlice;
	allSlice.reserve(m_vertices.size() / 3 * 2);
	for (Worker& w : workers)
		w.GetSlices(allSlice);
	return allSlice;
}
