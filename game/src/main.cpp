#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"


int main()
{
	//Window Dimensions
	const int WINDOW_DIMENSION[2]{ 384, 384 };

	InitWindow( WINDOW_DIMENSION[0], WINDOW_DIMENSION[1], "Hawlerak Clash" );


	//Textures
	Texture2D map = LoadTexture("nature_tileset/MapWorld.png");
	Texture2D rockTexture = LoadTexture("nature_tileset/Rock.png");
	Texture2D enemyIdle = LoadTexture("characters/goblin_idle_spritesheet.png");
	Texture2D enemyRun = LoadTexture("characters/goblin_run_spritesheet.png");

	//Objects
	Character knight(WINDOW_DIMENSION[0], WINDOW_DIMENSION[1]);
	Enemy goblin(Vector2{ 1800.0f, 350.0f }, enemyIdle, enemyRun);

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
		knight.tick(dT);
		goblin.tick(dT);

		//variables
		bool isOutOfBound = knight.getWorldPos().x < 0.f ||
							knight.getWorldPos().y < 0.f ||
							knight.getWorldPos().x + WINDOW_DIMENSION[0] > map.width * mapScale ||
							knight.getWorldPos().y + WINDOW_DIMENSION[1] > map.height * mapScale;
		
		
		if (isOutOfBound)
		{
			knight.UndoMovement();
		}

		for each (auto props in propArr)
		{
			if (CheckCollisionRecs(props.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
			{
				knight.UndoMovement();
			}
		}

		EndDrawing();
	}
	CloseWindow();
}