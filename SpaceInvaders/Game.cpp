#include "Game.h"

void Game::InitGame()
{
	//  Initialise the Game window
	InitWindow(screenWidth, screenHeight, "Space Invaders-ish!");
	SetTargetFPS(60);

	//  Initialise the player variables
	player.rectangle.x = screenWidth / 2.0f;
	player.rectangle.y = screenHeight - 30.0f;
	player.rectangle.width = 20.0f;
	player.rectangle.height = 20.0f;
	player.speed.x = 0.5f;
	player.speed.y = 0.0f;
	player.colour = GREEN;
	player.isAlive = true;

	//	Initialise the player's bullets to use and the variables of the bullet
	for (int i = 0; i < NUM_BULLET_COUNT; i++)
	{
		bullet[i].rectangle.x = player.rectangle.x;
		bullet[i].rectangle.y = player.rectangle.y + player.rectangle.height / 4;
		bullet[i].rectangle.width = 5.0f;
		bullet[i].rectangle.height = 10.0f;
		bullet[i].speed.x = 0.0f;
		bullet[i].speed.y = -0.2f;
		bullet[i].fired = false;
		bullet[i].colour = GREEN;
	}

	//	Initialise the enemy's bullets to use and the variables of the bullet
	for (int i = 0; i < NUM_ENEMY_BULLETS; i++)
	{
		enemyBullet[i].rectangle.x = player.rectangle.x;
		enemyBullet[i].rectangle.y = player.rectangle.y + player.rectangle.height / 4.0f;
		enemyBullet[i].rectangle.width = 5.0f;
		enemyBullet[i].rectangle.height = 10.0f;
		enemyBullet[i].speed.x = 0.0f;
		enemyBullet[i].speed.y = 0.2f;
		enemyBullet[i].fired = false;
		enemyBullet[i].colour = GREEN;
	}

	//	Initialise all the enemies and the variables for the enemies
	for (int i = 0; i < enemyRows; i++)
	{
		for (int j = 0; j < enemyCols; j++)
		{
			int index = i * enemyCols + j;
			Enemy newEnemy;
			newEnemy.center.x = (j + 1) * 65.0f;
			newEnemy.center.y = (i + 1) * 40.0f;
			newEnemy.speed.x = 0.05f;
			newEnemy.speed.y = 5.0f;
			newEnemy.isAlive = true;
			if (i == 0)
			{
				newEnemy.colour = BLUE;
			}
			else if (i == 1 || i == 2)
			{
				newEnemy.colour = RED;
			}
			else
			{
				newEnemy.colour = GREEN;
			}
			enemy.push_back(newEnemy);
		}
	}
}

void Game::GetDeltaTime()
{
	currentTime = clock();
	deltaTime = currentTime - previousTime;
	fps = (1 / deltaTime) * 1000;
}

