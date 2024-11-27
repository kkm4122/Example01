#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "World.h"
#include "ProjectileC.h"
#include "MovementComp.h"
#include "SceneComp.h"
#include "CharAnimController.h"

const std::string ProjectileC::COMPONENT_NAME = "ProjectileC";
ProjectileC::ProjectileC(Actor* actor, Vec2 targetPos)
    : UnitComp(actor), mTargetPos(targetPos), timer(0), mMode(E_Start)
{
    mCompName        = COMPONENT_NAME;
    actor->mUnitComp = this;
}

ProjectileC::~ProjectileC() {}

void ProjectileC::update(float delta)
{
    timer += delta;

    switch (mMode)
    {
    case E_Start:
        Start(delta);
        break;
    case E_Flying:
        FlyingUpdate(delta);
        break;
    case E_Explosion:
        ExplosionUpdate(delta);
        break;
    case E_End:
        End(delta);
        break;
    }
}

void ProjectileC::MessageProc(ActorMessage& msg) {}

void ProjectileC::Start(float delta)
{
    mActor->mMoveComp->mSpeed = 300.f;
    mActor->mMoveComp->setTarget(mTargetPos);

    mMode = E_Flying;
}

void ProjectileC::ExplosionUpdate(float delta) {}

void ProjectileC::FlyingUpdate(float delta) {}

void ProjectileC::End(float delta)
{
    World::get()->EraseActor(mActor);
}
