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
	Vector3 offset;
	float dummy;
};