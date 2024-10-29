#include "pch.h"
#include "World.h"
#include "Actor.h"

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
    for (Actor* act : mIdList.mActorList)
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
    updateActors(dt);
}

void World::updateActors(float dt)
{
    for (Actor* act : mIdList.mActorList)
    {
        if (act)
            act->update(dt);
    }

    for (Actor* act : mUpdateList_Extra)
    {
        if (act)
            act->update(dt);
    }
}

void World::eraseActor(Actor* act)
{
    //act->mStatus = Actor::E_Died;
    mDeleteActorList.push_back(act);
}

void World::Delete_Actors()
{
    if (mDeleteActorList.size() == 0)
        return;

    for (Actor* act : mDeleteActorList)
    {
        mIdList.Delete(act->mActorID);
        delete act;
    }

    mDeleteActorList.clear();
}

Actor* World::NewActor()
{
    Actor* act    = new Actor;
    act->mActorID = mIdList.Add(act);//return unsigned int idx(몇번째 액터인지)
    return act;
}
