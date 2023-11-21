#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
	//Window Dimensions
	const int WINDOW_DIMENSION[2]{ 384, 384 };

	InitWindow( WINDOW_DIMENSION[0], WINDOW_DIMENSION[1], "Hawlerak Clash" );


	//Textures
	Texture2D map = LoadTexture("nature_tileset/MapWorld.png");
	Texture2D rockTexture = LoadTexture("nature_tileset/Rock.png");
	Texture2D goblinIdle = LoadTexture("characters/goblin_idle_spritesheet.png");
	Texture2D goblinRun = LoadTexture("characters/goblin_run_spritesheet.png");
	Texture2D slimeRun = LoadTexture("characters/slime_run_spritesheet.png");
	Texture2D slimeIdle = LoadTexture("characters/slime_idle_spritesheet.png");

	//Objects
	Character knight(WINDOW_DIMENSION[0], WINDOW_DIMENSION[1]);
	Enemy goblin(Vector2{ 1800.0f, 350.0f }, goblinIdle, goblinRun);
	Enemy goblin1(Vector2{ 1200.0f, 500.0f }, goblinIdle, goblinRun);
	Enemy goblin2(Vector2{ 800.0f, 200.0f }, goblinIdle, goblinRun);
	Enemy slime(Vector2{ 1500.0f, 300.0f }, slimeIdle, slimeRun);
	Enemy slime2(Vector2{ 1000.0f, 150.0f }, slimeIdle, slimeRun);
	Enemy slime3(Vector2{ 700.0f, 400.0f }, slimeIdle, slimeRun);

	Enemy* enemies[]{ &goblin, &slime, &goblin1, &goblin2, &slime2, &slime3 };

	int deadEnemies = 0;

	Prop propArr[2]{
		Prop{Vector2{1600.0f, 320.0f}, rockTexture},
		Prop{Vector2{1600.0f, 256.0f}, rockTexture}
	};

	//Positions
	Vector2 mapPos{	
		(-map.width * 2) + WINDOW_DIMENSION[0],
		(0.0) }; //SelfNote: is negative widh because the image is the one that moves not the window, and time 2 'cause map is scaled by 2.
	const float mapScale = 2.0f;
	SetTargetFPS(60);
	Vector2 playerInitPos{ 1800.0, 80.0 };
	knight.setWorldPos(playerInitPos);

	for each (auto enemy in enemies)
	{
		enemy->setTarget(&knight);
	}

	while (!WindowShouldClose())
	{
		const float dT = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		mapPos = (Vector2Scale(knight.getWorldPos(), -1.0f));
		//Maps
		DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

		//Draw Props
		for each (Prop Props in propArr)
		{
			Props.Render(knight.getWorldPos());
		}

		//Ticks
		for each (auto enemy in enemies)
		{
			enemy->tick(dT);
		}
		knight.tick(dT);



		//variables
		bool isOutOfBound = knight.getWorldPos().x < 0.f ||
							knight.getWorldPos().y < 0.f ||
							knight.getWorldPos().x + WINDOW_DIMENSION[0] > map.width * mapScale ||
							knight.getWorldPos().y + WINDOW_DIMENSION[1] > map.height * mapScale;
		
		//Colliding of map boundaries
		if (isOutOfBound)
		{
			knight.UndoMovement();
		}

		//collading with props
		for each (auto props in propArr)
		{
			if (CheckCollisionRecs(props.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
			{
				knight.UndoMovement();
			}
		}

		if (!knight.getAlive()) //knight is dead
		{
			DrawText("Game Over!", 55.f, 45.f, 40, RED);
			EndDrawing();
			goblin.setSpeed(0);
			continue;
		}
		else
		{
			std::string knightHealthString = "Health: ";
			knightHealthString.append(std::to_string(knight.getHealth()), 0, 5);
			DrawText(knightHealthString.c_str(), 55.f, 45.f, 40, GREEN);
		}

		//Killing goblings
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			for each (auto enemy in enemies)
			{
				if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
				{
					enemy->setAlive(false);
					deadEnemies++;
				}
			}
		}

		if (deadEnemies >= 6)
		{
			DrawText("You Win!", 100.f, 160.f, 40, YELLOW);
			EndDrawing();
			continue;
		}
		EndDrawing();
	}
	CloseWindow();
}