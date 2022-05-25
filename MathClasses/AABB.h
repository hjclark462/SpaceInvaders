#pragma once
#include "Vector3.h"
#include "Matrix3.h"
#include <vector>
#include <limits>
class AABB
{
public:
	Vectr3 min = { std::numeric_limits<float>::infinity(),
					std::numeric_limits<float>::infinity(),
					std::numeric_limits<float>::infinity() };
	Vectr3 max = { -std::numeric_limits<float>::infinity(),
					-std::numeric_limits<float>::infinity(),
					-std::numeric_limits<float>::infinity() };
	AABB();
	AABB(Vectr3 min, Vectr3 max);
	Vectr3 Center();
	Vectr3 Extents();
	std::vector<Vectr3> Corners();
	void Fit(std::vector<Vectr3> points);	
	Vectr3 ClosestPoint(Vectr3 p);
	bool IsEmpty();
	void Empty();
	void SetToTransformedBox(AABB box, Matrix3 m);
};