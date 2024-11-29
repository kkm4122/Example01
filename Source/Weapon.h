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

    virtual void update(float delta)
    {
        
    }
    virtual void Attack() {}
    Actor* mActor;
    Vec2 mAiming;
    
    float ASps=1.0f;//AttackSpeed per secondw
    float dealay = 0;
};
