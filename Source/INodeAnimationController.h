#pragma once
#include "AniInfo.h"

class Actor;

class IActorNodeController : public ax::Component
{

public:
    std::string_view getName() const { return getOwner()->getName(); }
    Actor* getActor() { return mActor; }
    void RemoveSelfNode();
    Actor* mActor = nullptr;
};

class INodeAnimationController : public IActorNodeController
{
public:
    void Update_CharactorAnimation(float delta);

    
    void ChangeAnimation(ECharName charName, ECharActName actName, ECharDir dir, bool isRepeat = true);
    void ChangeAnimation(AnimInfo* ainfo, bool isRepeat);

    void ChangeAnimationByIndex(ECharName charName, int idx);

   

    int GetCurrentAnimFrameIndex() { return mAnimate->getCurrentFrameIndex(); }

public:
    ECharDir CalcAniDir(Vec2 dir);

    AnimInfo* mCurrentAnimInfo = nullptr;
    ECharName mAniCharName     = ECharName::None;
    ax::Animate* mAnimate      = nullptr;
};
