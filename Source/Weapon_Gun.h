#pragma once

#include "Weapon.h"

class Weapon_Gun : public Weapon
{
public:
    Weapon_Gun(Actor* actor);
    virtual void update(float delta) override;
    virtual void Attack() override;
    //1초에 1.5번 때림
    //2초에 3번
    //1/1.5=0.666666;

    float bulletspeed=3.5;
};
