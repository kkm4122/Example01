#include "pch.h"
#include "Actor.h"
#include "IActorComponent.h"
#include "ActorMessage.h"
#include "World.h"
//#include "ProjectileComp.h"
#include "FarmerComp.h"
//#include "SkeletonComp.h"
#include "MovementComp.h"
//#include "GoalComp.h"

void SendAcotrMessage(Actor* r, ActorMessage msg)
{

    switch (msg.msgType)
    {
    case ActorMessage::MoveToTarget:
    {
        // AMsgData_Vec2* v = (AMsgData_Vec2*)msg.data;
        // r->mMoveComp->MessageProc(ActorMessage::MoveToTarget);
    }
    break;
    }
    /*}
    case ActorMessage::AddToNextTarget:
    {
        AMsgData_Vec2* v = (AMsgData_Vec2*)msg.data;
        PushGoal_GotoTarget(r, v->pos);
        // if (r->mMoveComp) r->mMoveComp->PushTargetList(v->pos);
    }
    break;

    case ActorMessage::Contacted:
    {
        AXLOG("충돌");
        // if (r->mUnitComp && r->mUnitComp->getName() == ProjectileComp::COMPONENT_NAME)
        // r->mUnitComp->MessageProc(msg);
        if (r->mFarmerComp)
            r->mFarmerComp->MessageProc(msg);
        if (r->mSkeletonComp)
            r->mSkeletonComp->MessageProc(msg);
    }
    break;

    default:
        break;
    }
    */
    // 자동 삭제해야 할까?
    // if (msg.data)
    //    delete msg.data;
}
