#include "SmartPtr.h"
#include "animController.h"
#include "SceneComp.h"
#include "Aniinfo.h"
#include "Actor.h"
#include "MovementComp.h"
animController* animController::create(Actor* ac)
{
    animController* body = new (std::nothrow) animController();
    body->mActor      = ac;
    if (body->init())
    {
        body->autorelease();
        return body;
    }

    AX_SAFE_DELETE(body);
    return nullptr;
}

animController::animController()
{

    
}

animController::~animController() {}

void animController::update(float delta)
{
    update_animChar(delta);
}
void animController::update_animChar(float delta)
{
    Vec2 dirV = mActor->mMoveComp->mCurrentFrameMovement;
    //Vec2 dirV = mActor->mMoveComp->mWorldTargetPos - mActor->mPosition;
    // getOwner()->getParent()->getPosition();
    if (!mActor->mMoveComp->IsArrived())
    {
        // float a      = dirV.length();
        ECharDir dir = CalcAniDir(dirV);
        if (dir != mActor->currentAni->dir || mActor->currentAni->actionName != ECharActName::Move)
        {
            AnimInfo& info                 = FindAnimInfo(ECharActName::Move, dir);
            mActor->currentAni             = &info;
            mActor->currentAni->dir        = dir;
            mActor->currentAni->actionName = ECharActName::Move;
            Change_CharAnim(getOwner(), info);
        }
    }
    else
    {
        if (mActor->currentAni->actionName != ECharActName::Idle)
        {
            AnimInfo& info                 = FindAnimInfo(ECharActName::Idle, mActor->currentAni->dir);
            mActor->currentAni             = &info;
            mActor->currentAni->actionName = ECharActName::Idle;
            Change_CharAnim(getOwner(), info);
        }
    }
    
} /*
void animController::update_animChar1(float delta)
{
    if (mActor->mMoveComp)
    {
        Vec2 dirV = mActor->mMoveComp->mCurrentFrameMovement;

        ECharName charName      = mCurrentAnimInfo->charName;
        ECharActName actionName = mCurrentAnimInfo->actionName;
        ECharDir dir            = mCurrentAnimInfo->dir;
        if (dirV.length() > 0.01f)
        {
            dir        = CalcAniDir(mActor->mMoveComp->getVelocity());
            actionName = ECharActName::Move;
        }
        else
        {
            actionName = ECharActName::Idle;
        }

        // if (dir != mCurrentAnimInfo->dir || mCurrentAnimInfo->actionName != actionName)
        // ChangeAnimation(charName, actionName, dir);
    }
}

*/



/*
    Velocity = ax::Vec2(0, 0);
    if (IsTargetForce)
    {
        Do_TargetForce();
    }
    Velocity.normalize();
    Vec2 Pos = sprite->getPosition() + (Velocity * delta * mspeed);
    sprite->setPosition(Pos);

    Vec2 dirV = sprite->getPosition() - mWorldTargetPos;
    // DirV =이동거리
    //  값이 너무 작을 경우,
    //  앞을 처다보는 현상이 있음.
    if (!IsArrived())
    {
        float a      = dirV.length();
        ECharDir dir = CalcAniDir(-dirV);
        if (dir != currentD || currentS != ECharActName::Move)
        {
            AnimInfo& info = FindAnimInfo(ECharActName::Move, dir);
            currentAni     = &info;
            currentD       = dir;
            currentS       = ECharActName::Move;
            Change_CharAnim(sprite, info);
        }
    }
    else
    {
        if (currentS != ECharActName::Idle)
        {
            AnimInfo& info = FindAnimInfo(ECharActName::Idle, currentD);
            currentAni     = &info;
            currentS       = ECharActName::Idle;
            Change_CharAnim(sprite, info);
        }
    }
*/
