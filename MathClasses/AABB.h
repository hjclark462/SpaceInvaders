#include "Vector3.h"
#include <vector>
class AABB
{
public:
	Vector3 min = { 0,0,0 };
	Vector3 max = { 0, 0, 0};
	AABB();
	AABB(Vector3 min, Vector3 max);
	Vector3 Center();
	Vector3 Extents();
	std::vector<Vector3> Corners();

};