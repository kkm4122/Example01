#pragma once

#include "preDefines.h"
#pragma once
#include "ActorType.h"

enum class WeaponType
{
    Gun,
    Bow
};
enum class AimMode
{
    NEAR_E,
    FAR_E,
    MOUSE_POS
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
    AimMode mMode = AimMode::NEAR_E;
    float ASps=1.0f;//AttackSpeed per secondw
    float dealay = 0;
    float mLength;
    float TL = -1;
    bool setAim();
};
