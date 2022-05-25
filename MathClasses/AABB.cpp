#include "AABB.h"
AABB::AABB()
{

}


AABB::AABB(Vectr3 min, Vectr3 max)
{
	this->min = min;
	this->max = max;
}


Vectr3 AABB::Center()
{
	return (min + max) * 0.5f;
}
Vectr3 AABB::Extents()
{
	Vectr3 extents = { std::abs(max.x - min.x) * 0.5f,
					   std::abs(max.y - min.y) * 0.5f,
					   std::abs(max.z - min.z) * 0.5f };
	return extents;
}
std::vector<Vectr3> AABB::Corners()
{
	std::vector<Vectr3> corners;
	corners.push_back(min);
	corners.push_back(Vectr3(min.x, max.y, min.z));
	corners.push_back(max);
	corners.push_back(Vectr3(max.x, min.y, min.z));
	return corners;
}
void AABB::Fit(std::vector<Vectr3> points)
{
	min = Vectr3(std::numeric_limits<double>::infinity(),
		std::numeric_limits<double>::infinity(),
		std::numeric_limits<double>::infinity());
	max = Vectr3(-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity());
	// find min and max of the points
	for (Vectr3 p : points)
	{
		min.Min(min, p);
		max.Max(max, p);
	}
}

Vectr3 AABB::ClosestPoint(Vectr3 p)
{
	Vectr3 closestPoint;
	return closestPoint.Clamp(p, min, max);
}

bool AABB::IsEmpty()
{
    return (min.x > max.x || min.y > max.y || min.z > max.z);
}

void AABB::Empty()
{
    min = { std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity() };
    max = { -std::numeric_limits<double>::infinity(),
            -std::numeric_limits<double>::infinity(),
            -std::numeric_limits<double>::infinity() };
}

void AABB::SetToTransformedBox(AABB box, Matrix3 m)
{
    // If we're empty, then exit (an empty box defined as having the min/max set to infinity)
    if (box.IsEmpty())
    {
        Empty();
        return;
    }
    // Sets the min and max to 0 as it does not return the correct value if not done. 
    min = { 0, 0, 0 };
    max = { 0, 0, 0 };
    //Examine each of the nine matrix elements an compute the new AABB
    if (m.m00 > 0.0f)
    {
        min.x += m.m00 * box.min.x; max.x += m.m00 * box.max.x;
    }
    else
    {
        min.x += m.m00 * box.max.x; max.x += m.m00 * box.min.x;
    }
    if (m.m01 > 0.0f)
    {
        min.y += m.m01 * box.min.x; max.y += m.m01 * box.max.x;
    }
    else
    {
        min.y += m.m01 * box.max.x; max.y += m.m01 * box.min.x;
    }
    if (m.m02 > 0.0f)
    {
        min.z += m.m02 * box.min.x; max.z += m.m02 * box.max.x;
    }
    else
    {
        min.z += m.m02 * box.max.x; max.z += m.m02 * box.min.x;
    }
    if (m.m10 > 0.0f)
    {
        min.x += m.m10 * box.min.y; max.x += m.m10 * box.max.y;
    }
    else
    {
        min.x += m.m10 * box.max.y; max.x += m.m10 * box.min.y;
    }
    if (m.m11 > 0.0f)
    {
        min.y += m.m11 * box.min.y; max.y += m.m11 * box.max.y;
    }
    else
    {
        min.y += m.m11 * box.max.y; max.y += m.m11 * box.min.y;
    }
    if (m.m12 > 0.0f)
    {
        min.z += m.m12 * box.min.y; max.z += m.m12 * box.max.y;
    }
    else
    {
        min.z += m.m12 * box.max.y; max.z += m.m12 * box.min.y;
    }
    if (m.m20 > 0.0f)
    {
        min.x += m.m20 * box.min.z; max.x += m.m20 * box.max.z;
    }
    else
    {
        min.x += m.m20 * box.max.z; max.x += m.m20 * box.min.z;
    }
    if (m.m21 > 0.0f)
    {
        min.y += m.m21 * box.min.z; max.y += m.m21 * box.max.z;
    }
    else
    {
        min.y += m.m21 * box.max.z; max.y += m.m21 * box.min.z;
    }
    if (m.m22 > 0.0f)
    {
        min.z += m.m22 * box.min.z; max.z += m.m22 * box.max.z;
    }
    else
    {
        min.z += m.m22 * box.max.z; max.z += m.m22 * box.min.z;
    }
}

