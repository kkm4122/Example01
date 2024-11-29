#include "pch.h"
#include "WeaponComp.h"
#include "MovementComp.h"
#include "Actor.h"
#include "Weapon.h"
#include "Weapon_Gun.h"
#include "ActorMessage.h"
#include "UnitComp.h"
const std::string WeaponComp::COMPONENT_NAME = "WeaponComp";

WeaponComp::WeaponComp(Actor* actor) : IActorComponent(actor)
{
    mCompName        = COMPONENT_NAME;
    actor->mWeaponComp = this;
}

WeaponComp::~WeaponComp() {}

void WeaponComp::update(float delta)
{
    /*for (Weapon* weapon : mWeaponList)
    {
    }*/
        testGun->update(delta);
    //자기가 갖고있는 웨펀리스트vector
    //각자 업데이트 올림
    //각자 필요한 블릿(탄창) 생성 및 발사
}

void WeaponComp::MessageProc(ActorMessage& msg) {}

void WeaponComp::shot()
{
    if (testGun)
    {
        testGun->Attack();
    }
}

void WeaponComp::addGun()
{
    auto gun = new Weapon_Gun(mActor);
    Vec2 Pos(mActor->getPosition());
    Pos.x += 200;
    gun->mAiming=Pos;
    mWeaponList.push_back(gun);
    testGun = new Weapon_Gun(mActor);
    testGun->mAiming = Pos;
}
