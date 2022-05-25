#include "SceneObject.h"
#include <assert.h>
#include <algorithm>
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
		globalTransform = { parent->globalTransform * localTransform };
	}
	else
	{
		globalTransform = localTransform;
	}
	for (SceneObject child : children)
	{
		child.UpdateTransform();
	}
}

void SceneObject::SetPosition(float x, float y)
{
	localTransform.SetTranslation(x, y);
	UpdateTransform();
}

void SceneObject::SetRotate(float radians)
{
	localTransform.SetRotateZ(radians);
	UpdateTransform();
}

void SceneObject::SetScale(float width, float height)
{
	localTransform.SetScale(width, height, 1);
	UpdateTransform();
}

void SceneObject::Translate(float x, float y)
{
	localTransform.Translate(x, y);
	UpdateTransform();
}

void SceneObject::Rotate(float radians)
{
	localTransform.RotateZ(radians);
	UpdateTransform();
}

void SceneObject::Scale(float width, float height)
{
	localTransform.Scale(width, height, 1);
	UpdateTransform();
}

int SceneObject::GetChildCount()
{
	return children.size();
}

SceneObject SceneObject::GetChild(int index)
{
	return children[index];
}

void SceneObject::OnUpdate(float deltaTime)
{

}

void SceneObject::OnDraw()
{

}

void SceneObject::Update(float deltaTime)
{
	// run OnUpdate behaviour
	OnUpdate(deltaTime);

	// update children
	for (int i = 0; i < children.size(); i++)
	{
		children[i].Update(deltaTime);
	}
}

void SceneObject::Draw()
{
	// run OnDraw behaviour
	OnDraw();

	// draw children
	for(SceneObject child : children)
	{
		child.Draw();
	}
}
