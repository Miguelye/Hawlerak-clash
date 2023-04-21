#include "raylib.h"
#include "raymath.h"
#include "Character.h"

//Window Dimensions
const int WINDOW_DIMENSION[2]{ 384, 384 };

int main()
{
	InitWindow( WINDOW_DIMENSION[0], WINDOW_DIMENSION[1], "Hawlerak Clash" );

	Character knight;

	knight.setScreenPos(WINDOW_DIMENSION[0], WINDOW_DIMENSION[1]);

	//Textures
	Texture2D map = LoadTexture("nature_tileset/MapWorld.png");

	//Positions
	Vector2 mapStartPos{	
		(-map.width * 2) + WINDOW_DIMENSION[0],
		(0.0) }; //SelfNote: is negative widh becuase the image is the one that moves not the window, and time 2 'cause map is scaled by 2.
	Vector2 mapPos{};
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		const float dT = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		mapPos = Vector2Add(Vector2Scale(knight.getWorldPos(), -1.0f), mapStartPos);
		
		//Maps
		DrawTextureEx(map, mapPos, 0.0, 2.0, WHITE);

		knight.tick(dT);

		EndDrawing();
	}
	CloseWindow();
}