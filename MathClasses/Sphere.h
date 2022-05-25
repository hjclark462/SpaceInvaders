#pragma once
#include "Vector3.h"
#include "AABB.h"
#include <vector>
class Sphere
{
public:
	Vectr3 center = {0,0,0};
	float radius = 0;
	Sphere();
	Sphere(Vectr3 p, float r);
	void Fit(Vectr3 points[], int length);
	void Fit(std::vector<Vectr3> points);
	void FitX(Vectr3 points[], int length);
	void FitX(std::vector<Vectr3> points);	
	Vectr3 ClosestPoint(Vectr3 p);
};