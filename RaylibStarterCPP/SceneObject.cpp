#include "SceneObject.h"
using namespace std;
SceneObject::SceneObject()
{
	
}

SceneObject::~SceneObject()
{

}

void SceneObject::UpdateTransform()
{
	if (parent != nullptr)
	{
		globalTransorm = (parent->globalTransorm * localTransform);
	}
}

void SceneObject::SetPosition()
{
}

void SceneObject::SetRotate()
{
}

void SceneObject::SetScale()
{
}

int SceneObject::GetChildCount()
{
	return 0;
}

SceneObject SceneObject::GetChild(int index)
{
	return SceneObject();
}

void SceneObject::AddChild(SceneObject child)
{
}

void SceneObject::RemoveChild(SceneObject child)
{
}

void SceneObject::OnUpdate(float deltaTime)
{
}

void SceneObject::OnDraw()
{
}

void SceneObject::Update(float deltaTime)
{
}

void SceneObject::Draw()
{
}
