#pragma once
#include "SceneObject.h"
#include "AABB.h"
#include "Sphere.h"
class CollisionObject : public SceneObject
{
public:
	AABB box;
	AABB originalBox;
	Sphere sphere;
	CollisionObject();
	CollisionObject(Vectr3 min, Vectr3 max);
	CollisionObject(Vectr3 center, float radius);
	void OnUpdate(float deltaTime) override;
	void Translate(float x, float y) override;
	void UpdatePosition();	
	bool Overlaps(Vectr3 p);
	bool Overlaps(Sphere other);
	bool Overlaps(AABB other);
	bool CollisionCheck(CollisionObject other);
};
