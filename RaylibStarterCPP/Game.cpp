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
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		bullet[i].rectangle.x = player.rectangle.x;
		bullet[i].rectangle.y = player.rectangle.y + player.rectangle.height / 4;
		bullet[i].rectangle.width = 5;
		bullet[i].rectangle.height = 10;
		bullet[i].speed.x = 0;
		bullet[i].speed.y = -10;
		bullet[i].alive = false;
		bullet[i].colour = GREEN;
	}
	//	Initialise all the enemies and the variables for the enemies
	for (int i = 0; i < NUM_MAX_ENEMIES; i++)
	{
		enemy[i].center.x = GetRandomValue(0, screenWidth);
		enemy[i].center.y = GetRandomValue(-screenHeight, -20);
		enemy[i].speed.x = 1;
		enemy[i].speed.y = 1;
		enemy[i].alive = true;
		enemy[i].colour = GREEN;
	}
}

void Game::UpdateGame()
{
	//  Player movement
	if (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D))
	{
		player.rectangle.x += player.speed.x;
	}
	if (IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A))
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
		fireRate += 5;
		for (int i = 0; i < NUM_BULLETS; i++)
		{
			if (!bullet[i].alive && fireRate % 20 == 0)
			{
				bullet[i].rectangle.x = player.rectangle.x + player.rectangle.width / 2.5f;
				bullet[i].rectangle.y = player.rectangle.y + player.rectangle.height / 4;
				bullet[i].alive = true;
				break;
			}
		}
	}
	//	Bullet movement
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		if (bullet[i].alive)
		{
			//	Calculates the movement of the bullet
			bullet[i].rectangle.y += bullet[i].speed.y;
			//	If it leaves the screen set it dead
			if (bullet[i].rectangle.y <= 0)
			{
				bullet[i].alive = false;
				fireRate = 0;
			}
			for (int j = 0; j < aliveEnemies; j++)
			{
				//	Bullet shot the enemy asnd killed it!
				if (CheckCollisionPointCircle(bullet[i].position = { bullet[i].rectangle.x, bullet[i].rectangle.y }, enemy[j].center, enemy[j].radius))
				{
					bullet[i].alive = false;
					enemy[j].center.x = GetRandomValue(screenWidth, screenWidth + 1000);
					enemy[j].center.y = GetRandomValue(0, screenHeight - enemy[j].radius * 2);
					fireRate = 0;
				}
			}
		}
	}
	//	Moving the Enemies
	for (int i = 0; i < aliveEnemies; i++)
	{
		if (enemy[i].alive)
		{
			//	Adds the speed to the position creating movement
			enemy[i].center.y += enemy[i].speed.y;
			//	If it crosses the screen reset it in the array to keep coming through as if still alive
			if (enemy[i].center.y > screenHeight)
			{
				enemy[i].center.x = GetRandomValue(0, screenWidth);
				enemy[i].center.y = GetRandomValue(-screenHeight, -20);
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
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		if (bullet[i].alive)
		{
			DrawRectangleRec(bullet[i].rectangle, bullet[i].colour);

		}
	}
	//	If there are enemies onscreen draw them
	for (int i = 0; i < aliveEnemies; i++)
	{
		if (enemy[i].alive)
		{
			DrawCircle(enemy[i].center.x, enemy[i].center.y, enemy[i].radius, enemy[i].colour);
		}

	}
	EndDrawing();
}