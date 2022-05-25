#pragma once
#include "raylib.h"
#include "Vector3.h"
#include "Matrix3.h"
#include <vector>
using namespace std;

class SceneObject
{
protected:
	SceneObject* parent = nullptr;
	vector<SceneObject> children;
	Matrix3 localTransform = {1};
	Matrix3 globalTransform = {1};
public:
	SceneObject();
	~SceneObject();
	void UpdateTransform();
	void SetPosition(float x, float y);
	void SetRotate(float radians);
	void SetScale(float width, float height);
	virtual void Translate(float x, float y);
	void Rotate(float radians);
	void Scale(float width, float height);
	int GetChildCount();
	SceneObject GetChild(int index);
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw();
	void Update(float deltaTime);
	void Draw();
};