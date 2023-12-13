#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateRectangle(shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	vector<VertexColorData> vertexes;
	vertexes.resize(4);
	// 1 3
	// 0 2
	vertexes[0].position = Vector3(-0.5f, -0.5f, 0.f);
	vertexes[0].color = color;
	vertexes[1].position = Vector3(-0.5f, 0.5f, 0.f);
	vertexes[1].color = color;
	vertexes[2].position = Vector3(0.5f, -0.5f, 0.f);
	vertexes[2].color = color;
	vertexes[3].position = Vector3(0.5f, 0.5f, 0.f);
	vertexes[3].color = color;
	geometry->SetVertexes(vertexes);

	vector<uint32> indexes = { 0,1,2,2,1,3 };
	geometry->SetIndexes(indexes);
}

void GeometryHelper::CreateRectangle(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	vector<VertexTextureData> vertexes;
	vertexes.resize(4);
	// 1 3
	// 0 2
	vertexes[0].position = Vector3(-0.5f, -0.5f, 0.f);
	vertexes[0].uv = Vector2(0.f, 1.f);
	vertexes[1].position = Vector3(-0.5f, 0.5f, 0.f);
	vertexes[1].uv = Vector2(0.f, 0.f);
	vertexes[2].position = Vector3(0.5f, -0.5f, 0.f);
	vertexes[2].uv = Vector2(1.f, 1.f);
	vertexes[3].position = Vector3(0.5f, 0.5f, 0.f);
	vertexes[3].uv = Vector2(1.f, 0.f);
	geometry->SetVertexes(vertexes);

	vector<uint32> indexes = { 0,1,2,2,1,3 };
	geometry->SetIndexes(indexes);
}
