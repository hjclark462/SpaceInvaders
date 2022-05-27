#pragma once
#include "raylib.h"
#define NUM_ENEMY_COUNT 55
struct Enemy
{
public:	
	Vector2 center = {0.0f, 0.0f};
	float radius = 10.0f;	
	float fireTime = 4.0f;
	bool isAlive = false;
	Vector2 speed = {0.0f, 0.0f};
	Color colour = RED;		
};