#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "raylib.h"
#include <string>
#include <vector>
class Game
{
public:
	Player player;
	Bullet bullet[NUM_BULLET_COUNT];
	std::vector<Enemy> enemy;
	int enemyRows = 5;
	int enemyCols = 11;
	int deadEnemies = 0;
	bool moveRight = true;
	bool allMoved = false;
	int score = 0;	
	int screenWidth = 800;
	int screenHeight = 450;
	void InitGame();
	void UpdateGame();
	void DrawGame();
};