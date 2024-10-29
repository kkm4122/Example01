#pragma once

#include "preDefines.h"
#include "Aniinfo.h"


//노드에서 컴포넌트를 상속받아서 장착할수있음
//컴포넌트 상속받으면
enum class ActorType : UINT8
{
    None,
    Mouse,
    Farmer,
    Soldier,
    TownHall,
    Torch,
    Ball,
    Skeleton,
    Animal,

    Ores,
    Farm,
    Tree,

};

enum
{
    Idle = 1,
    Move,
    Attack,
    Watering,
    behavior_Count
};

class Actor
{
public:
    Actor();
    ~Actor();
    // 에니메이션 및 스프라이트

    // Actor 정보
    unsigned int mActorID = 0;
    std::string mActorName;
    std::string mTag;
    std::string mMapName;
    ActorType mActorType = ActorType::None;

    int MaxHP     = 200;
    int currentHP = 100;
    int getMax() const { return MaxHP; }
    int getCur() const { return currentHP; }

    // 컴포넌트
    SceneComp* mSceneComp = nullptr;
    MovementComp* mMoveComp = nullptr;

public:
    // 좌표 이동계
    ax::Vec2 mPosition;
    ax::Vec2 mtargetDir = ax::Vec2(200, 200);
    ax::Vec2 Velocity;
    bool IsTargetForce = false;
    double mspeed      = 50.f;
    ax::Vec2 mWorldTargetPos;
    Vec2 mTarget;
    
    float mTimer=0;

    ax::Vec2 Vec2DNormalized(ax::Vec2 target);
    void setTarget(ax::Vec2 target);
    bool IsArrived();
    void Do_TargetForce();
    double length(ax::Vec2 v1, ax::Vec2 v2);

    double getSpeed() const { return mspeed; }

    void update(float delta);

    void update_world(float delta);  // SceneUPdate comp호출

    /**********************************************************************/
    AnimInfo& info;
    AnimInfo* currentAni = nullptr;

    ax::Point getPosition() const { return mPosition; }
    void setPosition(ax::Vec2 v1) { mPosition = v1; }
};
