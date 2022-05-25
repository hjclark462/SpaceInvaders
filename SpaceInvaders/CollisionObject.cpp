#include "CollisionObject.h"

CollisionObject::CollisionObject()
{
	
}

CollisionObject::CollisionObject(Vectr3 min, Vectr3 max)
{
	originalBox = { min, max };
	box = {};
}

CollisionObject::CollisionObject(Vectr3 center, float radius)
{
	sphere = {center, radius};
}

void CollisionObject::OnUpdate(float deltaTime)
{
	UpdatePosition();
}

void CollisionObject::Translate(float x, float y)
{
	SceneObject::Translate(x, y);
	UpdatePosition();
}

void CollisionObject::UpdatePosition()
{
	if (box.IsEmpty())
	{
		sphere.center.x = globalTransform.m20;
		sphere.center.y = globalTransform.m21;
	}
	else
	{
		box.SetToTransformedBox(originalBox, globalTransform);
	}
}

bool CollisionObject::Overlaps(Vectr3 p)
{
	// test for not overlapped as it exits faster
	return !(p.x < box.min.x || p.y < box.min.y || p.x > box.max.x || p.y > box.max.y);
}

bool CollisionObject::Overlaps(Sphere other)
{
	Vectr3 diff = box.ClosestPoint(other.center) - other.center;
	return diff.Dot(diff) <= (other.radius * other.radius);
}

bool CollisionObject::Overlaps(AABB other)
{
	return !(box.max.x < other.min.x || box.max.y < other.min.y || box.min.x > other.max.x || box.min.y > other.max.y);
}


bool CollisionObject::CollisionCheck(CollisionObject other)
{
	if (box.IsEmpty())
	{
		// Checks which Geometry class the other CollisionObject is being used
		if (other.box.IsEmpty())
		{
			return Overlaps(other.sphere);
		}
		else
		{
			return Overlaps(other.box);
		}
	}
	else
	{
		// Checks which Geometry class the other CollisionObject is being used
		if (other.box.IsEmpty())
		{
			return Overlaps(other.sphere);
		}
		else
		{
			return Overlaps(other.box);
		}
	}
}
