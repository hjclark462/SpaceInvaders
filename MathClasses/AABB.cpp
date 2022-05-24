#include "AABB.h"
AABB::AABB()
{

}
AABB::AABB(Vector3 min, Vector3 max)
{
	this->min = min;
	this->max = max;
}
Vector3 AABB::Center()
{
	return (min + max) * 0.5f;
}
Vector3 AABB::Extents()
{
	Vector3 extents = { std::abs(max.x - min.x) * 0.5f,
					   std::abs(max.y - min.y) * 0.5f,
					   std::abs(max.z - min.z) * 0.5f };
	return extents;
}
std::vector<Vector3> AABB::Corners()
{
	std::vector<Vector3> corners;
	corners.push_back(min);
	corners.push_back(Vector3(min.x, max.y, min.z));
	corners.push_back(max);
	corners.push_back(Vector3(max.x, min.y, min.z));
	return corners;
}
void AABB::Fit(std::vector<Vector3> points)
{
	min = Vector3(std::numeric_limits<double>::infinity(),
		std::numeric_limits<double>::infinity(),
		std::numeric_limits<double>::infinity());
	max = Vector3(-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity());
	// find min and max of the points
	for (Vector3 p : points)
	{
		min.Min(min, p);
		max.Max(max, p);
	}
}
bool AABB::Overlaps(Vector3 p)
{
	// test for not overlapped as it exits faster
	return !(p.x < min.x || p.y < min.y || p.x > max.x || p.y > max.y);
}
Vector3 AABB::ClosestPoint(Vector3 p)
{
	Vector3 closestPoint;
	return closestPoint.Clamp(p, min, max);
}