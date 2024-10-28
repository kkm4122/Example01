#include "Actor.h"
#include "SceneComp.h"

Actor::Actor()
    : info(FindAnimInfo(ECharActName::Idle, ECharDir::Face))
{
    currentAni = &info;
}

Actor::~Actor() {}

void Actor::update_world(float delta)
{
    
    Velocity = ax::Vec2(0, 0);
    if (IsTargetForce)
    {
        Do_TargetForce();
    }
    Velocity.normalize();
    Vec2 moveDir = (Velocity * delta * mspeed);
    mPosition += moveDir;

    if(mSceneComp)
        mSceneComp->update_world(delta);
    if (currentHP > MaxHP)
    {
        currentHP = MaxHP;
    }
    else if (currentHP < 0)
    {
        currentHP = 0;
    }
    mTimer += delta;
    if (mTimer > 1.0f)
    {
        mTimer = 0;
        AXLOG("posx %f , posy %f",mPosition.x,mPosition.y);
    }
    mSceneComp->mRootNode->setPosition(mPosition);
}

void Actor::setTarget(ax::Vec2 target)
{
    IsTargetForce   = true;
    mtargetDir      = target - mPosition;
    mWorldTargetPos = target;
}

ax::Vec2 Actor::Vec2DNormalized(ax::Vec2 target)
{
    ax::Vec2 vec = target;

    double vector_length = vec.length();

    if (vector_length > 2)
    {
        vec.x /= vector_length;
        vec.y /= vector_length;
    }

    return vec;
}

bool Actor::IsArrived()
{
    if (1.0 > length(mWorldTargetPos, mPosition))
    {
        // mActor->mBehavior = Idle;
        return true;
    }
    return false;
}

void Actor::Do_TargetForce()
{
    if (IsArrived())
    {
        IsTargetForce = false;
    }
    else
        Velocity += Vec2DNormalized(mtargetDir);
}

double Actor::length(ax::Vec2 v1, ax::Vec2 v2)
{
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;

    return sqrt(dx * dx + dy * dy);
}
