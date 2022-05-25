#pragma once
#include "SpriteObject.h"

SpriteObject::SpriteObject()
{

}

void SpriteObject::Load(string filename)
{
	int length = filename.length();
	char* file = new char[length + 1];
	strcpy(file, filename.c_str());
	image = LoadImage(file);
	texture = LoadTextureFromImage(image);
}

void SpriteObject::OnDraw()
{
	float rotation = (float)atan2(globalTransform.m01, globalTransform.m00);
	DrawTextureEx(texture, Vector2{ globalTransform.m20, globalTransform.m21 },
		rotation * (float)(180.0f / PI), 1, Color(WHITE));
}