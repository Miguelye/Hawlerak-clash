#pragma once

#include "BaseCharacter.h"


class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    void setWorldPos(Vector2 position);
    Vector2 getScreenPos();
private:

};