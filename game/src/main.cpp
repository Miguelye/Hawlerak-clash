#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
	//Window Dimensions
	const int WINDOW_DIMENSION[2]{ 384, 384 };

	InitWindow( WINDOW_DIMENSION[0], WINDOW_DIMENSION[1], "Hawlerak Clash" );


	//Textures
	Texture2D map = LoadTexture("nature_tileset/MapWorld.png");
	Texture2D rockTexture = LoadTexture("nature_tileset/Rock.png");

	//Objects
	Character knight(WINDOW_DIMENSION[0], WINDOW_DIMENSION[1]);
	Prop rock(Vector2{1600.0f, 200.0f}, rockTexture);

	//Positions
	Vector2 mapPos{	
		(-map.width * 2) + WINDOW_DIMENSION[0],
		(0.0) }; //SelfNote: is negative widh becuase the image is the one that moves not the window, and time 2 'cause map is scaled by 2.
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

		rock.Render(knight.getWorldPos());
		knight.tick(dT);

		//variables
		bool isOutOfBound = knight.getWorldPos().x < 0.f ||
							knight.getWorldPos().y < 0.f ||
							knight.getWorldPos().x + WINDOW_DIMENSION[0] > map.width * mapScale ||
							knight.getWorldPos().y + WINDOW_DIMENSION[1] > map.height * mapScale;
		
		
		if (isOutOfBound)
		{
			knight.mapOutOfBound();
		}

		EndDrawing();
	}
	CloseWindow();
}