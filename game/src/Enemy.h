#pragma once

#include "BaseCharacter.h"
#include "raylib.h"
#include "Character.h"
class Enemy : public BaseCharacter
{
public:
	Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    virtual void tick(float deltaTime) override;
	void setTarget(Character* target);
	virtual Vector2 getScreenPos() override;
private:
	Character* target;
	float dps{ 10.f };
	float radius{ 25.f };
};



