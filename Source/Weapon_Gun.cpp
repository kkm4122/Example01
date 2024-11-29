#include "Weapon_Gun.h"
#include "Actor.h"
#include "Aniinfo.h"
#include "SceneComp.h"
//#include ""
Weapon_Gun::Weapon_Gun(Actor* actor) : Weapon(actor)
{
    ASps = 3.f;
}
void Weapon_Gun::update(float delta)
{
    dealay += delta;
    float a = 1.f / ASps;
    if (dealay >= a)
    {
        dealay = 0;
        Attack();
    }
}

void Weapon_Gun::Attack()
{
    
    auto bullet = Spawn_Bullet(mActor->mSceneComp->mRootNode->getParent(), mActor->getPosition(), mActor, mAiming);
}
