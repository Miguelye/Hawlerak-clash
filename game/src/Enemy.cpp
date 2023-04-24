#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture)
{
    worldPos = pos;
    texture = idleTexture;
    idle = idleTexture;
    run = runTexture;
    width = texture.width / maxFrames;
    height = texture.height;
    scaleSize = 4.0f;
}

void Enemy::tick(float deltaTime)
{
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);
}

void Enemy::setTarget(Character* target)
{
    this->target = target;
}