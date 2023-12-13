#pragma once

template <typename T>
class Geometry
{
public:
	Geometry() {};
	~Geometry() {};

	uint32 GetVertexCount() { return static_cast<uint32>(_vertexes.size()); }

	void* GetVertexData() { return _vertexes.data(); }
	const vector<T>& GetVertexes() { return _vertexes; }

	uint32 GetIndexCount() { return static_cast<uint32>(_indexes.size()); }
	void* GetIndexData() { return _indexes.data(); }
	const vector<uint32>& GetIndexes() { return _indexes; }

	void AddVertex(const T& vertex) { _vertexes.push_back(vertex); }
	void AddVertexes(const vector<T>& vertexes) { _vertexes.insert(_vertexes.end(), vertexes.begin(), vertexes.end()); }
	void SetVertexes(const vector<T>& vertexes) { _vertexes = vertexes; }

	void AddIndex(uint32 index) { _indexes.push_back(index); }
	void AddIndexes(const vector<uint32>& indexes) { _indexes.insert(_indexes.end(), indexes.begin(), indexes.end()); }
	void SetIndexes(const vector<uint32>& indexes) { _indexes = indexes; }

private:
	vector<T> _vertexes;
	vector<uint32> _indexes;
};

