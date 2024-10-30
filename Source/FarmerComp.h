#pragma once
#include "UnitComp.h"
#include "SceneComp.h"


class FarmerComp : public UnitComp
{
public:
    const static std::string COMPONENT_NAME;

    FarmerComp(Actor* actor);
    ~FarmerComp();

public:
    virtual void update(float delta) override;              //아직은 기능을 넣을 함수불필요
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void Attack() override;
    INodeAnimationController* mItemController       = nullptr;
    INodeAnimationController* mSelectController     = nullptr;
    INodeAnimationController* mCharHPAnimController = nullptr;
    Nodedata* mTargetData                           = nullptr;  //대상이 있으면 상황에 맞게 행동하기위한 포인터

public:
    bool isDamaged = false;
    StatusInfo* mFarmerStatusInfo;
    float mTimer = 0;
};
