#pragma once
#include "Vector3.h"
#include "AABB.h"
#include <vector>
class Sphere
{
public:
	Vector3 center = {0,0,0};
	float radius = 0;
	Sphere();
	Sphere(Vector3 p, float r);
	void Fit(Vector3 points[], int length);
	void Fit(std::vector<Vector3> points);
	void FitX(Vector3 points[], int length);
	void FitX(std::vector<Vector3> points);
	bool Overlaps(Vector3 p);
	bool Overlaps(Sphere other);
	bool Overlaps(AABB aabb);
	Vector3 ClosestPoint(Vector3 p);
};