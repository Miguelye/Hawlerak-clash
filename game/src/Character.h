#pragma once

#include "BaseCharacter.h"


class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    void setWorldPos(Vector2 position);
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
private:
    int winWidth{};
    int winHeight{};
    Texture2D weapon{ LoadTexture("characters/weapon_sword.png") };
    Rectangle weaponCollisionRec{};
    float health{ 100.f };
};