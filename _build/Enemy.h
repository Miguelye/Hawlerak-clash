#pragma once

#include "BaseCharacter.h"
#include "raylib.h"

class Enemy : public BaseCharacter
{
public:
	Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    virtual void tick(float deltaTime) override;

private:

};



