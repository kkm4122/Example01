#pragma once

#include "preDefines.h"
#include "Aniinfo.h"
#include "ActorType.h"

//노드에서 컴포넌트를 상속받아서 장착할수있음
//컴포넌트 상속받으면

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
    enum
    {//엑터 상태
        E_Died,
        E_Active,
        E_InActive,
    } mStatus=E_Active;
    Actor();
    ~Actor();
    // 에니메이션 및 스프라이트
    void update(float delta);

    //~~ Property ~~~~~~~~~~~~~~~~~~
    ax::Point getPosition() { return mPosition; }
    void setPosition(ax::Vec2 v1) { mPosition = v1; }
    const char* getActorTypeStr() { return getActorTypeName(mActorType); }
    // Actor 정보

    unsigned int mActorID = UINT32_MAX;
    std::string mActorName;
    std::string mTag;
    std::string mMapName;
    ActorType mActorType = ActorType::None;
    
    ax::Rect visibleRect;
    int MaxHP     = 200;
    int currentHP = 100;
    int getMax() const { return MaxHP; }
    int getCur() const { return currentHP; }

public:// 컴포넌트
    SceneComp* mSceneComp = nullptr;
    MovementComp* mMoveComp = nullptr;//좌표이동계
    UnitComp* mUnitComp     = nullptr;
    GoalComp* mGoalComp     = nullptr;
    InputKeyComp* mInputComp = nullptr;
    WeaponComp* mWeaponComp  = nullptr;
    // 좌표 이동계
    ax::Vec2 mPosition;
    Vec2 mTarget;

  
    
    float mTimer=0;




    /**********************************************************************/
    //AnimInfo& info;
    //AnimInfo* currentAni = nullptr;

    
};
