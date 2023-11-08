#pragma once
#include "Types.h"

struct Vertex
{
	Vector3 position;
	//Color color; 
	Vector2 uv;
};

struct TransformData
{
	Matrix matWorld = Matrix::Identity;
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};