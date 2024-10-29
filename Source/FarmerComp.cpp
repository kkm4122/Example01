#include "pch.h"
#include "UnitComp.h"
#include "Actor.h"
#include "FarmerComp.h"
//#include "GoalComp.h"
#include "ActorMessage.h"
//#include "SkeletonComp.h"

const std::string FarmerComp::COMPONENT_NAME = "FarmerComp";

FarmerComp::FarmerComp(Actor* actor) : UnitComp(actor)
{
    mCompName        = COMPONENT_NAME;
    actor->mUnitComp = this;

    mFarmerStatusInfo     = CreateStatusInfo(actor->mActorType);    //farmer의 기본스탯
    Nodedata* nodedata    = mActor->mSceneComp->getRootNodedata();
    nodedata->mStatusInfo = mFarmerStatusInfo;
}

FarmerComp::~FarmerComp() {}
