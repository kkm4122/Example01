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

    // auto target
    // 피직스 바디(사거리)
    // 컨텍트 이벤트에서 사거리에 들어오면 충돌감지 온 오프로 에너미 리스트에 추가
    //최신 조준은 에너미중 dir length길이 계산후 가장 짧은친구 에이밍타겟 설정
    for (Weapon* weapon : mWeaponList)
    {
        weapon->update(delta);
    }
     //   testGun->update(delta);
    //자기가 갖고있는 웨펀리스트vector
    //각자 업데이트 올림
    //각자 필요한 블릿(탄창) 생성 및 발사
}

void WeaponComp::MessageProc(ActorMessage& msg) {}

void WeaponComp::shot()
{
    for (Weapon* weapon : mWeaponList)
    {
        if (weapon->mMode == AimMode::NEAR_E)
        {
            weapon->mMode = AimMode::MOUSE_POS;
        }
        else
        {
            weapon->mMode = AimMode::NEAR_E;
        }
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
