#include "pch.h"
#include "INodeAnimationController.h"
#include "MovementComp.h"
#include "SceneComp.h"
//#include "UnitComp.h"

void IActorNodeController::RemoveSelfNode()
{
    mActor->mSceneComp->RemoveANController(this);
    getOwner()->removeFromParent();
}

void INodeAnimationController::Update_CharactorAnimation(float delta) {// 캐릭터가 바라보고 있는 방향을
    // 위동하려는 위치를 기준으로
    // 변경한다.
    if (mActor->mMoveComp)
    {
        Vec2 dirV = mActor->mMoveComp->mCurrentFrameMovement;

        ECharName charName      = mCurrentAnimInfo->charName;
        ECharActName actionName = mCurrentAnimInfo->actionName;
        ECharDir dir            = mCurrentAnimInfo->dir;

        // 값이 너무 작을 경우,
        // 앞을 처다보는 현상이 있음.
        if (actionName == ECharActName::Idle || actionName == ECharActName::Move)
        {
            if (dirV.length() > 0.01f)
            {
                dir        = CalcAniDir(mActor->mMoveComp->getVelocity());
                actionName = ECharActName::Move;
            }
            else
            {
                actionName = ECharActName::Idle;
            }

            if (dir != mCurrentAnimInfo->dir || mCurrentAnimInfo->actionName != actionName)
                ChangeAnimation(charName, actionName, dir);
        }
    }
}

void INodeAnimationController::ChangeAnimation(ECharName charName, ECharActName actName, ECharDir dir, bool isRepeat) {}

void INodeAnimationController::ChangeAnimation(AnimInfo* ainfo, bool isRepeat)
{
    getOwner()->stopActionByTag(20202);

    ainfo->CreateAnimation();

    Animate* animate = Animate::create(ainfo->animation.get());

    ax::Action* action;
    if (isRepeat)
        action = RepeatForever::create(animate);
    else
        action = Repeat::create(animate, 1);

    action->setTag(20202);
    getOwner()->runAction(action);

    mCurrentAnimInfo = ainfo;
    mAniCharName     = ainfo->charName;
    mAnimate         = animate;
}

void INodeAnimationController::ChangeAnimationByIndex(ECharName charName, int idx) {}

ECharDir INodeAnimationController::CalcAniDir(Vec2 dir)
{
    return ECharDir();
}
