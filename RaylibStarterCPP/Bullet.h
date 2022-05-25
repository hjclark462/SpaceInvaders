#pragma once
#include "raylib.h"
#define NUM_BULLETS 30
struct Bullet
{
	Rectangle rectangle;
	Vector2 position;
	Vector2 speed;
	bool alive;
	Color colour;
};