#pragma once

#include "Weapon.h"

class Weapon_Gun : public Weapon
{
public:
    Weapon_Gun(Actor* actor);
    virtual void update(float delta) override;

    float bulletspeed=3.5;
};
