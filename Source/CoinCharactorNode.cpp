#pragma once
#include "pch.h"
#include "CoinCharactorNode.h"
#include "Actor.h"
#include "MovementComp.h"
//#include "MealFarmC.h"
#include "UnitComp.h"
#include "SceneComp.h"
using namespace ax;

const std::string CoinCharactorNode::COMPONENT_NAME = "CoinCharactorNode";

CoinCharactorNode* CoinCharactorNode::create(Actor* ac)
{
    auto body    = new (std::nothrow) CoinCharactorNode();
    body->mActor = ac;

    if (body->init())
    {
        body->autorelease();
        return body;
    }

    AX_SAFE_DELETE(body);
    return nullptr;
}

bool CoinCharactorNode::init()
{
    auto node = mActor->mSceneComp->NewAnimNode("Body", ECharName::Coin, ECharActName::Move, ECharDir::Face, this);
    mActor->mSceneComp->addChild(node);

    mUnitPose = E_UnitPose::Move;

    return true;
}

void CoinCharactorNode::update(float delta) {}

ECharDir CoinCharactorNode::CalcAniDir(Vec2 dir)
{
    return ECharDir();
}
