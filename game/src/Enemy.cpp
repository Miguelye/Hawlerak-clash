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
    speed = 2.0f;
}

void Enemy::tick(float deltaTime)
{
    //Get toTarget
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    // Normalize toTarget
    toTarget = Vector2Normalize(toTarget);
    //multiply target by speed
    toTarget = Vector2Scale(toTarget, speed);
    //move the enemy
    worldPos = Vector2Add(worldPos, toTarget);
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);
}

void Enemy::setTarget(Character* target)
{
    this->target = target;
}