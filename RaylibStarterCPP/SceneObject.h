#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
using namespace std;

class SceneObject
{
protected:
	SceneObject* parent;
	vector<SceneObject> children;
	Matrix localTransform;
	Matrix globalTransorm;
public:
	SceneObject();
	~SceneObject();
	void UpdateTransform();
	void SetPosition();
	void SetRotate();
	void SetScale();
	int GetChildCount();
	SceneObject GetChild(int index);
	void AddChild(SceneObject child);
	void RemoveChild(SceneObject child);
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw();
	void Update(float deltaTime);
	void Draw();
};