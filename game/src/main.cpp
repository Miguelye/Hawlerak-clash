#include "raylib.h"
#include "raymath.h"


//Window Dimensions
const int WINDOW_DIMENSION[2]{ 384, 384 };

void UpdatePosition(Vector2&, Vector2&, float, const float dT);

int main()
{
	InitWindow( WINDOW_DIMENSION[0], WINDOW_DIMENSION[1], "Hawlerak Clash" );

	//Forces
	float velocity = 4.0;

	//Textures
	Texture2D map = LoadTexture("nature_tileset/MapWorld.png");
	Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");

	//Positions
	Vector2 mapPos{	
		(-map.width * 2) + WINDOW_DIMENSION[0],
		(0.0) }; //SelfNote: is negative widh becuase the image is the one that moves not the window, and time 2 'cause map is scaled by 2.
	Vector2 knigthPos{
		(WINDOW_DIMENSION[0] / 2.0) - 4.0 * (0.5 * knight.width / 6.0),
		(WINDOW_DIMENSION[1] / 2.0) - 4.0 * (0.5 * knight.height)
	};

	//animation variables
	float rightLeft = 1; //1 = right, -1 = left
	float runningTime = 0;
	int frame = 0;
	const int MAXFRAME = 6;
	const float UPDATETIME = 1.0/ 12.0;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		const float dT = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);


		Vector2 direction{ 0.0, 0.0 };
		if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
		{
			direction.y += 1.0;
		}

		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
		{
			direction.y -= 1.0;
		}

		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
		{
			direction.x -= 1.0;
		}

		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
		{
			direction.x += 1.0;
		}

		if (Vector2Length(direction) != 0)
		{
			knight = knightRun;
			UpdatePosition(mapPos, direction, velocity, dT);
			//Update right or left
			direction.x < 0.0 ? rightLeft = -1 : rightLeft = 1;
		}
		else
		{
			knight = knightIdle;
		}

		//Animations
		runningTime += dT;
		if (runningTime >= UPDATETIME)
		{
			frame++;
			runningTime = 0;
			if (frame > MAXFRAME)
			{
				frame = 0;
			}
		}

		//Drawings
		//Maps
		DrawTextureEx(map, mapPos, 0.0, 2.0, WHITE);
		//Character
		Rectangle source{frame * (knight.width / 6), 0.0, rightLeft * knight.width / 6, knight.height };
		Rectangle dest{ knigthPos.x, knigthPos.y, 4.0 * knight.width / 6.0, 4.0 * knight.height };
		DrawTexturePro(knight, source, dest, Vector2{}, 0.0, WHITE);

		EndDrawing();
	}
	CloseWindow();
}

void UpdatePosition(Vector2& data, Vector2& direction, float velocity, const float dT)
{
	data = Vector2Subtract(data, Vector2Scale(Vector2Normalize(direction), velocity));
}