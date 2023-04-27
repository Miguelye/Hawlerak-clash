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
    if (!getAlive()) { return; }
    //Get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    if (Vector2Length(velocity) < radius)
    {
        velocity = {};
    }

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(dps * deltaTime);
    }

    BaseCharacter::tick(deltaTime);
}

void Enemy::setTarget(Character* target)
{
    this->target = target;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}