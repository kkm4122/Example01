#pragma once
#include "IActorComponent.h"
#include "INodeAnimationController.h"
#include "UnitDefines.h"
class Actor;

struct
{
    int Lv;
    float MaxHP;
    float CurHP;
    float MaxExp;
    float CurExp;
    float Speed=10.f;
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

    std::string_view getPoseName();
    
};
