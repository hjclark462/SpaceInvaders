#pragma once
#include "raylib.h"
#define NUM_MAX_ENEMIES 55
class Enemy
{
public:
	Vector2 center;
	float radius = 10;
	Vector2 speed;
	bool alive;
	Color colour;	
	Enemy();	
};