#include "Weapon_Gun.h"
#include "Actor.h"
#include "Aniinfo.h"
#include "SceneComp.h"
//#include ""
Weapon_Gun::Weapon_Gun(Actor* actor) : Weapon(actor)
{
    ASps    = 3.f;
    mLength = 300;
    mMode   = AimMode::MOUSE_POS;
    mTimes  = 7;
}
void Weapon_Gun::update(float delta)
{
    dealay += delta;
    float a = 1.f / ASps;
    if (dealay >= a)
    {
        dealay = 0;
        if (setAim())
        {
            Attack();
        }
    }
}

void Weapon_Gun::Attack()
{
    Vec2 target;
    float x = M_PI / 180 * 3;
    float currenttimes = 0;
    float a            = 1;
    if (mTimes % 2 == 0)
    {
        currenttimes += x;
    }
    for (int i = 0; i < mTimes; i++)
    {
        a = i * (-1 + (((i + 1) % 2) * 2));
        currenttimes += x * 2 * a;
        target      = mAiming.rotateByAngle(mActor->mPosition, currenttimes);
        auto bullet = Spawn_Bullet(mActor->mSceneComp->mRootNode->getParent(), mActor->getPosition(), mActor, target);
    }
}
