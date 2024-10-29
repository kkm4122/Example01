#include "pch.h"
#include "Actor.h"
#include "SceneComp.h"
#include "MovementComp.h"
Actor::Actor()
    : info(FindAnimInfo(ECharActName::Idle, ECharDir::Face))
{
    currentAni = &info;
}

Actor::~Actor() {}

void Actor::update(float delta)
{
    //좌표 최신화(이동)
    //update_world(delta);
    if (mMoveComp)
        mMoveComp->update(delta);


    if (currentHP > MaxHP)
    {
        currentHP = MaxHP;
    }
    else if (currentHP < 0)
    {
        currentHP = 0;
    }
    //변경한 데이터값을 화면에 최신화
    if (mSceneComp)
        mSceneComp->update(delta);
}

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

    
    
    
}

void Actor::setTarget(ax::Vec2 target)
{
    mMoveComp->setTarget(target);
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
