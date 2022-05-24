#pragma once
#include "Vector3.h"
#include <vector>
#include <limits>
class AABB
{
public:
	Vector3 min = { std::numeric_limits<double>::infinity(),
					std::numeric_limits<double>::infinity(),
					std::numeric_limits<double>::infinity() };
	Vector3 max = { -std::numeric_limits<double>::infinity(),
					-std::numeric_limits<double>::infinity(),
					-std::numeric_limits<double>::infinity() };
	AABB();
	AABB(Vector3 min, Vector3 max);
	Vector3 Center();
	Vector3 Extents();
	std::vector<Vector3> Corners();
	void Fit(std::vector<Vector3> points);
	bool Overlaps(Vector3 p);	
	Vector3 ClosestPoint(Vector3 p);
};