#include "pch.h"
#include "World.h"
#include "Actor.h"
#include "MovementComp.h"
//#include "2dGeometryFunc.h"

USING_NS_AX;

namespace
{
static World* g = nullptr;
}


World::World()
{
    auto director = ax::Director::getInstance();
    director->getScheduler()->scheduleUpdate(this, -1, false);//diretor에서 바로 업데이트 호출 ->씬에서 호출안해도댐

}

World::~World()
{
    for (Actor* act : mActorList)
    {
        if (act)
            delete act;
    }
}

World* World::get()
{
    if (!g)
        g = new World;
    return g;
}

void World::destroy()
{
    SAFE_DELETE(g);
}

void World::update(float dt)
{
    if (!mIsRunning)
        return;
    ++mWorldUpdateCount;
    mWorldTime += dt;
    if (mWorldTime > 5.0f)
    {
        AXLOG("초당 %d번 update 호출",mWorldUpdateCount/5);
        mWorldTime = 0;
        mWorldUpdateCount = 0;
    }

    Delete_Actors();
    Delete_Bulletes();
    updateActors(dt);
}

void World::updateActors(float dt)
{
    int i = 0;

    for (Actor* act : mBulletList)
    {
        if (act != nullptr)
        {
            act->update(dt);
        }
    }
    for (Actor* act : mActorList)
    {
        
        if (act != nullptr)
        {
            act->update(dt);
        }
        
    }
    
    /*
    for (int i = 0; i < mActorList.size(); i++)
    {

        if (mActorList[i] != nullptr)
            mActorList[i]->update(dt);
    }
    */

    for (Actor* act : mUpdateList_Extra)
    {
        if (act)
            act->update(dt);
    }
}



void World::Delete_Actors()
{
    if (mDeleteActorList.size() == 0)
        return;

    for (Actor* act : mDeleteActorList)
    {
        UnRegisterActor(act);
        
        delete act;
        act = nullptr;
    }

    mDeleteActorList.clear();
}

void World::Delete_Bulletes()
{
    if (mDeleteBulletList.size() == 0)
        return;

    for (Actor* act : mDeleteBulletList)
    {
        UnRegisterBullet(act);

        delete act;
        act = nullptr;
    }

    mDeleteBulletList.clear();
}

Actor* World::NewActor()
{
    Actor* act    = new Actor;
    act->mActorID = RegisterActor(act);  // return unsigned int idx(몇번째 액터인지)
    return act;
}

Actor* World::NewBullet()
{
    Actor* act    = new Actor;
    act->mBulletID = RegisterBullet(act);  // return unsigned int idx(몇번째 액터인지)
    return act;
}

void World::EraseActor(Actor* act)
{
    x++;
    act->mStatus = Actor::E_Died;
    mDeleteActorList.push_back(act);
}

void World::EraseBullet(Actor* act)
{
    act->mStatus = Actor::E_Died;
    mDeleteBulletList.push_back(act);
}

unsigned int World::RegisterBullet(Actor* aa)
{
    unsigned int bidx;

    if (mBulletList.size() >= 1024 && mFreeBulletIDList.size() > 0)
    {
        bidx = mFreeBulletIDList.front();
        mFreeBulletIDList.pop_front();
        mBulletList[bidx] = aa;
    }
    else
    {
        bidx = mBulletList.size();
        mBulletList.push_back(aa);
    }

    return bidx;
}

void World::UnRegisterBullet(Actor* aa)
{
    unsigned int idx = aa->mBulletID;

    if (idx == UINT32_MAX)
        return;

    mBulletList[idx] = nullptr;
    mFreeBulletIDList.push_back(idx);
}

unsigned int World::RegisterActor(Actor* aa)
{
    unsigned int idx;

    if (mActorList.size() >= 1024 && mFreeActorIDList.size() > 0)
    {
        idx = mFreeActorIDList.front();
        mFreeActorIDList.pop_front();
        mActorList[idx] = aa;
    }
    else
    {
        idx = mActorList.size();
        mActorList.push_back(aa);
    }

    return idx;
}

void World::UnRegisterActor(Actor* aa)
{
    unsigned int idx = aa->mActorID;

    if (idx == UINT32_MAX)
        return;

    mActorList[idx] = nullptr;
    mFreeActorIDList.push_back(idx);
}
