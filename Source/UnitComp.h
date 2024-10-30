#pragma once
#include "IActorComponent.h"
#include "INodeAnimationController.h"

class Actor;

enum class Team
{
    Player,
    Enemy,
};

enum class E_UnitPose
{
    None,
    Idle,
    Move,
    Attack,
    Damaged,
    Watering,
    Die,
    Pos_Count
};

class UnitComp : public IActorComponent
{
public:
    UnitComp(Actor* actor);
    virtual void Attack() = 0;

    Team unitTeam        = Team::Player;
    E_UnitPose mUnitPose = E_UnitPose::None;

    INodeAnimationController* mCharAnimController = nullptr;
    //유닛이 가지고 있는 애니메이션ff

    std::string_view getPoseName()
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
};
