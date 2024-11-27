#include "pch.h"
#include "WeaponComp.h"
#include "MovementComp.h"
#include "Actor.h"
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
    for (Weapon* act : mWeaponList)
    {

    }
    //자기가 갖고있는 웨펀리스트vector
    //각자 업데이트 올림
    //각자 필요한 블릿(탄창) 생성 및 발사
}

void WeaponComp::MessageProc(ActorMessage& msg) {}
