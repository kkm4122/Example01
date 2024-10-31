#pragma once
#include "pch.h"
#include "FarmerCharactorNode.h"
#include "Actor.h"
#include "MovementComp.h"
//#include "MealFarmC.h"
#include "UnitComp.h"
#include "SceneComp.h"

using namespace ax;

const std::string FarmerCharactorNode::COMPONENT_NAME = "FarmerCharactorNode";

FarmerCharactorNode* FarmerCharactorNode::create(Actor* ac)
{
    auto body    = new (std::nothrow) FarmerCharactorNode();
    body->mActor = ac;

    if (body->init())
    {
        body->autorelease();
        return body;
    }

    AX_SAFE_DELETE(body);
    return nullptr;
}

bool FarmerCharactorNode::init()
{
    auto node = mActor->mSceneComp->NewAnimNode("Body", ECharName::Farmer, ECharActName::Idle, ECharDir::Face, this);
    mActor->mSceneComp->addChild(node);

    mUnitPose = E_UnitPose::Idle;

    return true;
}

void FarmerCharactorNode::update(float delta)
{
    ECharDir dir = mCurrentAnimInfo->dir;

    // 현재 움직이는 상태라면
    if (mActor->mUnitComp->mUnitPose == E_UnitPose::Move)
    {
        // 이동이 정지한거 아닌지 검사한다.
        Vec2 dirV = mActor->mMoveComp->mCurrentFrameMovement;
        if (dirV.length() < 0.01f)
        {
            // 정지했다.
            // Pose가 바뀌었다.
            mActor->mUnitComp->mUnitPose = E_UnitPose::Idle;
        }
        else
        {
            dir = CalcAniDir(mActor->mMoveComp->getVelocity());
        }
    }

    if (mActor->mUnitComp->mUnitPose == mUnitPose && dir == mCurrentAnimInfo->dir)
        return;

    ECharName charactorName = mCurrentAnimInfo->charName;
    ECharActName actionName = mCurrentAnimInfo->actionName;

    if (mActor->mMoveComp)
        dir = CalcAniDir(mActor->mMoveComp->getVelocity());

    switch (mActor->mUnitComp->mUnitPose)
    {
    case E_UnitPose::Idle:
        ChangeAnimation(charactorName, ECharActName::Idle, mCurrentAnimInfo->dir);
        break;
    case E_UnitPose::Move:
        ChangeAnimation(charactorName, ECharActName::Move, dir);
        break;
    case E_UnitPose::Attack:
        ChangeAnimation(charactorName, ECharActName::Attack, dir);
        break;
    case E_UnitPose::Damaged:
        ChangeAnimation(charactorName, ECharActName::Damaged, dir);
        break;
    case E_UnitPose::Watering:
        ChangeAnimation(charactorName, ECharActName::Watering, dir);
        break;
    case E_UnitPose::Die:
        ChangeAnimation(charactorName, ECharActName::Die, dir);
        break;
    }

    mUnitPose = mActor->mUnitComp->mUnitPose;
}
