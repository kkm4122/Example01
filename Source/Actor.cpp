#include "pch.h"
#include "Actor.h"
#include "SceneComp.h"
#include "MovementComp.h"
#include "InputKeyComp.h"
#include "GoalComp.h"
#include "WeaponComp.h"
#include "UnitComp.h"
const char* getActorTypeName(ActorType type)
{
    switch (type)
    {
    case ActorType::Mouse:
        return "None";
    case ActorType::Farmer:
        return "Farmer";
    case ActorType::Soldier:
        return "Soldier";
    case ActorType::TownHall:
        return "TownHall";
    case ActorType::Torch:
        return "Torch";
    case ActorType::Ball:
        return "Ball";
    case ActorType::Skeleton:
        return "Skeleton";
    case ActorType::CropsGround:
        return "CropsGround";
    case ActorType::Cow:
        return "Cow";
    }
    return "None";
}

Actor::Actor()
{
   // currentAni = &info;
}

Actor::~Actor()
{
    if (mSceneComp)
        delete mSceneComp;

    if (mMoveComp)
        delete mMoveComp;

    if (mUnitComp)
        delete mUnitComp;

    if (mGoalComp)
        delete mGoalComp;

    if (mInputComp)
        delete mInputComp;
    if (mWeaponComp)
        delete mWeaponComp;
}

void Actor::update(float delta)
{
    //좌표 최신화(이동)
    //update_world(delta);
    if (mStatus == E_Died)
    {
        return;
    }
    if (mInputComp)
        mInputComp->update(delta);
    if (mGoalComp)
        mGoalComp->update(delta);
    if (mUnitComp)
        mUnitComp->update(delta);
    if (mMoveComp)
        mMoveComp->update(delta);
    
    if (mWeaponComp)
        mWeaponComp->update(delta);
    
    if (currentHP > MaxHP)
    {
        currentHP = MaxHP;
    }
    else if (currentHP < 0)
    {
        currentHP = 0;
    }
    //변경한 데이터값을 화면에 최신화
    if (mSceneComp)
        mSceneComp->update(delta);
}


