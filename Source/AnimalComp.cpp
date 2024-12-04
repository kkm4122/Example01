#include "pch.h"
#include "AnimalComp.h"
#include "UnitComp.h"
#include "Actor.h"
#include "ActorMessage.h"
//#include "FarmerComp.h"
//#include "GoalComp.h"
//#include "SkeletonComp.h"

const std::string AnimalComp::COMPONENT_NAME = "AnimalComp";

AnimalComp::AnimalComp(Actor* actor) : UnitComp(actor)
{
    mCompName        = COMPONENT_NAME;
    actor->mUnitComp = this;

    mAnimalStatusInfo     = CreateStatusInfo(actor->mActorType);  // farmer의 기본스탯
    Nodedata* nodedata    = mActor->mSceneComp->getRootNodedata();
    nodedata->mStatusInfo = mAnimalStatusInfo;
}

AnimalComp::~AnimalComp() {}

void AnimalComp::update(float delta) {}

void AnimalComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case ActorMessage::Contacted:

        break;
    default:
        break;
    }
}

void AnimalComp::Attack() {}
