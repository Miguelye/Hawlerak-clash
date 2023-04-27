#pragma once

#include "raylib.h"

class BaseCharacter
{
public:
	BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void UndoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
    void setSpeed(float speed) { this->speed = speed; }
protected:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};
    // 1 : facing right, -1 : facing left
    float rightLeft{ 1.f };
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{ 6 };
    const float updateTime{ 1.f / 12.f };
    float speed{ 4.f };
    //drawing variables
    float width;
    float height;
    float scaleSize;
    bool alive = true;
};
