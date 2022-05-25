#pragma once
#include "SceneObject.h"
#include "Sphere.h"
class SphereCollision : public SceneObject
{
public:
	Sphere sphere;
	SphereCollision();
	SphereCollision(Vectr3 min, Vectr3 max);
	void OnUpdate(float deltaTime) override;
	void Translate(float x, float y);
	void UpdatePosition();
	bool CollisionCheck();
};