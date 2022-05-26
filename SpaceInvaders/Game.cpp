#include "Game.h"

void Game::InitGame()
{
	//  Initialise the Game window
	InitWindow(screenWidth, screenHeight, "Space Invaders-ish!");
	SetTargetFPS(60);

	//  Initialise the player variables
	player.rectangle.x = screenWidth / 2.0f;
	player.rectangle.y = screenHeight - 20;
	player.rectangle.width = 20;
	player.rectangle.height = 20;
	player.speed.x = 5;
	player.speed.y = 5;
	player.colour = GREEN;

	//	Initialise the amount of bullets to use and the variables of the bullet
	for (int i = 0; i < NUM_BULLET_COUNT; i++)
	{
		bullet[i].rectangle.x = player.rectangle.x;
		bullet[i].rectangle.y = player.rectangle.y + player.rectangle.height / 4;
		bullet[i].rectangle.width = 5;
		bullet[i].rectangle.height = 10;
		bullet[i].speed.x = 0;
		bullet[i].speed.y = -15;
		bullet[i].flying = false;
		bullet[i].colour = GREEN;
	}
	//	Initialise all the enemies and the variables for the enemies
	for (int i = 0; i < enemyRows; i++)
		{
			for (int j = 0; j < enemyCols; j++)
			{
				int index = i * enemyCols + j;
				Enemy newEnemy;
				newEnemy.center.x = (j + 1) * 65;
				newEnemy.center.y = (i + 1) * 40;
				newEnemy.speed.x = 1.0f;
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

void Game::UpdateGame()
{
	//  Player movement
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		player.rectangle.x += player.speed.x;
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		player.rectangle.x -= player.speed.x;
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
			if (!bullet[i].flying)
			{
				bullet[i].rectangle.x = player.rectangle.x + player.rectangle.width / 2.5f;
				bullet[i].rectangle.y = player.rectangle.y + player.rectangle.height / 4;
				bullet[i].flying = true;
				break;
			}
		}
	}	

	//	Bullet movement
	for (int i = 0; i < NUM_BULLET_COUNT; i++)
	{
		if (bullet[i].flying)
		{
			//	Calculates the movement of the bullet
			bullet[i].rectangle.y += bullet[i].speed.y;
			//	If it leaves the screen set it dead
			if (bullet[i].rectangle.y <= 0)
			{
				bullet[i].flying = false;				
			}
			for (int j = 0; j < NUM_ENEMY_COUNT; j++)
			{
				//	Bullet shot the enemy and killed it!
				if (CheckCollisionPointCircle(bullet[i].position = { bullet[i].rectangle.x, bullet[i].rectangle.y }, enemy[j].center, enemy[j].radius)
					&& enemy[j].isAlive)
				{
					bullet[i].flying = false;
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
						enemy[k].speed.x += 0.05f;
					}
				}
			}
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
				enemy[i].center.x += enemy[i].speed.x;
				if ((enemy[i].center.x > screenWidth && enemy[i].isAlive) || (enemy[i].center.x < 0 && enemy[i].isAlive))
				{
					moveRight = false;
					enemy[i].center.x = screenWidth;
					for (int j = 0; j < NUM_ENEMY_COUNT; j++)
					{
						enemy[j].center.y += enemy[j].speed.y;
					}
				}
			}
			else
			{
				enemy[i].center.x += (enemy[i].speed.x * -1);
				if ((enemy[i].center.x > screenWidth && enemy[i].isAlive) || (enemy[i].center.x < 0 && enemy[i].isAlive))
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
		if (bullet[i].flying)
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
	DrawText(std::to_string(score).c_str(), 40, 40, 15, RED);
	EndDrawing();
}