void Game::UpdateGame()
{
	//  Player movement
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		player.rectangle.x += player.speed.x * deltaTime;
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		player.rectangle.x -= player.speed.x * deltaTime;
	}

	//  Stops the player from going outside the bounds of the window
	if (player.rectangle.x <= 0)
	{
		player.rectangle.x = 0;
	}
	if (player.rectangle.x + player.rectangle.width >= screenWidth)
	{
		player.rectangle.x = screenWidth - player.rectangle.width;
	}

	//	Controls for firing
	if (IsKeyDown(KEY_SPACE))
	{
		for (int i = 0; i < NUM_BULLET_COUNT; i++)
		{
			if (!bullet[i].fired)
			{
				bullet[i].rectangle.x = player.rectangle.x + player.rectangle.width / 2.5f;
				bullet[i].rectangle.y = player.rectangle.y + player.rectangle.height / 4;
				bullet[i].fired = true;
				break;
			}
		}
	}

	//	Player bullet movement
	for (int i = 0; i < NUM_BULLET_COUNT; i++)
	{
		if (bullet[i].fired)
		{
			//	Calculates the movement of the bullet
			bullet[i].rectangle.y += bullet[i].speed.y * deltaTime;
			//	If it leaves the screen set it dead
			if (bullet[i].rectangle.y <= 0)
			{
				bullet[i].fired = false;
			}
			for (int j = 0; j < NUM_ENEMY_COUNT; j++)
			{
				//	Bullet shot the enemy and killed it!
				if (CheckCollisionPointCircle(bullet[i].position = { bullet[i].rectangle.x, bullet[i].rectangle.y }, enemy[j].center, enemy[j].radius)
					&& enemy[j].isAlive)
				{
					bullet[i].fired = false;
					enemy[j].isAlive = false;
					int row = j / enemyCols;
					if (row == 4 || row == 3)
					{
						score += 10;
					}
					else if (row == 2 || row == 1)
					{
						score += 20;
					}
					else
					{
						score += 30;
					}
					for (int k = 0; k < NUM_ENEMY_COUNT; k++)
					{
						enemy[k].speed.x += 0.001f;
					}
				}
			}
		}
	}
	//	Enemy firing bullets 
	for (int i = 0; i < NUM_ENEMY_COUNT; i++)
	{
		enemy[i].fireTime -= deltaTime;
		int rando = rand() % 11;
		if (enemy[i].fireTime <= 0 && rando == 0 && (i >= NUM_ENEMY_COUNT - 11 || !enemy[i + 11].isAlive))
		{
			for (int j = 0; j < NUM_ENEMY_BULLETS; j++)
			{
				if (!enemyBullet[j].fired)
				{
					enemyBullet[j].rectangle.x = enemy[i].center.x;
					enemyBullet[j].rectangle.y = enemy[i].center.y;
					enemyBullet[j].fired = true;
					break;
				}
			}			
			enemy[i].fireTime = 4.0f;
		}		
	}
	//	Moving the Enemies
	allMoved = false;
	while (!allMoved)
	{
		for (int i = 0; i < NUM_ENEMY_COUNT; i++)
		{
			if (moveRight)
			{
				enemy[i].center.x += enemy[i].speed.x * deltaTime;
				if ((enemy[i].center.x > screenWidth - 16 && enemy[i].isAlive))
				{
					moveRight = false;
					enemy[i].center.x = screenWidth - 16.0f;
					for (int j = 0; j < NUM_ENEMY_COUNT; j++)
					{
						enemy[j].center.y += enemy[j].speed.y;
					}
				}
			}
			else
			{
				enemy[i].center.x += (enemy[i].speed.x * -1) * deltaTime;
				if ((enemy[i].center.x < 0 && enemy[i].isAlive))
				{
					moveRight = true;
					enemy[i].center.x = 0;
					for (int j = 0; j < NUM_ENEMY_COUNT; j++)
					{
						enemy[j].center.y += enemy[j].speed.y;
					}
				}
			}
		}
		allMoved = true;
	}
	//	Calculates the movement of the bullet
	for (int j = 0; j < NUM_ENEMY_BULLETS; j++)
	{
		if (enemyBullet[j].fired)
		{
			enemyBullet[j].rectangle.y += enemyBullet[j].speed.y * deltaTime;
			//	If it leaves the screen set it dead
			if (enemyBullet[j].rectangle.y >= screenHeight)
			{
				enemyBullet[j].fired = false;
			}
			//	Bullet shot the enemy and killed it!
			if (CheckCollisionRecs(enemyBullet[j].rectangle, player.rectangle))
			{
				enemyBullet[j].fired = false;
				player.lives--;
				if (player.lives <= 0)
				{
					CloseWindow();
				}
			}
		}
		
	}
}

void Game::DrawGame()
{
	//	Begin drawing and set the background colour
	BeginDrawing();
	ClearBackground(BLACK);
	//	Draw the player
	DrawRectangleRec(player.rectangle, player.colour);
	//	If there are bullets onscreen draw them
	for (int i = 0; i < NUM_BULLET_COUNT; i++)
	{
		if (bullet[i].fired)
		{
			DrawRectangleRec(bullet[i].rectangle, bullet[i].colour);
		}
	}
	//	If there are enemies onscreen draw them
	for (int i = 0; i < NUM_ENEMY_COUNT; i++)
	{
		if (enemy[i].isAlive)
		{
			DrawCircle(enemy[i].center.x, enemy[i].center.y, enemy[i].radius, enemy[i].colour);
		}
	}
	for (int i = 0; i < NUM_ENEMY_BULLETS; i++)
	{
		if (enemyBullet[i].fired)
		{
			DrawRectangleRec(enemyBullet[i].rectangle, enemyBullet[i].colour);
		}
	}
	DrawText(std::to_string(score).c_str(), 40, 40, 15, RED);
	DrawText(std::to_string(fps).c_str(), 40, 50, 20, GREEN);
	EndDrawing();
}