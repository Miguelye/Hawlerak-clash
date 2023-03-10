#include "raylib.h"


//Window Dimensions
const int WINDOW_DIMENSION[2]{ 384, 384 };



int main()
{
	InitWindow( WINDOW_DIMENSION[0], WINDOW_DIMENSION[1], "Hawlerak Clash" );

	//Textures
	Texture2D map = LoadTexture("nature_tileset/MapWorld.png");
	Vector2 mapPos{ -map.width * 2 + WINDOW_DIMENSION[0], 0.0};

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		//Drawings
		DrawTextureEx(map, mapPos, 0.0, 2.0, WHITE);

		EndDrawing();
	}
	CloseWindow();
}