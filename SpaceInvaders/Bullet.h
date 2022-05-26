#pragma once
#include "raylib.h"
#define NUM_BULLET_COUNT 1
#define NUM_ENEMY_BULLETS 3
struct Bullet
{
	Rectangle rectangle;
	Vector2 position;
	Vector2 speed;
	bool fired;
	Color colour;
};