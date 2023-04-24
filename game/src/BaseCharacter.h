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
protected:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos{};
    Vector2 screenCenterPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 : facing right, -1 : facing left
    float rightLeft{ 1.f };
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{ 6 };
    const float updateTime{ 1.f / 12.f };
    const float speed{ 4.f };
    //drawing variables
    float width;
    float height;
    float scaleSize;
};
