#pragma once
#include "raylib.h"
struct Player
{
	Rectangle rectangle;
	Vector2 speed;
	Color colour;
	bool isAlive;
	int lives = 3;
};

