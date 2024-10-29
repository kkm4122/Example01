#pragma once
#include "IActorComponent.h"
#include "Actor.h"

class MovementComp : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;

    bool IsTargetForce = false;

public:
    MovementComp(Actor* actor);
    ~MovementComp();

    void update(float delta);


    void Do_TargetForce();
   
    ax::Vec2 Vec2DNormalized(ax::Vec2 target);
    double length(ax::Vec2 v1, ax::Vec2 v2);

    
    //타겟 관련 함수
    bool IsArrived();
    void setTarget(ax::Vec2 target);
    void SetTargetList(std::list<Vec2>& list);
    void PushTargetList(Vec2 v1);
    void CheckTargetList();

    double getSpeed() const { return mSpeed; }
    ax::Vec2 getVelocity() { return mVelocity; }

public:
    float mSpeed     = 50.f;
    double m경과시간 = -1.0;
    ax::Vec2 mCurrentFrameMovement;

public:
    void _setTarget(ax::Vec2 target);

    ax::Vec2 mWorldTargetPos;
    ax::Vec2 mVelocity;
    std::list<Vec2> mTargetList;
};
