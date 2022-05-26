#pragma once
#include "raylib.h"
#define NUM_ENEMY_COUNT 55
struct Enemy
{
public:	
	Vector2 center;
	float radius = 10.0f;	
	float fireTime = 0.0f;
	bool isAlive;
	Vector2 speed;	
	Color colour;		
};