#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "raylib.h"
class Game
{
public:
	Player player;
	Bullet bullet[NUM_BULLETS];
	Enemy enemy[NUM_MAX_ENEMIES];
	int fireRate = 0;
	int aliveEnemies = 10;
	int screenWidth = 800;
	int screenHeight = 450;
	void InitGame();
	void UpdateGame();
	void DrawGame();
};