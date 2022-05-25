#include "Sphere.h"
#include <limits>
Sphere::Sphere()
{

}

Sphere::Sphere(Vectr3 p, float r)
{
	center = p;
	radius = r;
}
void Sphere::Fit(Vectr3 points[], int length)
{
	// invalidate extents
	Vectr3 min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	Vectr3 max = { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };
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
void Sphere::Fit(std::vector<Vectr3> points)
{
	// invalidate extents
	Vectr3 min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	Vectr3 max = { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };
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
void Sphere::FitX(Vectr3 points[], int length)
{
	// invalidate extents
	Vectr3 sum;
	// find min and max of the points
	for (int i = 0; i < length; i++)
	{
		sum += points[i];
	}
	// put a circle around the min/max box
	center = sum / length;
	Vectr3 outer = center;
	for (int i = 0; i < length; i++)
	{
		if (points[i].Distance(center) > outer.Distance(center))
		{
			outer = points[i];
		}
	}
	radius = center.Distance(outer);
}
void Sphere::FitX(std::vector<Vectr3> points)
{
	// invalidate extents
	Vectr3 sum;
	// find min and max of the points
	for (Vectr3 p : points)
	{
		sum += p;
	}
	// put a circle around the min/max box
	center = sum / points.size();
	Vectr3 outer = center;
	for (Vectr3 p : points)
	{
		if (p.Distance(center) > outer.Distance(center))
		{
			outer = p;
		}
	}
	radius = center.Distance(outer);
}

Vectr3 Sphere::ClosestPoint(Vectr3 p) 
{
	//distance from center
	Vectr3 toPoint = p - center;
	// if outside the radius bring it back to the radius;
	if (toPoint.MagnitudeSqr() > radius * radius)
	{
		toPoint = toPoint.GetNormalised() * radius;
	}
	return center + toPoint;
}