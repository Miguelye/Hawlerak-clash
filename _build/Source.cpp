#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    texture = LoadTexture("characters/knight_idle_spritesheet.png");
    idle = LoadTexture("characters/knight_idle_spritesheet.png");
    run = LoadTexture("characters/knight_run_spritesheet.png");
        width = texture.width / maxFrames;
    height = texture.height;
    scaleSize = 4.0f;
    screenCenterPos = screenPos = { static_cast<float>(winWidth) / 2.0f - scaleSize * (0.5f * width),
                                    static_cast<float>(winHeight) / 2.0f - scaleSize * (0.5f * height) };
}

void Character::setWorldPos(Vector2 position)
{
    worldPos = position;
}

void Character::tick(float deltaTime)
{

    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    worldPosLastFrame = worldPos;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    
    BaseCharacter::tick(deltaTime);
}