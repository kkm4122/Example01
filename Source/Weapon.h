#pragma once

#include "preDefines.h"
#pragma once
#include "ActorType.h"

enum class WeaponType
{
    Gun,
    Bow
};
class Weapon
{
public:

    
    Weapon(Actor* actor) : mActor(actor) {}
    virtual ~Weapon() {}

    virtual void update(float delta) {};
    void Shot();
    Actor* mActor;
    float ASps=1.0f;//AttackSpeed per second
};
