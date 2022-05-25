#include "Sphere.h"
#include <limits>
Sphere::Sphere()
{

}
Sphere::Sphere(Vector3 p, float r)
{
	center = p;
	radius = r;
}
void Sphere::Fit(Vector3 points[], int length)
{
	// invalidate extents
	Vector3 min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	Vector3 max = { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };
	// find min and max of the points
	for (int i = 0; i < length; i++)
	{
		min.Min(min, points[i]);
		max.Max(max, points[i]);
	}
	// put a circle around the min/max box
	center = (min + max) * 0.5f;
	radius = center.Distance(max);
}
void Sphere::Fit(std::vector<Vector3> points)
{
	// invalidate extents
	Vector3 min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	Vector3 max = { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };
	// find min and max of the points
	for (int i = 0; i < points.size(); i++)
	{
		min.Min(min, points[i]);
		max.Max(max, points[i]);
	}
	// put a circle around the min/max box
	center = (min + max) * 0.5f;
	radius = center.Distance(max);
}
void Sphere::FitX(Vector3 points[], int length)
{
	// invalidate extents
	Vector3 sum;
	// find min and max of the points
	for (int i = 0; i < length; i++)
	{
		sum += points[i];
	}
	// put a circle around the min/max box
	center = sum / length;
	Vector3 outer = center;
	for (int i = 0; i < length; i++)
	{
		if (points[i].Distance(center) > outer.Distance(center))
		{
			outer = points[i];
		}
	}
	radius = center.Distance(outer);
}
void Sphere::FitX(std::vector<Vector3> points)
{
	// invalidate extents
	Vector3 sum;
	// find min and max of the points
	for(Vector3 p : points)
	{
		sum += p;
	}
	// put a circle around the min/max box
	center = sum / points.size();
	Vector3 outer = center;
	for(Vector3 p : points)
	{
		if (p.Distance(center) > outer.Distance(center))
		{
			outer = p;
		}
	}
	radius = center.Distance(outer);
}
bool Sphere::Overlaps(Vector3 p) 
{
	Vector3 toPoint = p - center;
	return toPoint.MagnitudeSqr() <= (radius * radius);
}
bool Sphere::Overlaps(Sphere other) 
{
	Vector3 diff = other.center - center;
	// compare the distance between spheres to combined radii
	float r = radius + other.radius;
	return diff.MagnitudeSqr() <= (r * r);
}
bool Sphere::Overlaps(AABB aabb) 
{
	Vector3 diff = aabb.ClosestPoint(center) - center;
	return diff.Dot(diff) <= (radius * radius);
}
Vector3 Sphere::ClosestPoint(Vector3 p) 
{
	//distance from center
	Vector3 toPoint = p - center;
	// if outside the radius bring it back to the radius;
	if (toPoint.MagnitudeSqr() > radius * radius)
	{
		toPoint = toPoint.GetNormalised() * radius;
	}
	return center + toPoint;
}