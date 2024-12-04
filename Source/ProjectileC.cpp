#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "World.h"
#include "ProjectileC.h"
#include "MovementComp.h"
#include "SceneComp.h"
#include "NoChangeAnimController.h"

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

void ProjectileC::Attack() {}

void ProjectileC::PlayExplosion()
{
    //mActor->mMoveComp->isEnabled = false;
    Vec2 vel = mActor->mSceneComp->mRootNode->getPhysicsBody()->getVelocity();
    mActor->mSceneComp->mRootNode->getPhysicsBody()->setVelocity(vel * 0);
    mActor->mSceneComp->mRootNode->getPhysicsBody()->setDynamic(false);
    mActor->mSceneComp->mRootNode->getPhysicsBody()->setContactTestBitmask(false);
    mActor->mSceneComp->mRootNode->getPhysicsBody()->setCollisionBitmask(false);
    //
    // 폭발 animation 으로  바꾸기
    //
    // mAnimController->ChangeAnimation(ECharName::Explosion, ECharActName::Attack, ECharDir::Left);
    mAnimController->RemoveSelfNode();

    mAnimController = mActor->mSceneComp->CreateNode_withNoChangeAnimController("Body", ECharName::Explosion,
                                                                                ECharActName::Attack, ECharDir::Left);

    mMode = E_Explosion;
}

void ProjectileC::Damage처리하라(Actor* other) {}

void ProjectileC::Start(float delta)
{
    //mActor->mMoveComp->mSpeed = 300.f;
    //mActor->mMoveComp->setTarget(mTargetPos);
    mTargetPos -= mActor->getPosition();
    mTargetPos.normalize();
    mActor->mSceneComp->mRootNode->getPhysicsBody()->setVelocity(mTargetPos*500);
   //mActor->mSceneComp->mRootNode->getPhysicsBody()->applyForce(Vec2(100,100));
    mMode = E_Flying;
}

void ProjectileC::ExplosionUpdate(float delta)
{
    Vec2 vel = mActor->mSceneComp->mRootNode->getPhysicsBody()->getVelocity();
    mActor->mSceneComp->mRootNode->getPhysicsBody()->setVelocity(vel * 0);
    int idx = mAnimController->GetCurrentAnimFrameIndex();
    if (idx == 9)
        mMode = E_End;
}

void ProjectileC::FlyingUpdate(float delta)
{
    Vec2 vel = mActor->mSceneComp->mRootNode->getPhysicsBody()->getVelocity();
    vel.normalize();
    mActor->mSceneComp->mRootNode->getPhysicsBody()->setVelocity(vel * 500);
    if (3.f < timer)
    {
        mActor->mSceneComp->mRootNode->getPhysicsBody()->setVelocity(vel*0);
        PlayExplosion();
    }
}

void ProjectileC::End(float delta)
{
   // mActor->mStatus = Actor::E_Died;
    //mActor->mSceneComp->mRootNode->setVisible(false);
    World::get()->EraseBullet(mActor);
}
