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
    screenPos = { static_cast<float>(winWidth) / 2.0f - scaleSize * (0.5f * width),
                  static_cast<float>(winHeight) / 2.0f - scaleSize * (0.5f * height) };
}

void Character::setWorldPos(Vector2 position)
{
    worldPos = position;
}

Vector2 Character::getScreenPos()
{
    return screenPos;
}

void Character::tick(float deltaTime)
{

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);
}