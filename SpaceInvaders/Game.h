#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "raylib.h"
#include <string>
#include <vector>
#include <time.h>
class Game
{
public:
	float currentTime;
	float previousTime;
	float deltaTime = 0.0f;
	float fps;
	Player player;
	Bullet bullet[NUM_BULLET_COUNT];
	Bullet enemyBullet[NUM_ENEMY_BULLETS];
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
	void GetDeltaTime();
	void UpdateGame();
	void DrawGame();
};