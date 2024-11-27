#include "pch.h"
#include "UnitComp.h"
#include "Actor.h"

UnitComp::UnitComp(Actor* actor) : IActorComponent(actor)
{
    SAFE_DELETE(actor->mUnitComp);
    actor->mUnitComp = this;
}

std::string_view UnitComp::getPoseName()
{
    switch (mUnitPose)
    {
    case E_UnitPose::None:
        return "None";
    case E_UnitPose::Idle:
        return "Idle";
    case E_UnitPose::Move:
        return "Move";
    case E_UnitPose::Attack:
        return "Attack";
    case E_UnitPose::Die:
        return "Die";
    case E_UnitPose::Pos_Count:
        return "Pos_Count";
    }
    return "None00";
}

//projecttile component를 가지고 있다.
