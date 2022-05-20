#pragma once
#include "raylib.h"
#include "SceneObject.h"
#include <string>
using namespace std;
class SpriteObject : public SceneObject
{
	Image image;
public:
	Texture2D texture;
	float width;
	float height;
	SpriteObject();
	void Load(string filname);
	void OnDraw() override;
};