#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    winWidth(winWidth),
    winHeight(winHeight)
{
    texture = LoadTexture("characters/knight_idle_spritesheet.png");
    idle = LoadTexture("characters/knight_idle_spritesheet.png");
    run = LoadTexture("characters/knight_run_spritesheet.png");
    width = texture.width / maxFrames;
    height = texture.height;
    scaleSize = 4.0f;
}

Vector2 Character::getScreenPos()
{
    return Vector2
    {
        static_cast<float>(winWidth) / 2.0f - scaleSize * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scaleSize * (0.5f * height)
    };
}

void Character::setWorldPos(Vector2 position)
{
    worldPos = position;
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    if (!getAlive())
    {
        return;
    }
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);
    

    Vector2 origin{};
    Vector2 offset{};
    float rotation;

    if (rightLeft > 0.f)
    {
        origin = { 0.f, weapon.height * scaleSize };
        offset = { 35.f, 55.f };

        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scaleSize,
            weapon.width * scaleSize,
            weapon.height * scaleSize,
        };

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = { weapon.width * scaleSize, weapon.height * scaleSize };
        offset = { 25.f, 55.f };

        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scaleSize,
            getScreenPos().y + offset.y - weapon.height * scaleSize,
            weapon.width * scaleSize,
            weapon.height * scaleSize,
        };

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }
    

    //Draw Sword
    Rectangle source{ 0.f, 0.f, rightLeft * static_cast <float>(weapon.width), static_cast <float>(weapon.height) };
    Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scaleSize, weapon.height * scaleSize };
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRec.x,
        weaponCollisionRec.y,
        weaponCollisionRec.width,
        weaponCollisionRec.height,
        RED
    );

}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0)
    {
        setAlive(false);
    }
}