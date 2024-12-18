#pragma once

#include "Weapon.h"

class Weapon_Gun : public Weapon
{
public:
    Weapon_Gun(Actor* actor);
    virtual void update(float delta) override;
    virtual void Attack() override;
    
    float bulletspeed=3.5;
};

class Weapon_Gun2 : public Weapon
{
public:
    Weapon_Gun2(Actor* actor);
    virtual void update(float delta) override;
    virtual void Attack() override;

    float bulletspeed = 3.5;
};
